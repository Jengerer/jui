#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "jui/layout/component.hpp"

namespace JUI
{

    class Image: public Component
    {

    public:

        __declspec(dllexport) Image( const Texture* texture, float localX = 0.0f, float localY = 0.0f );

        __declspec(dllexport) virtual void draw( Graphics2D* graphics );
        __declspec(dllexport) void set_texture( const Texture *texture );

        __declspec(dllexport) void set_alpha( int alpha );
        __declspec(dllexport) void set_tint( const Colour& tint );
        __declspec(dllexport) const Colour& get_tint( void ) const;

    private:

        const Texture*	get_texture( void ) const;

    private:

        const Texture *texture_;
        Colour tint_;

    };

}

#endif // IMAGE_HPP
