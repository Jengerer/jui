#ifndef RENDERABLE_WIDE_STRING_HPP
#define RENDERABLE_WIDE_STRING_HPP

#include "jui/gfx/renderable_string.hpp"
#include <string/constant_wide_string.hpp>

namespace JUI
{

    /*
     * Renderable string for a wide-character representation.
     */
    class RenderableWideString : public RenderableString
    {

    public:

        RenderableWideString( const JUTIL::ConstantWideString& string );

        // Get character code.
        unsigned long char_code_at( size_t index ) const;

    private:

        JUTIL::ConstantWideString string_;

    };

}

#endif // RENDERABLE_WIDE_STRING_HPP
