#include "jui/gfx/box.hpp"

namespace JUI
{

    /*
     * Box component constructor.
     */
    Box::Box( void )
    {
        colour_ = Colour( 255, 125, 0, 255 );
    }

    /*
     * Draw the box.
     */
    void Box::draw( Graphics2D* graphics )
    {
        graphics->set_colour( colour_ );

        // Draw rectangle over bounds.
        int x = get_x();
        int y = get_y();
        int width = get_width();
        int height = get_height();
        graphics->draw_rectangle( x, y, width, height );
    }

}
