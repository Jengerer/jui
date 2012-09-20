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

        // Create the folder(s) if needed.
        size_t slash = destination.find( '/' );
        while (slash != std::string::npos) {
            // TODO: This can be cleaner, no need to remake substr.
            std::string path = destination.substr( 0, slash );
            if ( GetFileAttributes( path.c_str() ) == INVALID_FILE_ATTRIBUTES )
                CreateDirectory( path.c_str(), 0 );

            slash = destination.find( '/', slash + 1 );
        }

        // Create the file.
        Download download;
        download.filename = destination.c_str();
        download.file = nullptr;

        // Get the file ready for downloading.
        curl_easy_setopt( curl_, CURLOPT_WRITEDATA, &download );
        curl_easy_setopt( curl_, CURLOPT_WRITEFUNCTION, write );
        curl_easy_setopt( curl_, CURLOPT_FAILONERROR, true );

        // Get it!
        result = curl_easy_perform( curl_ );
        if (result != CURLE_OK) {
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: download failed for %s.", url.get_string() );
            return false;
        }

        // Close the stream if it exists.
        if (download.file != nullptr) {
            fclose( download.file );
        }
    }

    /*
     * Read the file at the given URL to string.
     */
    bool Curl::read( const JUTIL::ConstantString& url, JUTIL::StringBuilder* builder )
    {
        // Create empty memory buffer struct.
        MemoryBuffer read;
        ZeroMemory( &read, sizeof( MemoryBuffer ) );

        // Specify url.
        curl_easy_setopt( curl_, CURLOPT_URL, url.get_string() );

        // Send all data to this function.
        curl_easy_setopt( curl_, CURLOPT_WRITEFUNCTION, write_callback );

        // Send chuck struct.
        curl_easy_setopt( curl_, CURLOPT_WRITEDATA, &read );

        // Fail if not found.
        curl_easy_setopt( curl_, CURLOPT_FAILONERROR, true );

        // Get it!
        CURLcode result = curl_easy_perform( curl_ );
        if (result != CURLE_OK) {
            ErrorStack* error_stack = ErrorStack::get_instance();
            error_stack->log( "Curl: read failed for %s.", url.get_string() );
        }

        // Set builder's buffer.
        builder->set_string( read.memory, read.size );
        return true;
    }

    /*
     * Helper function to allocate or reallocate to size.
     */
    static void *reallocate( void* buffer, size_t size )
    {
        return (buffer != nullptr ? realloc( buffer, size ) : malloc( size ));
    }

    /*
     * Callback when ready to write.
     */
    static size_t write_callback( void *buffer, size_t size, size_t num_members, void* data )
    {
        // Get real buffer size.
        size_t real_size = size*num_members;
        struct MemoryBuffer *read = (struct MemoryBuffer*)data;

        // Get buffer of proper size.
        read->memory = (char*)reallocate( read->memory, read->size + real_size + 1 );
        if (read->memory != nullptr) {
            // Write received data.
            void* copy_memory = &read->memory[read->size];
            memcpy( copy_memory, buffer, real_size );
            read->size += real_size;
            read->memory[read->size] = 0;
        }

        return real_size;
    }

    /*
     * Call to write to buffer.
     */
    static size_t write( void *buffer, size_t size, size_t num_members, void* data )
    {
        struct Download *download = (struct Download*)data;

        // Open file if none yet.
        if ((download != nullptr) && (download->file == nullptr)) {
            errno_t error = fopen_s( &download->file, download->filename, "wb" );
            if (error != 0) {
                throw std::runtime_error( "Failed to open file to download." );
            }
        }

        // Write to file.
        return fwrite( buffer, size, num_members, download->file );
    }

}
