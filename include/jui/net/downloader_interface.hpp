#ifndef DOWNLOADER_INTERFACE_HPP
#define DOWNLOADER_INTERFACE_HPP

#include <string/constant_string.hpp>
#include <string/string.hpp>

namespace JUI
{

    /*
     * Interface for requesting files from an external server.
     */
    class DownloaderInterface
    {

    public:

        // Download a file to disk.
        virtual bool download( const JUTIL::ConstantString& url, const JUTIL::ConstantString& destination ) = 0;

        // Read file to string builder.
        virtual bool read( const JUTIL::ConstantString& url, JUTIL::String* output ) = 0;

    };

}

#endif // DOWNLOADER_INTERFACE_HPP
