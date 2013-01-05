#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "jui/layout/component.hpp"

namespace JUI
{

	/*
	 * Component for drawing a single image.
	 */
	class __declspec(dllexport) Image: public Component
	{

	public:

		Image( const Texture* texture );
		Image( const Texture* texture, int x, int y );

		// Drawing functions.
		virtual void draw( Graphics2D* graphics );
		void set_texture( const Texture *texture );

		// Imagine rendering attributes.
		void set_alpha( int alpha );
		void set_tint( const Colour* tint );
		const Colour* get_tint( void ) const;

	private:

		const Texture *texture_;
		Colour tint_;

	};

}

#endif // IMAGE_HPP
