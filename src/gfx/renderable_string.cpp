#include "jui/gfx/renderable_string.hpp"

namespace JUI
{

    /*
     * Renderable string constructor for length.
     */
    RenderableString::RenderableString( size_t length )
    {
        length_ = length;
    }

    /*
     * Get renderable string length.
     */
    size_t RenderableString::get_length( void ) const
    {
        return length_;
    }

}
