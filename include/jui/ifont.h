#ifndef IFONT_H
#define IFONT_H

#include "jui/graphics_2d.h"
#include "jui/renderable_string.h"

// Horizontal align specifiers.
enum TextHorizontalAlignType {
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
};

/*
 * Font interface.
 */
class IFont
{

public:

	// Draw characters.
	virtual void draw_char( unsigned long c ) const = 0;

	// Jump to next line.
	virtual void new_line( void ) const = 0;

	// Draw measured renderable string.
	virtual void draw( RECT* rect, const RenderableString* text, size_t start, size_t end ) const = 0;

	// Draw aligned renderable string.
	virtual void draw_aligned( const RenderableString* text, size_t start, size_t end, float width, TextHorizontalAlignType align_type ) const = 0;

	// Prepare draw list for wrapped string.
	virtual void draw_wrapped( RECT* rect, const RenderableString* text, TextHorizontalAlignType align_type ) const = 0;

};

#endif // IFONT_H