#include "jui/application/error_stack.hpp"
#include "jui/net/curl.hpp"
#include <ctime>

namespace JUI
{

	Curl* Curl::instance_ = nullptr;

	/*
	 * Constructor does nothing.
	 */
	Curl::Curl( void )
	{
		// Nothing.
	}

	/*
	 * Clean operation and clean up interfaces.
	 */
	Curl::~Curl( void )
	{
		clean();
		curl_global_cleanup();
	}

	/*
	 * Get an instance; create if necessary.
	 */
	Curl* Curl::get_instance( void )
	{
		// Stack for logging.
		JUI::ErrorStack* stack = JUI::ErrorStack::get_instance();

		// Initialize instance if not exists.
		if (instance_ == nullptr) {
			if (!JUTIL::BaseAllocator::allocate( &instance_ )) {
				stack->log( "Failed to allocate Curl instance." );
				return nullptr;
			}
			instance_ = new (instance_) Curl();
			JUI::Curl::ReturnStatus status = instance_->initialize();
			if (status != Success) {
				return nullptr;
			}
		}

		return instance_;
	}

	/*
	 * Delete instance if exists.
	 */
	void Curl::shut_down( void )
	{
		JUTIL::BaseAllocator::safe_destroy( &instance_ );
	}

	/*
	 * Initialize CURL interfaces.
	 */
	Curl::ReturnStatus Curl::initialize( void )
	{
		// Error stack for logging.
		JUI::ErrorStack* stack = JUI::ErrorStack::get_instance();

		// Initialize CURL.
		curl_ = curl_easy_init();
		if (curl_ == nullptr) {
			stack->log( "Failed to initialize Curl." );
			return InitializeFailure;
		}

		return Success;
	}

	/*
	 * Clean up CURL operations.
	 */
	void Curl::clean( void )
	{
		curl_easy_cleanup( curl_ );
	}

	/*
	 * Download file at given URL to destination.
	 */
	bool Curl::download( const JUTIL::String* url, const JUTIL::String* destination )
	{
		// Set the URL.
		CURLcode result = curl_easy_setopt( curl_, CURLOPT_URL, url->get_string() );
		if (result != CURLE_OK) {
			ErrorStack* error_stack = ErrorStack::get_instance();
			error_stack->log( "Curl: failed to set operation." );
			return false;
		}

		creat_path_to( destination );

		// Read contents of file.
		JUTIL::DynamicString contents;
		if (!read( url, &contents )) {
			ErrorStack* error_stack = ErrorStack::get_instance();
			error_stack->log( "Curl: download failed for %s.", url->get_string() );
			return false;
		}

		if (!write_to_local_file( destination, &contents )) {
			ErrorStack* error_stack = ErrorStack::get_instance();
			error_stack->log( "Curl: failed to write to %s for download.", destination->get_string() );
			return false;
		}

		return true;
	}

	/*
	 * Read the file at the given URL to string.
	 */
	bool Curl::read( const JUTIL::String* url, JUTIL::DynamicString* output )
	{
		// Error stack for reporting.
		ErrorStack* stack = ErrorStack::get_instance();

		// Create empty memory buffer struct.
		JUTIL::DynamicString string;

		// Set up CURL operation.
		curl_easy_setopt( curl_, CURLOPT_URL, url->get_string() );
		curl_easy_setopt( curl_, CURLOPT_WRITEFUNCTION, write_buffer );
		curl_easy_setopt( curl_, CURLOPT_WRITEDATA, &string );
		curl_easy_setopt( curl_, CURLOPT_FAILONERROR, true );
		CURLcode result = curl_easy_perform( curl_ );
		if (result != CURLE_OK) {
			stack->log( "Curl: read failed for %s.", url->get_string() );
			return false;
		}

		// Set builder's buffer.
		output->set_string( string.get_string(), string.get_length() );
		string.release();
		return true;
	}

