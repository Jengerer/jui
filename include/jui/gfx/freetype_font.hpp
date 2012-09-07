#ifndef FREETYPE_FONT_HPP
#define FREETYPE_FONT_HPP

#include "jui/gfx/font_interface.hpp"
#include "jui/gfx/renderable_string.hpp"
#include "jui/gfx/opengl_shared.hpp"
#include <containers/vector.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace JUI
{

    class FreetypeFont : public FontInterface
    {

    public:

        // Return code for functions.
        enum ReturnStatus
        {
            Success = 0,
            LoadGlyphFailure,
            RenderGlyphFailure,
            NoMemoryFailure,
            GenerateListFailure,
        };

    public:

        FreetypeFont( FT_Face face );
        ~FreetypeFont( void );
        virtual bool initialize( void );
        virtual void release( void );

        // Font initialization.
        ReturnStatus generate_glyphs( void );
        ReturnStatus create_display_lists( void );

        // Font measurement functions.
        FT_Pos get_char_width( unsigned long c ) const;
        FT_Pos get_string_width( const RenderableString* text, size_t start, size_t end ) const;
        GLsizei get_line_height( void ) const;
        GLsizei get_baseline_spacing( void ) const;

        // Drawing functions for font interface.
        virtual void draw_char( unsigned long c ) const;
        virtual void new_line( void ) const;
        virtual void draw( RECT* rect, const RenderableString* text, size_t start, size_t end ) const;
        virtual void draw_aligned( const RenderableString* text, size_t start, size_t end, float width, TextHorizontalAlignType align_type ) const;
        virtual void draw_wrapped( RECT* bounds, const RenderableString* text, TextHorizontalAlignType align_type ) const;

    private:

        FT_Face face_;
        GLuint  list_;
        JUTIL::Vector<GLuint> textures_;
        JUTIL::Vector<FT_Pos> advances_;
        
    };

}

#endif // FONT_HPP
