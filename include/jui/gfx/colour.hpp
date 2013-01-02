#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "jui/gfx/opengl_shared.hpp"

namespace JUI
{

    // Alpha constants.
    const GLubyte COMPONENT_MIN = 0;
    const GLubyte COMPONENT_MAX = 255;

	const double HUE_MIN = 0;
    const double HUE_MAX = 360;// Not include 360
	const double SATURATION_MIN = 0;
    const double SATURATION_MAX = 1;
	const double VALUE_MIN = 0;
    const double VALUE_MAX = 1;

	const double HUE_SCALING = 60;

    // Colour struct.
    class __declspec(dllexport) Colour
    {

    public:

        Colour( GLubyte red = COMPONENT_MAX, 
            GLubyte green = COMPONENT_MAX,
            GLubyte blue = COMPONENT_MAX, 
            GLubyte alpha = COMPONENT_MAX );

    public:

		// Getters
		GLubyte get_alpha( void ) const;

		GLubyte get_red( void ) const;
		GLubyte get_green( void ) const;
		GLubyte get_blue( void ) const;

		double get_hue( void ) const;
		double get_saturation( void ) const;
		double get_value( void ) const;

		// Setters
		void set_alpha( GLubyte alpha );

		void set_red( GLubyte red );
		void set_green( GLubyte green );
		void set_blue( GLubyte blue );

		bool set_hue( double hue );
		bool set_saturation( double saturation );
		bool set_value( double value );
		bool set_hsv( double hue, double saturation, double value );

	private:

		GLubyte alpha_;
		GLubyte red_;
        GLubyte green_;
        GLubyte blue_;

    };

    // Useful colours.
    const Colour COLOUR_WHITE( COMPONENT_MAX, COMPONENT_MAX, COMPONENT_MAX );
    const Colour COLOUR_BLACK( COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MIN );
    const Colour COLOUR_BLANK( COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MIN );

}

#endif // COLOUR_HPP
