#include "jui/gfx/font_factory.hpp"
#include "jui/gfx/freetype_font_manager.hpp"

namespace JUI
{

    /*
     * Get font interface.
     */
    FontInterface* FontFactory::create_font( const JUTIL::String* file_name, unsigned int height )
    {
        // Get font from freetype manager.
        FreetypeFontManager* manager = FreetypeFontManager::get_instance();
        return manager->create_font( file_name, height );
    }

    /*
     * Release font interface.
     */
    void FontFactory::destroy_font( FontInterface* font )
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

}
