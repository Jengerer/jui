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

	// Callbacks for reading and writing.
	static size_t write_buffer( void *buffer, size_t size, size_t num_members, void* data );

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
		virtual bool download( const JUTIL::String* string, const JUTIL::String* destination );
		virtual bool read( const JUTIL::String* url, JUTIL::DynamicString* output );
		virtual bool read_cached( const JUTIL::String* url, const JUTIL::String* destination, JUTIL::DynamicString* output );

	private:

		bool creat_path_to( const JUTIL::String* destination );
		bool read_from_local_file( const JUTIL::String* destination, JUTIL::DynamicString* output );
		bool write_to_local_file( const JUTIL::String* destination, JUTIL::String* output );

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
