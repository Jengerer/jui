#ifndef DOWNLOADER_INTERFACE_HPP
#define DOWNLOADER_INTERFACE_HPP

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
        virtual bool download( const JUTIL::String* url, const JUTIL::String* destination ) = 0;

        // Read file to string builder.
        virtual bool read( const JUTIL::String* url, JUTIL::DynamicString* output ) = 0;

    };

}

#endif // DOWNLOADER_INTERFACE_HPP
