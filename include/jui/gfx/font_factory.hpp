#ifndef FREETYPE_FONT_FACTORY_HPP
#define FREETYPE_FONT_FACTORY_HPP

#include "jui/gfx/font_interface.hpp"
#include <string/constant_string.hpp>

namespace JUI
{

    class FontFactory
    {

    public:

	    // Loading and handling fonts.
	    static __declspec(dllexport) FontInterface* create_font( const JUTIL::ConstantString& file_name, unsigned int height );
	    static __declspec(dllexport) void destroy_font( FontInterface* font );
	    static __declspec(dllexport) void shut_down( void );

    };

}

#endif // FONT_FACTORY_HPP
