#ifndef FILE_TEXTURE_HPP
#define FILE_TEXTURE_HPP

#include "jui/gfx/texture.hpp"
#include <string>

namespace JUI
{

    class FileTexture : public Texture
    {
        
    public:

        __declspec(dllexport) FileTexture( const std::string& filename );

        // File attributes.
        __declspec(dllexport) const std::string& get_filename() const;

    private:

        std::string filename_;

    };

}

#endif // FILE_TEXTURE_HPP
