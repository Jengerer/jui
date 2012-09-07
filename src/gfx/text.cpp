#include "jui/gfx/renderable_cstring.hpp"
#include "jui/gfx/renderable_wide_string.hpp"
#include "jui/gfx/text.hpp"

namespace JUI
{

    /*
     * Text constructor.
     */
    Text::Text( FontInterface *font )
    {
        set_font( font );
        set_colour( COLOUR_WHITE );
        list_ = glGenLists( 1 );
        str_ = nullptr;
    }

    /*
     * Text destructor.
     */
    Text::~Text( void )
    {
        glDeleteLists( list_, 1 );
    }

    /*
     * Set new displayed text.
     */
    void Text::set_text( const std::string& text )
    {
        // Set renderable std::string and pack.
        str_ = new RenderableCString( text.c_str(), text.length() );
        pack();
    }

    /*
     * Set new displayed wchar text.
     */
    void Text::set_text( const wchar_t* text, size_t length )
    {
        // Set renderable wide std::string and pack.
        str_ = new RenderableWideString( text, length );
        pack();
    }

    /*
     * Set text colour.
     */
    void Text::set_colour( const Colour& colour )
    {
        colour_.r = colour.r;
        colour_.g = colour.g;
        colour_.b = colour.b;
    }

    /*
     * Get text colour.
     */
    const Colour& Text::get_colour( void ) const
    {
        return colour_;
    }

    /*
     * Set text alpha.
     */
    void Text::set_alpha( int alpha )
    {
        Component::set_alpha( alpha );
        colour_.a = get_alpha();
    }

    /*
     * Draw text to screen.
     */
    void Text::draw( Graphics2D* graphics )
    {
        glPushMatrix();
        glTranslatef( get_x(), get_y(), 0.0f );
        graphics->set_colour( colour_ );
        glCallList( list_ );
        glPopMatrix();
    }

    /*
     * Get font interface.
     */
    FontInterface* Text::get_font( void ) const
    {
        return font_;
    }

    /*
     * Set font interface.
     */
    void Text::set_font( FontInterface *font )
    {
        font_ = font;
    }

    /*
     * Pack text to size.
     */
    void Text::pack( void )
    {
        if (str_ != nullptr) {
            // Pack on renderable string size.
            RECT size;

            // Draw to list.
            glNewList( list_, GL_COMPILE );
            font_->draw( &size, str_, 0, str_->length() );
            glEndList();

            // Set component size.
            set_size( size.right, size.bottom );

            // Remove temporary renderable string.
            delete str_;
            str_ = nullptr;
        }
        else {
            set_size( 0, 0 );
        }
    }

}
