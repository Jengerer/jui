#include "jui/layout/component.hpp"

namespace JUI
{

    /*
     * Component constructor.
     */
    Component::Component( float x, float y )
    {
        set_position( x, y );
        set_size( 0, 0 );
        set_alpha( 255 );
    }

    /*
     * Default component destructor.
     */
    Component::~Component( void )
    {
        // Component is destroyed.
    }

    /*
     * Default empty reservation for component.
     */
    bool Component::reserve( void )
    {
        return true;
    }

    /*
     * Set component position.
     */
    void Component::set_position( float x, float y )
    {
        x_ = x;
        y_ = y;
    }

    /*
     * Get component width.
     */
    int Component::get_width( void ) const
    {
        return width_;
    }

    /*
     * Get component height.
     */
    int Component::get_height( void ) const
    {
        return height_;
    }

    /*
     * Set both component width and height.
     */
    void Component::set_size( int width, int height )
    {
        width_ = width;
        height_ = height;
    }

    /*
     * Get component X position.
     */
    float Component::get_x( void ) const
    {
        return x_;
    }

    /*
     * Get component Y position.
     */
    float Component::get_y( void ) const
    {
        return y_;
    }

    /*
     * Set component alpha (clamping invalid values).
     */
    void Component::set_alpha( int alpha )
    {
        if (alpha > COMPONENT_MAX) {
            alpha_ = COMPONENT_MAX;
        }
        else if (alpha < COMPONENT_MIN) {
            alpha_ = COMPONENT_MIN;
        }
        else {
            alpha_ = static_cast<GLubyte>(alpha);
        }
    }

    /*
     * Get clamped component alpha.
     */
    GLubyte Component::get_alpha( void ) const
    {
        return alpha_;
    }

}
