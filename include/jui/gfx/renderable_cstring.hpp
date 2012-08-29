#ifndef RENDERABLE_CSTRING_HPP
#define RENDERABLE_CSTRING_HPP

#include "jui/renderable_string.hpp"

namespace JUI
{

    class RenderableCString : public RenderableString
    {

    public:

        RenderableCString( const char* str, size_t length );

        // Get character code.
        unsigned long char_code_at( size_t index ) const;

    private:

        const char* str_;
        size_t length;

    };

}

#endif // RENDERABLE_CSTRING_HPP
