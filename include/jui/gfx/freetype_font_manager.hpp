#ifndef FREETYPE_FONT_MANAGER_HPP
#define FREETYPE_FONT_MANAGER_HPP

#include "jui/gfx/freetype_font.hpp"
#include "jui/gfx/font_interface.hpp"

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

	    // Singleton instance manager.
	    static FreetypeFontManager* get_instance( void );
	    static void shut_down( void );

	    // Font creation and destruction.
	    FontInterface* create_font( const JUTIL::ConstantString& filename, unsigned int height );
	    void destroy_font( FontInterface* font );

    private:

	    // Private constructor/destructor.
	    FreetypeFontManager( void );
	    ~FreetypeFontManager( void );

	    // Interface initializer.
	    bool initialize( void );
	    void close( void );

    private:

	    // Singleton instance.
	    static FreetypeFontManager* instance_;

    private:

	    // Singleton member variables.
	    FT_Library library_;
	    JUTIL::Vector<FontInterface*> fonts_;

    };

}

#endif // FREETYPE_FONT_MANAGER_HPP
