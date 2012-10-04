#ifndef MOUSE_HANDLER_HPP
#define MOUSE_HANDLER_HPP

#include "jui/io/mouse.hpp"

namespace JUI
{

    /*
     * Interface to handle mouse events.
     */
    class MouseHandlerInterface
    {

    public:

        virtual bool on_mouse_clicked( Mouse *mouse ) = 0;
        virtual bool on_mouse_released( Mouse *mouse ) = 0;
        virtual bool on_mouse_moved( Mouse *mouse ) = 0;

    };

}

#endif // MOUSE_HANDLER_HPP
