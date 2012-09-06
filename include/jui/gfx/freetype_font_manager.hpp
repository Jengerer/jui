#ifndef FREETYPE_FONT_MANAGER_HPP
#define FREETYPE_FONT_MANAGER_HPP

#include "jui/gfx/freetype_font.hpp"
#include "jui/gfx/ifont.hpp"

#include <containers/vector.hpp>
#include <string/constant_string.hpp>

namespace JUI
{

    /*
     * Freetype font object manager.
     */
    class FreetypeFontManager
    {

    public:

	    // Get singleton instance.
	    static FreetypeFontManager* get_instance( void );

	    // Destroy singleton instance.
	    static void shut_down( void );

	    // Get a font by file and size.
	    IFont* create_font( const std::string& filename, unsigned int height );

	    // Destroy a font instance.
	    void destroy_font( IFont* font );

    private:

	    // Private constructor/destructor.
	    FreetypeFontManager( void );
	    ~FreetypeFontManager( void );

	    // Interface initializer.
	    void initialize( void );
	    void close( void );

    private:

	    // Singleton instance.
	    static FreetypeFontManager* instance_;

    private:

	    // Singleton member variables.
	    FT_Library library_;
	    JUTIL::Vector<FreetypeFont*> fonts_;

    };

}

#endif // FREETYPE_FONT_MANAGER_HPP
