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
    bool Curl::download( const JUTIL::ConstantString& url, const JUTIL::ConstantString& destination )
    {
        // Set the URL.
        CURLcode result = curl_easy_setopt( curl_, CURLOPT_URL, url.get_string() );
        if (result != CURLE_OK) {
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: failed to set operation." );
            return false;
        }

        // Copy destination to create path.
        JUTIL::StringBuilder builder;
        if (!builder.copy( destination.get_string(), destination.get_length() )) {
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: failed to allocate for path name." );
            return false;
        }
        JUTIL::String destination_copy( &builder );
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
            slash_index = destination.find( '/', slash_index + 1 );
        }
        builder.clear();

        // Read contents of file.
        if (!read( url, &builder )) {
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: download failed for %s.", url.get_string() );
            return false;
        }

        // Open file for writing.
        FILE* file;
        errno_t error = fopen_s( &file, destination.get_string(), "w" );
        if (error != 0) {
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: failed to open %s for download.", destination_string );
            return false;
        }
        
        // Write to file.
        size_t size = builder.get_length() + 1;
        size_t written = fwrite( builder.get_string(), size, 1, file );
        if (written != size) {
            fclose( file );
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: failed to write to %s for download.", destination_string );
            return false;
        }

        fclose( file );
        return true;
    }

    /*
     * Read the file at the given URL to string.
     */
    bool Curl::read( const JUTIL::ConstantString& url, JUTIL::StringBuilder* builder )
    {
        // Create empty memory buffer struct.
        JUTIL::ArrayBuilder<char> buffer;

        // Set up CURL operation.
        curl_easy_setopt( curl_, CURLOPT_URL, url.get_string() );
        curl_easy_setopt( curl_, CURLOPT_WRITEFUNCTION, write_buffer );
        curl_easy_setopt( curl_, CURLOPT_WRITEDATA, &buffer );
        curl_easy_setopt( curl_, CURLOPT_FAILONERROR, true );
        CURLcode result = curl_easy_perform( curl_ );
        if (result != CURLE_OK) {
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: read failed for %s.", url.get_string() );
        }

        // Set builder's buffer.
        builder->set_string( buffer.get_array(), buffer.get_size() );
        buffer.release();
        return true;
    }

    /*
     * Callback when ready to write.
     */
    static size_t write_buffer( void *buffer, size_t size, size_t num_members, void* data )
    {
        // Get real buffer size.
        size_t real_size = size * num_members;
        JUTIL::ArrayBuilder<char>* array_buffer = static_cast<JUTIL::ArrayBuilder<char>*>(data);

        // Get buffer of proper size.
        size_t old_size = array_buffer->get_size();
        size_t new_size = old_size + real_size;
        if (!array_buffer->set_size( new_size ))
        {
            return 0;
        }

        char* write_start = array_buffer->get_array() + old_size;
        memcpy( write_start, buffer, real_size );
        return real_size;
    }

}
