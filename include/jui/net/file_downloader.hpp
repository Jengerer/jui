#ifndef FILE_DOWNLOADER_HPP
#define FILE_DOWNLOADER_HPP

#include "jui/jui_base.hpp"
#include "jui/net/downloader_interface.hpp"

namespace JUI
{

	class JUI_API FileDownloader
	{
		
	public:

		// Initialize and exit.
		static FileDownloader* get_instance( void );
		static void shut_down( void );

		// Get a file if it doesn't exist.
		bool check_and_get( const JUTIL::String* filename, const JUTIL::String* url );

		// Get a file.
		bool get( const JUTIL::String* filename, const JUTIL::String* url );

		// Read a file.
		bool read( const JUTIL::String* url, JUTIL::DynamicString* output );

		// Read a cached filed.
		bool read_cached( const JUTIL::String* filename, const JUTIL::String* url, JUTIL::DynamicString* output );

		// Set maximum wait time for an operation to complete
		void set_timeout( long timeout );

		// Removes maxximum wait time for operations to complete.
		void clear_timeout();

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
