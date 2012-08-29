#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "jui/gfx/opengl_shared.hpp"

namespace JUI
{

    class Texture
    {

    public:

        __declspec(dllexport) Texture();
        __declspec(dllexport) Texture( GLuint texture, GLsizei width, GLsizei height, GLfloat tu = 1.0f, GLfloat tv = 1.0f );
        __declspec(dllexport) virtual ~Texture();

        // Texture setter.
        __declspec(dllexport) void set_texture( GLuint texture, GLsizei width, GLsizei height, GLfloat tu, GLfloat tv );

        // Texture attribute functions.
        __declspec(dllexport) bool is_loaded() const;
        __declspec(dllexport) GLuint get_texture() const;
        __declspec(dllexport) GLsizei get_width() const;
        __declspec(dllexport) GLsizei get_height() const;
        __declspec(dllexport) GLfloat get_tu() const;
        __declspec(dllexport) GLfloat get_tv() const;

    private:

        GLuint texture_;

        // Size variables.
        GLsizei width_;
        GLsizei height_;

        // Texture mapping coordinates.
        GLfloat tu_;
        GLfloat tv_;

    };

}

#endif // TEXTURE_HPP
