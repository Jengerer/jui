#ifndef FREETYPE_FONT_FACTORY_HPP
#define FREETYPE_FONT_FACTORY_HPP

#include "jui/jui_base.hpp"
#include "jui/gfx/font_interface.hpp"
#include <string/constant_string.hpp>

namespace JUI
{

	class FontFactory
	{

	public:

		// Loading and handling fonts.
		static JUI_API FontInterface* create_font( const JUTIL::String* file_name, unsigned int height );
		static JUI_API void destroy_font( FontInterface* font );
		static JUI_API void shut_down( void );

	};

}

#endif // FONT_FACTORY_HPP
