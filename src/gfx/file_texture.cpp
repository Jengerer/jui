#include "jui/gfx/file_texture.hpp"

namespace JUI
{

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

}
