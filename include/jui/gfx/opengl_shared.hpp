#ifndef OPENGL_SHARED_HPP
#define OPENGL_SHARED_HPP

#include <stdlib.h>
#include <windows.h>
#include <gl/GLee.h>
#include <gl/gl.h>
#include <gl/glu.h>

namespace JUI
{

    /*
     * Generic function used by OpenGL.
     */
    class OpenGLShared
    {

    public:

        static GLsizei next_power_of_2( GLsizei num );

    };

}

#endif // OPENGL_SHARED_HPP
