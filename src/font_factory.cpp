#include "jui/font_factory.h"
#include "jui/freetype_font_manager.h"

/*
 * Get font interface.
 */
IFont* FontFactory::create_font( const std::string& filename, unsigned int height )
{
	// Get font from freetype manager.
	FreetypeFontManager* manager = FreetypeFontManager::get_instance();
	return manager->create_font( filename, height );
}

/*
 * Release font interface.
 */
void FontFactory::destroy_font( IFont* font )
{
	// Destroy font in freetype manager.
	FreetypeFontManager* manager = FreetypeFontManager::get_instance();
	manager->destroy_font( font );
}

/*
 * Close interfaces.
 */
void FontFactory::shut_down()
{
	FreetypeFontManager::shut_down();
}