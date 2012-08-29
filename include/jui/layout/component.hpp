#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "jui/gfx/idrawable.hpp"

namespace JUI
{

    class Component : public IDrawable
    {

    public:

        __declspec(dllexport) Component( float x = 0.0f, float y = 0.0f );
        __declspec(dllexport) virtual ~Component( void );

        // Position functions.
        __declspec(dllexport) virtual void	set_position( float x, float y );
        
        // Position getters.
        __declspec(dllexport) virtual float	get_x() const;
        __declspec(dllexport) virtual float	get_y() const;

        // Visibility functions.
        __declspec(dllexport) virtual void set_alpha( int alpha ); // Using int to handle underflow.
        __declspec(dllexport) GLubyte get_alpha( void ) const;

        // Size functions.
        __declspec(dllexport) virtual void set_size( int width, int height );
        __declspec(dllexport) virtual int get_width( void ) const;
        __declspec(dllexport) virtual int get_height( void ) const;

    private:

        float x_;
        float y_;
        int width_;
        int height_;
        GLubyte alpha_;

    };

}

#endif // COMPONENT_HPP
