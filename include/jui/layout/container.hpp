#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "jui/layout/component.hpp"
#include <containers/vector.hpp>

namespace JUI
{

    class __declspec(dllexport) Container : public Component
    {

    public:

        // Container constructor.
        Container( void );
        Container( int x, int y );

        // Container destructor.
        virtual ~Container( void );

        // Container resource handling.
        virtual bool add( Component *component );
        virtual void remove( Component *component );

        // Drawing functions.
        virtual void draw( Graphics2D* graphics );
        virtual void set_alpha( int alpha );

        // Local/global child position handling.
        void clamp_child( Component *child, int padding = 0.0f ) const;
        virtual bool is_visible( Component* child ) const;
        virtual bool is_within_bounds( Component* child ) const;

    protected:

        JUTIL::Vector<Component*> components_;

    };

}

#endif // CONTAINER_HPP
