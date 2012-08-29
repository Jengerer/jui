#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include "jui/gfx/graphics_2d.hpp"

namespace JUI
{

    class IDrawable
    {

    public:

        virtual void draw( Graphics2D* graphics ) = 0;

    };

}

#endif // IDRAWABLE_HPP
