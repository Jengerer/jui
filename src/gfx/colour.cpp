#include "jui/gfx/colour.hpp"
#include <math.h>

namespace JUI
{

	Colour::Colour( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha )
	{
		set_alpha( alpha );
		set_red( red );
		set_green( green );
		set_blue( blue );
	}

	GLubyte Colour::get_alpha( void ) const
	{
		return alpha_;
	}

	GLubyte Colour::get_red( void ) const
	{
		return red_;
	}

	GLubyte Colour::get_green( void ) const
	{
		return green_;
	}

	GLubyte Colour::get_blue( void ) const
	{
		return blue_;
	}

	double Colour::get_hue( void ) const
	{
		double red = static_cast<double>(red_);
		double green = static_cast<double>(green_);
		double blue = static_cast<double>(blue_);
		double max_channel = max( max( red, green ), blue );
		double min_channel = min( min( red, green ), blue );
		if( max_channel == min_channel ){
			return 0;
		}
		if( max_channel == red ){
			return fmod(((green - blue) / (max_channel - min_channel)), 6) * HUE_SCALING;
		}
		if( max_channel == green_ ){
			return (((blue - red) / (max_channel - min_channel)) + 2) * HUE_SCALING;
		}
		return (((red - green) / (max_channel - min_channel)) + 4) * HUE_SCALING;
	}

	double Colour::get_saturation( void ) const
	{
		double red = static_cast<double>(red_);
		double green = static_cast<double>(green_);
		double blue = static_cast<double>(blue_);
		double max_channel = max( max( red, green ), blue );
		double min_channel = min( min( red, green ), blue );
		return (max_channel - min_channel) / max_channel;
	}

	double Colour::get_value( void ) const
	{
		double red = static_cast<double>(red_);
		double green = static_cast<double>(green_);
		double blue = static_cast<double>(blue_);
		double max_channel = max( max( red, green ), blue );
		return max_channel / COMPONENT_MAX;
	}

	void Colour::set_alpha( GLubyte alpha )
	{
		alpha_ = alpha;
	}

	void Colour::set_red( GLubyte red )
	{
		red_ = red;
	}

	void Colour::set_green( GLubyte green )
	{
		green_ = green;
	}

	void Colour::set_blue( GLubyte blue )
	{
		blue_ = blue;
	}

	bool Colour::set_hue( double hue )
	{
		return set_hsv( hue, get_saturation(), get_value() );
	}

	bool Colour::set_saturation( double saturation )
	{
		return set_hsv( get_hue(), saturation, get_value() );
	}

	bool Colour::set_value( double value )
	{
		return set_hsv( get_hue(), get_saturation(), value );
	}

	bool Colour::set_hsv( double hue, double saturation, double value )
	{
		if( hue < HUE_MIN || saturation < SATURATION_MIN || value < VALUE_MIN ) {
			return false;
		}
		if( hue >= HUE_MAX || saturation > SATURATION_MAX || value > VALUE_MAX ) {
			return false;
		}
		double red, green, blue;
		double max_channel = value;
		double middle_channel = value * ((saturation * (1 - abs(fmod((hue / HUE_SCALING), 2) - 1))) + 1 - saturation);
		double min_channel = value * (1 - saturation);
		if( hue < 1 * HUE_SCALING ){
			red = max_channel;
			green = middle_channel;
			blue = min_channel;
		}else if( hue < 2 * HUE_SCALING ){
			green = max_channel;
			red = middle_channel;
			blue = min_channel;
		}else if( hue < 3 * HUE_SCALING ){
			green = max_channel;
			blue = middle_channel;
			red = min_channel;
		}else if( hue < 4 * HUE_SCALING ){
			blue = max_channel;
			green = middle_channel;
			red = min_channel;
		}else if( hue < 5 * HUE_SCALING ){
			blue = max_channel;
			red = middle_channel;
			green = min_channel;
		}else{
			red = max_channel;
			blue = middle_channel;
			green = min_channel;
		}
		set_red( static_cast<GLubyte>(floor(red * COMPONENT_MAX) + 0.5) );
		set_green( static_cast<GLubyte>(floor(green * COMPONENT_MAX) + 0.5) );
		set_blue( static_cast<GLubyte>(floor(blue * COMPONENT_MAX) + 0.5) );
		return true;
	}
}