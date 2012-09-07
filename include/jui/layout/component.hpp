#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "jui/gfx/idrawable.hpp"
#include "jui/layout/reserve_interface.hpp"

namespace JUI
{

    class __declspec(dllexport) Component : public IDrawable, public ReserveInterface
    {

    public:

        Component( float x = 0.0f, float y = 0.0f );
        virtual ~Component( void );

        // Default reservation function.
        virtual bool    reserve( void );

        // Position functions.
        virtual void	set_position( float x, float y );
        
        // Position getters.
        virtual float	get_x() const;
        virtual float	get_y() const;

        // Visibility functions.
        virtual void set_alpha( int alpha ); // Using int to handle underflow.
        GLubyte get_alpha( void ) const;

        // Size functions.
        virtual void set_size( int width, int height );
        virtual int get_width( void ) const;
        virtual int get_height( void ) const;

    private:

        float x_;
        float y_;
        int width_;
        int height_;
        GLubyte alpha_;

    };

}

#endif // COMPONENT_HPP
