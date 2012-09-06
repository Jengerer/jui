#include "jui/gfx/file_texture.hpp"

namespace JUI
{

    /*
     * File texture constructor.
     */
    FileTexture::FileTexture( const JUTIL::ConstantString& filename )
    {
        filename_ = filename;
    }

    /*
     * Get filename.
     */
    const JUTIL::ConstantString* FileTexture::get_filename( void ) const
    {
        return &filename_;
    }

}
