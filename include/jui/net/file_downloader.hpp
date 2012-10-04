#ifndef FILE_DOWNLOADER_HPP
#define FILE_DOWNLOADER_HPP

#include "jui/net/downloader_interface.hpp"

namespace JUI
{

    class FileDownloader
    {
        
    public:

        // Initialize and exit.
        static __declspec(dllexport) FileDownloader* get_instance( void );
        static __declspec(dllexport) void shut_down( void );

        // Get a file if it doesn't exist.
        __declspec(dllexport) bool check_and_get( const JUTIL::ConstantString& filename, const JUTIL::ConstantString& url );

        // Get a file.
        __declspec(dllexport) bool get( const JUTIL::ConstantString& filename, const JUTIL::ConstantString& url );

        // Read a file.
        __declspec(dllexport) bool read( const JUTIL::ConstantString& url, JUTIL::String* output );

    private:

        // Private constructor.
        FileDownloader( DownloaderInterface* downloader );

    private:

        // Singleton instance.
        static FileDownloader* instance_;

    private:

        // Singleton member variable.
        DownloaderInterface* downloader_;

    };

}

#endif // FILE_DOWNLOADER_HPP
