#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace JUI
{

    // Number of key codes.
    const size_t KEY_COUNT = 255;


    class Keyboard
    {

    public:

        __declspec(dllexport) Keyboard();
        
        // Keyboard state getters.
        __declspec(dllexport) bool is_key_pressed( int code ) const;
        
        // State updater.
        __declspec(dllexport) void set_key_state( int code, bool is_pressed );

        // Reset key states.
        __declspec(dllexport) void clear_states();

    private:

        // Stores key states.
        bool states_[ KEY_COUNT ];

    };

}

#endif // KEYBOARD_HPP
