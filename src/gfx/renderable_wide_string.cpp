#include "jui/gfx/renderable_wide_string.hpp"

namespace JUI
{

    /*
     * Renderable string constructor from constant wide string reference.
     */
    RenderableWideString::RenderableWideString( const JUTIL::ConstantWideString& string ) : RenderableString( string.get_length() )
    {
        string_.set_string( &string );
    }

    /*
     * Renderable wide string character indexing.
     */
    unsigned long RenderableWideString::char_code_at( size_t index ) const
    {
        const wchar_t* string = string_.get_string();
        return static_cast<unsigned long>(string[index]);
    }

}
