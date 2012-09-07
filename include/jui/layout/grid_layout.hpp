#ifndef GRID_LAYOUT_HPP
#define GRID_LAYOUT_HPP

#include "jui/layout/layout.hpp"

namespace JUI
{

    /*
     * Layout that inserts equally sized elements into a grid format
     * given a certain number of elements per row.
     */
    class __declspec(dllexport) GridLayout : public Layout
    {

    public:

        GridLayout( int grid_width, unsigned int spacing );
        virtual ~GridLayout( void );

        // Layout packing.
        virtual void pack( void );

    private:

        int grid_width_;

    };

}

#endif // GRID_LAYOUT_HPP
