#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "jui/gfx/opengl_shared.hpp"

namespace JUI
{

    // Alpha constants.
    const GLubyte COMPONENT_MIN = 0;
    const GLubyte COMPONENT_MAX = 255;

    // Colour struct.
    class __declspec(dllexport) Colour
    {

    public:

        Colour( GLubyte r = COMPONENT_MAX, 
            GLubyte g = COMPONENT_MAX,
            GLubyte b = COMPONENT_MAX, 
            GLubyte a = COMPONENT_MAX );

    public:

        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;

    };

    // Useful colours.
    const Colour COLOUR_WHITE( COMPONENT_MAX, COMPONENT_MAX, COMPONENT_MAX );
    const Colour COLOUR_BLACK( COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MIN );
    const Colour COLOUR_BLANK( COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MIN, COMPONENT_MIN );

}

#endif // COLOUR_HPP
