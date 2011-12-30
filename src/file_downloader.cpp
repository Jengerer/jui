#include "jui/curl.h"
#include "jui/file_downloader.h"

#include <stdio.h>
#include "jui/curl.h"

// Downloader interface.
FileDownloader* FileDownloader::instance_ = nullptr;

/*
 * Downloader constructor.
 */
FileDownloader::FileDownloader()
{
	// Get instance of CURL.
	downloader_ = Curl::get_instance();
}

/*
 * Create/get instance of singleton.
 */
FileDownloader* FileDownloader::get_instance()
{
	// Get instance.
	if (instance_ == nullptr) {
		instance_ = new FileDownloader();
	}

	return instance_;
}

/*
 * Clean up downloader interface.
 */
void FileDownloader::shut_down()
{
	// Delete instance.
	if (instance_ != nullptr) {
		delete instance_;
		instance_ = nullptr;
	}
}

/*
 * Check if a file exists; if it does not, get it from
 * the specified URL.
 */
void FileDownloader::check_and_get( const std::string& filename, const std::string& url )
{
	// Check if file exists.
	FILE* file = nullptr;
	errno_t error = fopen_s( &file, filename.c_str(), "r" );

	// Get file if failed to open.
	if (error != 0) {
		get( filename, url );
	}
	else {
		// File already exists.
		fclose( file );
	}
}

/*
 * Get a file without checking if it's already there.
 */
void FileDownloader::get( const std::string& filename, const std::string& url )
{
	downloader_->download( url, filename );
}

/*
 * Read a file to string.
 */
std::string FileDownloader::read( const std::string& url )
{
	return downloader_->read( url );
}