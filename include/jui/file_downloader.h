#ifndef FILE_DOWNLOADER_H
#define FILE_DOWNLOADER_H

#include <string>

#include "jui/idownloader.h"

class FileDownloader
{
	
public:

	// Initialize and exit.
	static __declspec(dllexport) void initialize();
	static __declspec(dllexport) void close();

	// Get a file if it doesn't exist.
	static __declspec(dllexport) void check_and_get( const std::string& filename, const std::string& url );

	// Get a file.
	static __declspec(dllexport) void get( const std::string& filename, const std::string& url );

	// Read a file.
	static __declspec(dllexport) std::string read( const std::string& url );

private:

	static IDownloader* downloader_;

};

#endif // FILE_DOWNLOADER_H