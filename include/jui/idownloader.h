#ifndef IDOWNLOADER_H
#define IDOWNLOADER_H

/*
 * Interface for requesting files from an external server.
 */
class IDownloader
{

public:

	// Download a file to disk.
	virtual void download( const std::string& url, const std::string& destination ) = 0;

	// Read file to string.
	virtual std::string read( const std::string& url ) = 0;

};

#endif // IDOWNLOADER_H