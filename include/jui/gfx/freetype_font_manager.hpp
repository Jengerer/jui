#ifndef FREETYPE_FONT_MANAGER_HPP
#define FREETYPE_FONT_MANAGER_HPP

#include "jui/gfx/freetype_font.hpp"
#include "jui/gfx/ifont.hpp"

#include <string>
#include <vector>

/*
 * Freetype font object manager.
 */
class FreetypeFontManager
{

public:

	// Get singleton instance.
	static FreetypeFontManager* get_instance();

	// Destroy singleton instance.
	static void shut_down();

	// Get a font by file and size.
	IFont* create_font( const std::string& filename, unsigned int height );

	// Destroy a font instance.
	void destroy_font( IFont* font );

private:

	// Private constructor/destructor.
	FreetypeFontManager();
	~FreetypeFontManager();

	// Interface initializer.
	void initialize();
	void close();

private:

	// Singleton instance.
	static FreetypeFontManager* instance_;

private:

	// Singleton member variables.
	FT_Library library_;
	std::vector<FreetypeFont*> fonts_;

};

#endif // FREETYPE_FONT_MANAGER_HPP
