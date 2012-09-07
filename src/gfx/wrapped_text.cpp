#include "jui/gfx/wrapped_text.hpp"
#include "jui/gfx/renderable_cstring.hpp"

namespace JUI
{

    WrappedText::WrappedText( FontInterface *font, int text_width ) : Text( font )
    {
        set_text_formatting( 0 );
        set_text_width( text_width );
    }

    WrappedText::~WrappedText( void )
    {
        // Wrapped text destroyed.
    }

    void WrappedText::pack( void )
    {	
        if (str_ != nullptr) {
            // Wrap renderable string.
            RECT bounds = { 0, 0, get_text_width(), 0 };

            // Draw to list.
            glNewList( list_, GL_COMPILE );
            font_->draw_wrapped( &bounds, str_, TEXT_ALIGN_CENTER );
            glEndList();

            // Set text size.
            set_size( get_text_width(), bounds.bottom - bounds.top );

            // Delete renderable string.
            delete str_;
            str_ = nullptr;
        }
        else {
            set_size( 0, 0 );
        }
    }

    int WrappedText::get_text_width( void ) const
    {
        return textWidth_;
    }

    void WrappedText::set_text_width( int text_width )
    {
        textWidth_ = text_width;
    }

    DWORD WrappedText::get_text_formatting( void ) const
    {
        return formatting_;
    }

    void WrappedText::set_text_formatting( DWORD formatting )
    {
        formatting_ = formatting;
    }

}
