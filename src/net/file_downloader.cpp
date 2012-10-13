#include "jui/net/curl.hpp"
#include "jui/net/file_downloader.hpp"
#include <memory/base_allocator.hpp>

namespace JUI
{

    // Downloader interface.
    FileDownloader* FileDownloader::instance_ = nullptr;

    /*
     * Downloader constructor.
     */
    FileDownloader::FileDownloader( DownloaderInterface* downloader )
    {
        downloader_ = downloader;
    }

    /*
     * Create/get instance of singleton.
     */
    FileDownloader* FileDownloader::get_instance( void )
    {
        // Get instance.
        if (instance_ == nullptr) {
            // Get an instance of CURL.
            Curl* curl = Curl::get_instance();
            if (curl == nullptr) {
                return nullptr;
            }

            // Create instance of downloader.
            if (!JUTIL::BaseAllocator::allocate( &instance_ )) {
				Curl::shut_down();
				return nullptr;
            }
			instance_ = new (instance_) FileDownloader( curl );
        }

        return instance_;
    }

    /*
     * Clean up downloader interface.
     */
    void FileDownloader::shut_down( void )
    {
        // Delete instance.
        JUTIL::BaseAllocator::safe_destroy( &instance_ );
    }

    /*
     * Check if a file exists; if it does not, get it from
     * the specified URL.
     */
    bool FileDownloader::check_and_get( const JUTIL::String* filename, const JUTIL::String* url )
    {
        // Check if file exists.
        FILE* file = nullptr;
        errno_t error = fopen_s( &file, filename->get_string(), "r" );

        // Get file if failed to open.
        if (error != 0) {
            return get( filename, url );
        }
        
        // File already exists.
        fclose( file );
        return true;
    }

    /*
     * Get a file without checking if it's already there.
     */
    bool FileDownloader::get( const JUTIL::String* filename, const JUTIL::String* url )
    {
        return downloader_->download( url, filename );
    }

    /*
     * Read a file to string.
     */
    bool FileDownloader::read( const JUTIL::String* url, JUTIL::DynamicString* output )
    {
        return downloader_->read( url, output );
    }

}
