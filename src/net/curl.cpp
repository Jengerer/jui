#include "jui/application/error_stack.hpp"
#include "jui/net/curl.hpp"

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
        // Initialize instance if not exists.
        if (instance_ == nullptr) {
            instance_ = new Curl();
            instance_->initialize();
        }

        return instance_;
    }

    /*
     * Delete instance if exists.
     */
    void Curl::shut_down( void )
    {
        if (instance_ != nullptr) {
            delete instance_;
            instance_ = nullptr;
        }
    }

    /*
     * Initialize CURL interfaces.
     */
    Curl::ReturnStatus Curl::initialize( void )
    {
        // Initialize CURL.
        curl_ = curl_easy_init();
        if (curl_ == nullptr) {
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

        // Read contents of file.
		JUTIL::DynamicString contents;
        if (!read( url, &contents )) {
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: download failed for %s.", url->get_string() );
            return false;
        }

        // Open file for writing.
        FILE* file;
        errno_t error = fopen_s( &file, destination->get_string(), "wb" );
        if (error != 0) {
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: failed to open %s for download.", destination->get_string() );
            return false;
        }
        
        // Write to file.
        size_t size = contents.get_length();
        size_t written = fwrite( contents.get_string(), size, 1, file );
        if (written != 1) {
            fclose( file );
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: failed to write to %s for download.", destination->get_string() );
            return false;
        }

        fclose( file );
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
