#ifndef FONT_INTERFACE_HPP
#define FONT_INTERFACE_HPP

#include "jui/gfx/graphics_2d.hpp"
#include "jui/gfx/renderable_string.hpp"

namespace JUI
{

    // Horizontal align specifiers.
    enum TextHorizontalAlignType {
        TEXT_ALIGN_LEFT,
        TEXT_ALIGN_CENTER,
        TEXT_ALIGN_RIGHT
    };

    /*
     * Font abstraction class.
     */
    class FontInterface
    {

    public:

        // Releasing font handle.
        virtual bool initialize( void ) = 0;
        virtual void release( void ) = 0;

        // Drawing functions.
        virtual void draw_char( unsigned long c ) const = 0;
        virtual void new_line( void ) const = 0;
        virtual void draw( RECT* rect, const RenderableString* text, size_t start, size_t end ) const = 0;
        virtual void draw_aligned( const RenderableString* text, size_t start, size_t end, float width, TextHorizontalAlignType align_type ) const = 0;
        virtual void draw_wrapped( RECT* rect, const RenderableString* text, TextHorizontalAlignType align_type ) const = 0;

    };

}

#endif // FONT_INTERFACE_HPP
