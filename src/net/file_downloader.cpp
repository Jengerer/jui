#include "jui/net/curl.hpp"
#include "jui/net/file_downloader.hpp"
#include <memory\base_allocator.hpp>

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
            JUI::Curl* curl = Curl::get_instance();
            if (curl == nullptr) {
                return nullptr;
            }

            // Create instance of downloader.
            if (!JUTIL::BaseAllocator::allocate( &instance_ )) {
                instance_ = new (instance_) FileDownloader( curl );
            }
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
    bool FileDownloader::check_and_get( const JUTIL::ConstantString& filename, const JUTIL::ConstantString& url )
    {
        // Check if file exists.
        FILE* file = nullptr;
        errno_t error = fopen_s( &file, filename.get_string(), "r" );

        // Get file if failed to open.
        if (error != 0) {
            return get( filename, url );
        }
        else {
            // File already exists.
            fclose( file );
        }
    }

    /*
     * Get a file without checking if it's already there.
     */
    bool FileDownloader::get( const JUTIL::ConstantString& filename, const JUTIL::ConstantString& url )
    {
        return downloader_->download( url, filename );
    }

    /*
     * Read a file to string.
     */
    bool FileDownloader::read( const JUTIL::ConstantString& url, JUTIL::StringBuilder* output )
    {
        return downloader_->read( url, output );
    }

}
