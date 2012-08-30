#ifndef CURL_HPP
#define CURL_HPP

#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include "jui/net/idownloader.hpp"

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

    class Curl : public IDownloader
    {
    public:

        // Create/get singleton instance.
        static Curl* get_instance();

        // Shut down singleton.
        static void shut_down();

        // Downloader interface functions.
        virtual void download( const std::string& url, const std::string& destination );

        // Read file to string.
        virtual std::string read( const std::string& url );

    private:

        // Private constructor.
        Curl( void );

        // Private destructor.
        virtual ~Curl( void );

        // Handling interfaces.
        void initialize( void );

        // Close interfaces.
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
