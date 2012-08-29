#ifndef FILE_DOWNLOADER_HPP
#define FILE_DOWNLOADER_HPP

#include <string>

#include "jui/net/idownloader.hpp"

namespace JUI
{

    class FileDownloader
    {
        
    public:

        // Initialize and exit.
        static __declspec(dllexport) FileDownloader* get_instance();
        static __declspec(dllexport) void shut_down();

        // Get a file if it doesn't exist.
        __declspec(dllexport) void check_and_get( const std::string& filename, const std::string& url );

        // Get a file.
        __declspec(dllexport) void get( const std::string& filename, const std::string& url );

        // Read a file.
        __declspec(dllexport) std::string read( const std::string& url );

    private:

        // Private constructor.
        FileDownloader();

    private:

        // Singleton instance.
        static FileDownloader* instance_;

    private:

        // Singleton member variable.
        IDownloader* downloader_;

    };

}

#endif // FILE_DOWNLOADER_HPP
