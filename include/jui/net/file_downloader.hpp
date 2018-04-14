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
		__declspec(dllexport) bool check_and_get( const JUTIL::String* filename, const JUTIL::String* url );

		// Get a file.
		__declspec(dllexport) bool get( const JUTIL::String* filename, const JUTIL::String* url );

		// Read a file.
		__declspec(dllexport) bool read( const JUTIL::String* url, JUTIL::DynamicString* output );

		// Read a cached filed.
		__declspec(dllexport) bool read_cached( const JUTIL::String* filename, const JUTIL::String* url, JUTIL::DynamicString* output );

		// Set maximum wait time for an operation to complete
		__declspec(dllexport) void set_timeout( long timeout );

		// Removes maxximum wait time for operations to complete.
		__declspec(dllexport) void clear_timeout();

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
