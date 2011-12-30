#ifndef FILE_TEXTURE_H
#define FILE_TEXTURE_H

#include "jui/texture.h"

#include <string>

class FileTexture : public Texture
{
	
public:

	__declspec(dllexport) FileTexture( const std::string& filename );

	// File attributes.
	__declspec(dllexport) const std::string& get_filename() const;

private:

	std::string filename_;

};

#endif // FILE_TEXTURE_H