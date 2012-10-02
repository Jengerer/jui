#include "jui/gfx/texture.hpp"

namespace JUI
{

    /*
     * 2D texture constructor.
     */
    Texture::Texture( void )
    {
        set_texture( 0, 0, 0, 1.0f, 1.0f );
    }

    /*
     * 2D texture constructor from texture parameters.
     */
    Texture::Texture( GLuint texture, GLsizei width, GLsizei height, GLfloat tu, GLfloat tv )
    {
        set_texture( texture, width, height, tu, tv );
    }

    /*
     * Texture destructor.
     */
    Texture::~Texture( void )
    {
        glDeleteTextures( 1, &texture_ );
    }

    /*
     * Set new texture by texture parameters.
     */
    void Texture::set_texture( GLuint texture, GLsizei width, GLsizei height, GLfloat tu, GLfloat tv )
    {
        texture_ = texture;
        width_ = width;
        height_ = height;
        tu_ = tu;
        tv_ = tv;
    }

    /*
     * Returns whether the texture has been initialized.
     */
    bool Texture::is_loaded( void ) const
    {
        return texture_ != 0;
    }

    /*
     * Gets OpenGL handle to texture.
     */
    GLuint Texture::get_texture( void ) const
    {
        return texture_;
    }

    /*
     * Get texture width.
     */
    GLsizei Texture::get_width( void ) const
    {
        return width_;
    }

    /*
     * Get texture height.
     */
    GLsizei Texture::get_height( void ) const
    {
        return height_;
    }

    /*
     * Get texture X coordinate.
     */
    GLfloat Texture::get_tu() const
    {
        return tu_;
    }

    /*
     * Get texture Y coordinate.
     */
    GLfloat Texture::get_tv() const
    {
        return tv_;
    }

}
