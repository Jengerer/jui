#include "jui/file_texture.h"

/*
 * File texture constructor.
 */
FileTexture::FileTexture( const std::string& filename )
{
	filename_ = filename;
}

/*
 * Get filename.
 */
const std::string& FileTexture::get_filename() const
{
	return filename_;
}