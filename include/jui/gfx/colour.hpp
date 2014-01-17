#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "jui/gfx/opengl_shared.hpp"

namespace JUI
{

	// Alpha constants.
	const float COMPONENT_MIN = 0.0f;
	const float COMPONENT_MAX = 1.0f;
	const float HUE_MIN = 0.0f;
	const float HUE_MAX = 360.0f; // Not include 360.
	const float SATURATION_MIN = 0.0f;
	const float SATURATION_MAX = 1.0f;
	const float VALUE_MIN = 0.0f;
	const float VALUE_MAX = 1.0f;
	const float HUE_SCALING = 60.0f;

	// Byte-vector colour component parameters.
	const unsigned int COLOUR_MASK_R = 0xFF0000;
	const unsigned int COLOUR_MASK_G = 0x00FF00;
	const unsigned int COLOUR_MASK_B = 0x0000FF;
	const unsigned int COLOUR_SHIFT_R = 16;
	const unsigned int COLOUR_SHIFT_G = 8;
	const unsigned int COLOUR_SHIFT_B = 0;
	const float MAX_BYTE = 255.0f;

	// Colour struct.
	class __declspec(dllexport) Colour
	{

	public:

		Colour( unsigned int rgb = 0, float a = 1.0f );
		Colour( float r, float g, float b, float a );

	public:

		// Component getters.
		float get_alpha( void ) const;
		float get_red( void ) const;
		float get_green( void ) const;
		float get_blue( void ) const;

		// Secondary colour attribute getters.
		float get_hue( void ) const;
		float get_saturation( void ) const;
		float get_value( void ) const;

		// Component setters.
		void set_alpha( float alpha );
		void set_red( float red );
		void set_green( float green );
		void set_blue( float blue );

		// Secondary colour attribute setters.
		bool set_hue( float hue );
		bool set_saturation( float saturation );
		bool set_value( float value );
		bool set_hsv( float hue, float saturation, float value );

	private:

		float alpha_;
		float red_;
		float green_;
		float blue_;

	};

	// Useful colours.
	const Colour COLOUR_WHITE( COMPONENT_MAX, COMPONENT_MAX, COMPONENT_MAX, COMPONENT_MAX );
	const Colour COLOUR_BLACK( COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MAX );
	const Colour COLOUR_BLANK( COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MIN );

}

#endif // COLOUR_HPP
