#ifndef CROPPED_IMAGE_HPP
#define CROPPED_IMAGE_HPP

#include "jui/gfx/image.hpp"

namespace JUI
{

	/*
	 * Component for drawing a single image.
	 */
	class __declspec(dllexport) CroppedImage: public Image
	{

	public:

		CroppedImage( const Texture* texture );
		CroppedImage( const Texture* texture, int x, int y );
		CroppedImage( const Texture* texture, int x, int y, int cropped_x, int cropped_y, int cropped_width, int cropped_height );

		void set_cropped( int x, int y, int width, int height );

		int get_cropped_x( void ) const;
		int get_cropped_y( void ) const;
		int get_cropped_width( void ) const;
		int get_cropped_height( void ) const;

		// Drawing functions.
		virtual void draw( Graphics2D* graphics );

	private:

		int cropped_x_;
		int cropped_y_;
		int cropped_width_;
		int cropped_height_;

	};

}

#endif // CROPPED_IMAGE_HPP
