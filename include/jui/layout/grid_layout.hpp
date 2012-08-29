#ifndef GRID_LAYOUT_HPP
#define GRID_LAYOUT_HPP

#include "jui/layout/layout.hpp"

namespace JUI
{

    class GridLayout : public Layout
    {

    public:

        __declspec(dllexport) GridLayout( int gridWidth, unsigned int spacing );
        __declspec(dllexport) virtual ~GridLayout( void );

        __declspec(dllexport) virtual void pack( void );

    private:

        int gridWidth_;

    };

}

#endif // GRID_LAYOUT_HPP
