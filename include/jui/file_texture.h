#ifndef FILE_TEXTURE_H
#define FILE_TEXTURE_H

#include "jui/texture.h"

#include <string>

class FileTexture : public Texture
{
	
public:

	FileTexture( const std::string& filename );

	// File attributes.
	const std::string& get_filename() const;

private:

	std::string filename_;

};

#endif // FILE_TEXTURE_H