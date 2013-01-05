#include "jui/gfx/file_texture.hpp"

namespace JUI
{

	/*
	 * File texture constructor.
	 */
	FileTexture::FileTexture( const JUTIL::String* filename )
	{
		filename_ = filename;
	}

	/*
	 * Get filename.
	 */
	const JUTIL::String* FileTexture::get_filename( void ) const
	{
		return filename_;
	}

}
