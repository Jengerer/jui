#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "jui/jui_base.hpp"
#include "jui/gfx/idrawable.hpp"

namespace JUI
{

	class JUI_API Component : public IDrawable
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
		void set_alpha( float alpha );
		float get_alpha( void ) const;

		// Size functions.
		virtual void set_size( int width, int height );
		virtual int get_width( void ) const;
		virtual int get_height( void ) const;

	private:

		int x_;
		int y_;
		int width_;
		int height_;
		float alpha_;

	};

}

#endif // COMPONENT_HPP
