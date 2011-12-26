#ifndef CURL_H
#define CURL_H

#include <string>

#include <curl/curl.h>
#include <curl/easy.h>

#include "jui/idownloader.h"

/* Struct for downloaded files. */
struct Download {
	const char* filename;
	FILE* file;
};

/* Struct for reading files. */
struct MemoryBuffer {
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

	static Curl* get_instance();
	static void shut_down();

	// Downloader interface functions.
	virtual void download( const std::string& url, const std::string& destination );
	virtual std::string read( const std::string& url );

private:

	Curl( void );
	virtual ~Curl( void );

	// Handling interfaces.
	void initialize( void );
	void close( void );
	void clean( void );

private:
	
	static Curl* instance_;
	static CURL* curl_;

};

#endif // CURL_H