#include "jui/gfx/colour.hpp"
#include <math.h>

namespace JUI
{
	/*
	 * Construct colour from integer value with each byte representing a component.
	 */
	Colour::Colour( unsigned int rgb, float a )
	{
		float r = static_cast<float>((rgb & COLOUR_MASK_R) >> COLOUR_SHIFT_R) / MAX_BYTE;
		float g = static_cast<float>((rgb & COLOUR_MASK_G) >> COLOUR_SHIFT_G) / MAX_BYTE;
		float b = static_cast<float>((rgb & COLOUR_MASK_B) >> COLOUR_SHIFT_B) / MAX_BYTE;
		set_red( r );
		set_green( g );
		set_blue( b );
		set_alpha( a );
	}

	/*
	 * Construct colour from normalized colour components.
	 */
	Colour::Colour( float r, float g, float b, float a )
	{
		set_red( r );
		set_green( g );
		set_blue( b );
		set_alpha( a );
	}

	/*
	 * Get red component.
	 */
	float Colour::get_red( void ) const
	{
		return red_;
	}

	/*
	 * Get green component.
	 */
	float Colour::get_green( void ) const
	{
		return green_;
	}

	/*
	 * Get blue component.
	 */
	float Colour::get_blue( void ) const
	{
		return blue_;
	}
	
	/*
	 * Get alpha component.
	 */
	float Colour::get_alpha( void ) const
	{
		return alpha_;
	}

	/*
	 * Set red component.
	 */
	void Colour::set_red( float red )
	{
		red_ = red;
	}

	/*
	 * Set green component.
	 */
	void Colour::set_green( float green )
	{
		green_ = green;
	}

	/*
	 * Set blue component.
	 */
	void Colour::set_blue( float blue )
	{
		blue_ = blue;
	}

	/*
	 * Set alpha component.
	 */
	void Colour::set_alpha( float alpha )
	{
		alpha_ = alpha;
	}

}