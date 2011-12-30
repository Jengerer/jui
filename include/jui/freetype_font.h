#ifndef FREETYPE_FONT_H
#define FREETYPE_FONT_H

#include <stdexcept>

#include "jui/ifont.h"
#include "jui/renderable_string.h"
#include "jui/opengl_shared.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

class FreetypeFont : public IFont
{

public:

	// Constructor.
	FreetypeFont( FT_Face face );

	// Destructor.
	~FreetypeFont();

	// Generate font glyphs.
	void generate_glyphs();

	// Create glyph display lists.
	void create_display_lists();

	// Draw character.
	void draw_char( unsigned long c ) const;

	// Jump to next line.
	void new_line() const;

	// Get width of character.
	FT_Pos get_char_width( unsigned long c ) const;

	// Get width of string.
	FT_Pos get_string_width( const RenderableString* text, size_t start, size_t end ) const;

	// Draw measured renderable string.
	void draw( RECT* rect, const RenderableString* text, size_t start, size_t end ) const;

	// Draw aligned renderable string.
	void draw_aligned( const RenderableString* text, size_t start, size_t end, float width, TextHorizontalAlignType align_type ) const;

	// Prepare draw list for wrapped string.
	void draw_wrapped( RECT* bounds, const RenderableString* text, TextHorizontalAlignType align_type ) const;

	// Get height of line.
	GLsizei get_line_height() const;

	// Get height between line bases.
	GLsizei get_baseline_spacing() const;

private:

	// Font face handle.
	FT_Face		face_;

	// Array of textures.
	GLuint*		textures_;

	// Display lists for characters.
	GLuint		list_;

	// Advances for characters.
	FT_Pos*		advances_;
	
};

#endif // FONT_H