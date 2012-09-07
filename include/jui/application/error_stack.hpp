#ifndef ERROR_STACK_HPP
#define ERROR_STACK_HPP

#include <string/constant_string.hpp>
#include <containers/vector.hpp>

namespace JUI
{

    /*
     * Singleton class for managing error stack from components.
     */
    class ErrorStack
    {
    
    public:

        static ErrorStack* get_instance( void );
        static void shut_down( void );

        // Error logging functions.
        void log_error( const char* format, ... );

    private:

        JUTIL::Vector<JUTIL::String*> errors_;

    };

}

#endif // ERROR_STACK_HPP
