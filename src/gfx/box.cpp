#include "jui/gfx/box.hpp"

namespace JUI
{

    /*
     * Box component constructor.
     */
    Box::Box()
    {
        colour_ = Colour( 255, 125, 0, 255 );
    }

    /*
     * Draw the box.
     */
    void Box::draw( Graphics2D* graphics )
    {
        graphics->set_colour( colour_ );
        graphics->draw_rectangle( get_x(), get_y(), static_cast<float>(get_width()), static_cast<float>(get_height()) );
    }

}
