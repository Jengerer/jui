#include "jui/gfx/opengl_shared.hpp"

namespace JUI
{

	/*
	 * Return lowest power of 2 larger than num.
	 */
	GLsizei OpenGLShared::next_power_of_2( GLsizei num )
	{
		GLsizei result = 1;
		while (result < num) {
			result <<= 1;
		}

		return result;
	}

}
