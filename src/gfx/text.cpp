#include "jui/gfx/base_renderable_string.hpp"
#include "jui/gfx/text.hpp"

namespace JUI
{

	/*
	 * Text constructor.
	 */
	Text::Text( FontInterface *font )
	{
		set_font( font );
		set_colour( &COLOUR_WHITE );
		list_ = glGenLists( 1 );
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
	void Text::set_text( const JUTIL::String* text )
	{
		// Set renderable string.
		RenderableString render_string( text );
		pack( &render_string );
	}

	/*
	 * Set new displayed wchar text.
	 */
	void Text::set_text( const JUTIL::WideString* text )
	{
		// Set renderable wide string and pack.
		RenderableWideString render_string( text );
		pack( &render_string );
	}

	/*
	 * Set text colour.
	 */
	void Text::set_colour( const Colour* colour )
	{
		colour_.set_red( colour->get_red() );
		colour_.set_green( colour->get_green() );
		colour_.set_blue( colour->get_blue() );
	}

	/*
	 * Get text colour.
	 */
	const Colour* Text::get_colour( void ) const
	{
		return &colour_;
	}

	/*
	 * Set text alpha.
	 */
	void Text::set_alpha( int alpha )
	{
		Component::set_alpha( alpha );
		colour_.set_alpha( get_alpha() );
	}

	/*
	 * Draw text to screen.
	 */
	void Text::draw( Graphics2D* graphics )
	{
		graphics->push_matrix();
		graphics->translate( get_x(), get_y() );
		graphics->set_colour( &colour_ );
		glCallList( list_ );
		graphics->pop_matrix();
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
	void Text::pack( RenderableStringInterface* render_string )
	{
		// Pack on renderable string size.
		RECT size;

		// Draw to list.
		glNewList( list_, GL_COMPILE );
		font_->draw( &size, render_string, 0, render_string->get_length() );
		glEndList();

		// Set component size.
		set_size( size.right, size.bottom );
	}

}
