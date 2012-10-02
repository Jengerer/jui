#ifndef RENDERABLE_CSTRING_HPP
#define RENDERABLE_CSTRING_HPP

#include "jui/gfx/renderable_string.hpp"
#include <string/constant_string.hpp>

namespace JUI
{

    /*
     * Renderable string for a C-style string representation.
     */
    class RenderableCString : public RenderableString
    {

    public:

        RenderableCString( const JUTIL::ConstantString& string );

        // String index getter.
        virtual unsigned long char_code_at( size_t index ) const;

    private:

        JUTIL::ConstantString string_;

    };

}

#endif // RENDERABLE_CSTRING_HPP
