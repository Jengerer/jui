#ifndef HORIZONTAL_SPLIT_CONTAINER_HPP
#define HORIZONTAL_SPLIT_CONTAINER_HPP

#include "jui/layout/layout.hpp"
#include "jui/layout/horizontal_layout.hpp"

namespace JUI
{

    class HorizontalSplitLayout: public Layout
    {

    public:

        __declspec(dllexport) HorizontalSplitLayout( int width, unsigned int spacing = 0 );

        // Over-write reserve function for left and right.
        virtual bool reserve( void );

        // Layout packing functions.
        __declspec(dllexport) virtual void pack( void );
        __declspec(dllexport) bool add_left( Component* component );
        __declspec(dllexport) bool add_right( Component* component );

    private:

        // Layout functions.
        unsigned int spacing_;
        HorizontalLayout* left_;
        HorizontalLayout* right_;

    };

}

#endif // HORIZONTAL_SPLIT_CONTAINER_HPP
