#ifndef RENDERABLE_WIDE_STRING_HPP
#define RENDERABLE_WIDE_STRING_HPP

#include "jui/renderable_string.hpp"

namespace JUI
{

    class RenderableWideString : public RenderableString
    {

    public:

        RenderableWideString( const wchar_t* wstr, size_t length );

        // Get character code.
        unsigned long char_code_at( size_t index ) const;

    private:

        const wchar_t* wstr_;

    };

}

#endif // RENDERABLE_WIDE_STRING_HPP