	/*
	 * Read the file at the given URL to string. The file is then cached to the
	 * given destination string. If the file at the destination is up to date,
	 * the file is read from disk rather than fetched from the URL.
	 */
	bool Curl::read_cached( const JUTIL::String* url, const JUTIL::String* destination, JUTIL::DynamicString* output )
	{
		//return read( url, output );
		// Error stack for reporting.
		ErrorStack* stack = ErrorStack::get_instance();

		bool send_http_header = true;

		// Create date and sum strings
		JUTIL::DynamicString date_destination;
		if (!date_destination.copy( destination->get_string(), destination->get_length() )) {
			stack->log( "Curl: failed to allocate for date path name." );
			return false;
		}
		if(!date_destination.write( ".date" )) {
			stack->log( "Curl: failed to append date file extention." );
			return false;
		}
		JUTIL::DynamicString sum_destination;
		if (!sum_destination.copy( destination->get_string(), destination->get_length() )) {
			stack->log( "Curl: failed to allocate for sum path name." );
			return false;
		}
		if(!sum_destination.write( ".sum" )) {
			stack->log( "Curl: failed to append sum file extention." );
			return false;
		}

		// Ensure that the folder exists
		if(!creat_path_to( destination )) {
			stack->log( "Curl: failed to create cache folder." );
			return false;
		}

		// Check if the cache file exists
		JUTIL::DynamicString cache_string;
		if (read_from_local_file( destination, &cache_string )) {
			// Check the sum
			JUTIL::DynamicString cache_sum_string;
			if(read_from_local_file( &sum_destination, &cache_sum_string )) {
				uint8_t calculated_sum [JUTIL::StringHasher::MD5_HASH_SIZE];
				JUTIL::StringHasher::md5( &cache_string, calculated_sum );

				JUTIL::DynamicString calculated_sum_string;
				for( int i = 0; i < JUTIL::StringHasher::MD5_HASH_SIZE; ++i ){
					if(!calculated_sum_string.write( "%02x", calculated_sum[i] )){
						stack->log( "Curl: failed to write to sum string." );
						return false;
					}
				}

				if(!cache_sum_string.is_equal( &calculated_sum_string )){
					send_http_header = false;
				}

			}else{
				// Sum does not exist, fetch the entire file.
				send_http_header = false;
			}

		}else{
			// Cache does not exist, fetch the entire file.
			send_http_header = false;
		}

		// Read from date file.
		JUTIL::DynamicString date;
		if(!read_from_local_file( &date_destination, &date )) {
			// Date file does not exist, fetch the entire file
			send_http_header = false;
		}

		// TODO: probably should check if the date file is of proper form
		// Example
		// If-Modified-Since: Mon, 07 Jan 2013 18:12:53 GMT
		
		// Create empty memory buffer struct.
		JUTIL::DynamicString downloaded_string;

		// Set up CURL operation.
		curl_easy_setopt( curl_, CURLOPT_URL, url->get_string() );
		curl_easy_setopt( curl_, CURLOPT_WRITEFUNCTION, write_buffer );
		curl_easy_setopt( curl_, CURLOPT_WRITEDATA, &downloaded_string );
		curl_easy_setopt( curl_, CURLOPT_FAILONERROR, true );
		
		// Add the if-modified header
		if(send_http_header){
			struct curl_slist if_modified_since_header;
			if_modified_since_header.data = date.get_string();
			if_modified_since_header.next = nullptr;
			curl_easy_setopt( curl_, CURLOPT_HTTPHEADER, &if_modified_since_header);
		}
		
		CURLcode result = curl_easy_perform( curl_ );
		if (result != CURLE_OK) {
			stack->log( "Curl: read failed for %s.", url->get_string() );
			return false;
		}

		// Update the cache, the date and the sum
		if( !send_http_header || downloaded_string.get_length() != 0 ){
			// Generate the date string
			time_t current_time = time( nullptr );
			struct tm current_gmt;
			gmtime_s( &current_gmt, &current_time );
			JUTIL::DynamicString current_time_string;
			char rfc_822_string [26];
			int test = strftime( rfc_822_string, 26, "%a, %d %b %Y %H:%M:%S", &current_gmt );
			if(!current_time_string.write( "If-Modified-Since: %s GMT", rfc_822_string )){
				stack->log( "Curl: failed to write date string" );
				return false;
			}

			// Generate the sum string
			uint8_t calculated_sum [JUTIL::StringHasher::MD5_HASH_SIZE];
			JUTIL::StringHasher::md5( &downloaded_string, calculated_sum );
			JUTIL::DynamicString calculated_sum_string;
			for( int i = 0; i < JUTIL::StringHasher::MD5_HASH_SIZE; ++i ){
				if(!calculated_sum_string.write( "%02x", calculated_sum[i] )){
					stack->log( "Curl: failed to write to sum string." );
					return false;
				}
			}

			if (!write_to_local_file( &sum_destination, &calculated_sum_string )) {
				stack->log( "Curl: failed to write cache date file" );
				return false;
			}
			if (!write_to_local_file( &date_destination, &current_time_string )) {
				stack->log( "Curl: failed to write cache date file" );
				return false;
			}
			if(!write_to_local_file( destination, &downloaded_string )) {
				stack->log( "Curl: failed to write cache file" );
				return false;
			}
		}

		// Clean up and remove header for other curl reads
		downloaded_string.release();
		curl_easy_setopt( curl_, CURLOPT_HTTPHEADER, nullptr);
		
		// Return the cache
		if(!read_from_local_file( destination, output )) {
			stack->log( "Curl: cache read failed for %s.", destination->get_string() );
			return false;
		}
		
		return true;

	}
	/*
	 * Creates a path to the given file if it does not exist.
	 */
	bool Curl::creat_path_to( const JUTIL::String* destination )
	{
		// Copy destination to create path.
		JUTIL::DynamicString destination_copy;
		if (!destination_copy.copy( destination->get_string(), destination->get_length() )) {
			ErrorStack* error_stack = ErrorStack::get_instance();
			error_stack->log( "Curl: failed to allocate for path name." );
			return false;
		}
		char* destination_string = destination_copy.get_string();

		// Create path if necessary.
		size_t slash_index = destination_copy.find( '/' );
		while (slash_index != JUTIL::String::INVALID_INDEX) {
			// End the string at index.
			destination_string[slash_index] = '\0';
			if (GetFileAttributes( destination_string ) == INVALID_FILE_ATTRIBUTES) {
				CreateDirectory( destination_string, 0 );
			}

			// Undo and find next slash.
			destination_string[slash_index] = '/';
			slash_index = destination->find( '/', slash_index + 1 );
		}
		destination_copy.clear();
		return true;
	}

