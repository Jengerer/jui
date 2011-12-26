#ifndef FONT_FACTORY_H
#define FONT_FACTORY_H

#include "jui/font.h"

#include <string>

class FontFactory
{

public:

	static __declspec(dllexport) void initialize();
	static __declspec(dllexport) void shut_down();

	// Loading and handling fonts.
	static Font* create_font( const std::string& filename, FT_F26Dot6 height );

private:

	static FT_Library library_;

};

#endif // FONT_FACTOR_H