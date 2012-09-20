#ifndef CURL_HPP
#define CURL_HPP

#include <curl/curl.h>
#include <curl/easy.h>
#include "jui/net/downloader_interface.hpp"

/*
 * Curl implementation of downloader interface.
 */
namespace JUI
{

    /* Struct for downloaded files. */
    struct Download
    {
        const char* filename;
        FILE* file;
    };

    /* Struct for reading files. */
    struct MemoryBuffer
    {
        char* memory;
        size_t size;
    };

    /* Helper functions for downloading/reading. */
    static void *reallocate( void *buffer, size_t size );
    static size_t write( void *buffer, size_t size, size_t num_members, void* data );
    static size_t write_callback( void *buffer, size_t size, size_t num_members, void* data );

    class Curl : public DownloaderInterface
    {

    public:

        enum ReturnStatus
        {
            Success = 0,
            InitializeFailure,
            SetOperationFailure,
            DownloadFailure,
            ReadFailure,
            OutOfMemoryFailure,
        };

    public:

        // Public destructor for allocation.
        virtual ~Curl( void );

        // Create/get singleton instance.
        static Curl* get_instance( void );

        // Shut down singleton.
        static void shut_down( void );

        // Downloader interface functions.
        virtual bool download( const JUTIL::ConstantString& string, const JUTIL::ConstantString& destination );
        virtual bool read( const JUTIL::ConstantString& url, JUTIL::StringBuilder* output );

    private:

        // Private constructor.
        Curl( void );

        // Handling interfaces.
        ReturnStatus initialize( void );
        void close( void );

        // Clean interfaces.
        void clean( void );

    private:
        
        // Singleton reference.
        static Curl* instance_;

    private:

        // Singleton members.
        CURL* curl_;

    };

}

#endif // CURL_HPP
