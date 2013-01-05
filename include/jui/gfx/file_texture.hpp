#ifndef FILE_TEXTURE_HPP
#define FILE_TEXTURE_HPP

#include "jui/gfx/texture.hpp"
#include <string/string.hpp>

namespace JUI
{

	class FileTexture : public Texture
	{
		
	public:

		__declspec(dllexport) FileTexture( const JUTIL::String* filename );
		__declspec(dllexport) const JUTIL::String* get_filename( void ) const;

	private:

		const JUTIL::String* filename_;

	};

}

#endif // FILE_TEXTURE_HPP
