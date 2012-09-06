#ifndef FILE_TEXTURE_HPP
#define FILE_TEXTURE_HPP

#include "jui/gfx/texture.hpp"
#include <string/constant_string.hpp>

namespace JUI
{

    class FileTexture : public Texture
    {
        
    public:

        __declspec(dllexport) FileTexture( const JUTIL::ConstantString& filename );
        __declspec(dllexport) const JUTIL::ConstantString* get_filename( void ) const;

    private:

        JUTIL::ConstantString filename_;

    };

}

#endif // FILE_TEXTURE_HPP
