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

        __declspec(dllexport) virtual void pack();
        __declspec(dllexport) void add_left( Component* component );
        __declspec(dllexport) void add_right( Component* component );

    private:

        HorizontalLayout* left_;
        HorizontalLayout* right_;

    };

}

#endif // HORIZONTAL_SPLIT_CONTAINER_HPP
