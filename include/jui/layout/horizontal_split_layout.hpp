#ifndef HORIZONTAL_SPLIT_CONTAINER_HPP
#define HORIZONTAL_SPLIT_CONTAINER_HPP

#include "jui/layout/layout.hpp"
#include "jui/layout/horizontal_layout.hpp"

namespace JUI
{

    class HorizontalSplitLayout: public Layout
    {

    public:

        // Over-write reserve function for left and right.
        static HorizontalSplitLayout* create( int width, int spacing );

        // Layout packing functions.
        __declspec(dllexport) virtual void pack( void );
        __declspec(dllexport) bool add_left( Component* component );
        __declspec(dllexport) bool add_right( Component* component );

    public:

        __declspec(dllexport) HorizontalSplitLayout( void );

    private:

        HorizontalLayout* left_;
        HorizontalLayout* right_;

    };

}

#endif // HORIZONTAL_SPLIT_CONTAINER_HPP
