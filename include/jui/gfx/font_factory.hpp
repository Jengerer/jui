#ifndef FREETYPE_FONT_FACTORY_HPP
#define FREETYPE_FONT_FACTORY_HPP

#include "jui/gfx/ifont.hpp"
#include <string>

namespace JUI
{

    class FontFactory
    {

    public:

	    // Loading and handling fonts.
	    static __declspec(dllexport) IFont* create_font( const std::string& filename, unsigned int height );

	    // Destroy font.
	    static __declspec(dllexport) void destroy_font( IFont* font );

	    // Clean up interfaces.
	    static __declspec(dllexport) void shut_down();

    };

}

#endif // FONT_FACTOR_HPP
