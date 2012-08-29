#include "jui/gfx/renderable_string.hpp"

namespace JUI
{

    RenderableString::RenderableString( size_t length )
    {
        length_ = length;
    }

    size_t RenderableString::length() const
    {
        return length_;
    }

}
