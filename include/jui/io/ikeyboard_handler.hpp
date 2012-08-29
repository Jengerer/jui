#ifndef IKEYBOARD_HANDLER_HPP
#define IKEYBOARD_HANDLER_HPP

namespace JUI
{

    class IKeyboardHandler
    {

    public:

        virtual bool on_key_pressed( int key ) = 0;
        virtual bool on_key_released( int key ) = 0;

    };

}

#endif // IKEYBOARD_HANDLER_HPP
