#ifndef FREETYPE_FONT_FACTORY_HPP
#define FREETYPE_FONT_FACTORY_HPP

#include "jui/gfx/ifont.hpp"
#include <string/constant_string.hpp>

namespace JUI
{

    class FontFactory
    {

    public:

	    // Loading and handling fonts.
	    static __declspec(dllexport) IFont* create_font( const JUTIL::ConstantString& file_name, unsigned int height );

	    // Destroy font.
	    static __declspec(dllexport) void destroy_font( IFont* font );

	    // Clean up interfaces.
	    static __declspec(dllexport) void shut_down( void );

    };

}

#endif // FONT_FACTOR_HPP
