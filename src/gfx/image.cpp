#include "jui/gfx/image.hpp"

namespace JUI
{

	/*
	 * Image constructor from texture.
	 */
	Image::Image( const Texture* texture )
	{
		set_texture( texture );
		set_tint( &COLOUR_WHITE );
	}

	/*
	 * Image constructor from texture and default position.
	 */
	Image::Image( const Texture* texture, int x, int y ): Component( x, y )
	{
		set_texture( texture );
		set_tint( &COLOUR_WHITE );
	}

	/*
	 * Image drawing function.
	 */
	void Image::draw( Graphics2D* graphics )
	{
		// Draw texture.
		if (texture_ != nullptr) {
			graphics->set_colour( tint_ );

			// Draw texture.
			int x = get_x();
			int y = get_y();
			int width = get_width();
			int height = get_height();
			graphics->draw_texture( texture_, x, y, width, height );
		}
	}

	/*
	 * Set alpha for this image.
	 */
	void Image::set_alpha( int alpha )
	{
		Component::set_alpha( alpha );
		tint_.set_alpha( get_alpha() );
	}

	/*
	 * Set tint for this image.
	 */
	void Image::set_tint( const Colour* tint )
	{
		tint_.set_red( tint->get_red() );
		tint_.set_green( tint->get_green() );
		tint_.set_blue( tint->get_blue() );
	}

	/*
	 * Get the tint for this image.
	 */
	const Colour* Image::get_tint( void ) const
	{
		return &tint_;
	}

	/*
	 * Set texture to draw as component.
	 */
	void Image::set_texture( const Texture *texture )
	{
		texture_ = texture;
	}

}
