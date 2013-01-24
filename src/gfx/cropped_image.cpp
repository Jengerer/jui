#include "jui/gfx/cropped_image.hpp"

namespace JUI
{

	/*
	 * Image constructor from texture.
	 */
	CroppedImage::CroppedImage( const Texture* texture ): Image( texture )
	{
		set_cropped( 0, 0, 0, 0 );
	}

	/*
	 * Image constructor from texture and default position.
	 */
	CroppedImage::CroppedImage( const Texture* texture, int x, int y ): Image( texture, x, y )
	{
		set_cropped( 0, 0, 0, 0 );
	}

	/*
	 * Image constructor from texture and default position and cropped restriction.
	 */
	CroppedImage::CroppedImage( const Texture* texture, int x, int y,
		int cropped_x, int cropped_y, int cropped_width, int cropped_height ): Image( texture, x, y )
	{
		set_cropped( cropped_x, cropped_y, cropped_width, cropped_height );
	}

	/*
	 * Image drawing function.
	 */
	void CroppedImage::draw( Graphics2D* graphics )
	{
		// Draw texture.
		if (get_texture() != nullptr) {
			graphics->set_colour( *get_tint() );

			// Draw texture.
			int x = get_x();
			int y = get_y();
			int width = get_width();
			int height = get_height();
			graphics->draw_texture_restricted( get_texture(), x, y, width, height, cropped_x_, cropped_y_, cropped_width_, cropped_height_ );
		}
	}

	void CroppedImage::set_cropped( int x, int y, int width, int height )
	{
		cropped_x_ = x;
		cropped_y_ = y;
		cropped_width_ = width;
		cropped_height_ = height;
	}

	int CroppedImage::get_cropped_x( void ) const
	{
		return cropped_x_;
	}

	int CroppedImage::get_cropped_y( void ) const
	{
		return cropped_y_;
	}

	int CroppedImage::get_cropped_width( void ) const
	{
		return cropped_width_;
	}

	int CroppedImage::get_cropped_height( void ) const
	{
		return cropped_height_;
	}
}
