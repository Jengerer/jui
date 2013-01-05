#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "jui/gfx/idrawable.hpp"

namespace JUI
{

	class __declspec(dllexport) Component : public IDrawable
	{

	public:

		Component( void );
		Component( int x, int y );
		virtual ~Component( void );

		// Position functions.
		virtual void set_position( int x, int y );
		
		// Position getters.
		virtual int get_x( void ) const;
		virtual int get_y( void ) const;

		// Visibility functions.
		virtual void set_alpha( int alpha ); // Using int to handle underflow.
		GLubyte get_alpha( void ) const;

		// Size functions.
		virtual void set_size( int width, int height );
		virtual int get_width( void ) const;
		virtual int get_height( void ) const;

	private:

		int x_;
		int y_;
		int width_;
		int height_;
		GLubyte alpha_;

	};

}

#endif // COMPONENT_HPP