	bool Curl::read_from_local_file( const JUTIL::String* destination, JUTIL::DynamicString* output )
	{
		// Open file.
		FILE* file;
		errno_t error = fopen_s( &file, destination->get_string(), "rb" );
		if (error != 0) {
			return false;
		}

		if(file == nullptr){
			return false;
		}
		
		// Get the size
		fseek (file , 0 , SEEK_END);
		size_t size = ftell (file);
		rewind (file);
		output->set_length( size );

		// Read from the file
		size_t read = fread( output->get_string(), 1, size, file );
		// Close the file reguardless of the error state
		fclose( file );
		if( read != size ){
			return false;
		}
		return true;
	}

	bool Curl::write_to_local_file( const JUTIL::String* destination, JUTIL::String* input )
	{
		// Open file for writing.
		FILE* file;
		errno_t error = fopen_s( &file, destination->get_string(), "wb" );
		if (error != 0) {
			return false;
		}
		
		// Write to file.
		size_t size = input->get_length();
		size_t written = fwrite( input->get_string(), 1, size, file );
		fclose( file );
		if ( written != size ) {
			return false;
		}
		return true;
	}

	/*
	 * Callback when ready to write.
	 */
	static size_t write_buffer( void *buffer, size_t size, size_t num_members, void* data )
	{
		// Get real buffer size.
		size_t real_size = size * num_members;
		JUTIL::DynamicString* string = static_cast<JUTIL::DynamicString*>(data);

		// Get buffer of proper size.
		size_t old_length = string->get_length();
		size_t new_length = old_length + real_size;
		if (!string->set_length( new_length )) {
			return 0;
		}

		// Write new string.
		char* write_start = string->get_string() + old_length;
		memcpy( write_start, buffer, real_size );
		return real_size;
	}

}
