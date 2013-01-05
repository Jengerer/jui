#include "jui/gfx/wrapped_text.hpp"
#include "jui/gfx/renderable_string_interface.hpp"

namespace JUI
{

	/*
	 * Wrapped text constructor.
	 */
	WrappedText::WrappedText( FontInterface *font, int text_width ) : Text( font )
	{
		set_text_formatting( 0 );
		set_text_width( text_width );
	}

	/*
	 * Wrapped text destructor.
	 */
	WrappedText::~WrappedText( void )
	{
		// Wrapped text destroyed.
	}

	/*
	 * Pack and align wrapped text.
	 */
	void WrappedText::pack( RenderableStringInterface* render_string )
	{	
		// Wrap renderable string.
		RECT bounds = { 0, 0, get_text_width(), 0 };

		// Draw to list.
		glNewList( list_, GL_COMPILE );
		font_->draw_wrapped( &bounds, render_string, TEXT_ALIGN_CENTER );
		glEndList();

		// Set text size.
		set_size( get_text_width(), bounds.bottom - bounds.top );
	}

	/*
	 * Get wrap width of text.
	 */
	int WrappedText::get_text_width( void ) const
	{
		return text_width_;
	}

	/*
	 * Set wrap width of text.
	 */
	void WrappedText::set_text_width( int text_width )
	{
		text_width_ = text_width;
	}

	/*
	 * Get text formatting flags.
	 */
	DWORD WrappedText::get_text_formatting( void ) const
	{
		return formatting_;
	}

	/*
	 * Set text formatting flags.
	 */
	void WrappedText::set_text_formatting( DWORD formatting )
	{
		formatting_ = formatting;
	}

}
