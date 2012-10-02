#include "jui/gfx/renderable_cstring.hpp"

namespace JUI
{

    /*
     * Renderable C string by constant string constructor.
     */
    RenderableCString::RenderableCString( const JUTIL::ConstantString& string ) : RenderableString( string.get_length() )
    {
        string_.set_string( &string );
    }

    /*
     * Get character at string index.
     */
    unsigned long RenderableCString::char_code_at( size_t index ) const
    {
        const char* string = string_.get_string();
        return static_cast<unsigned long>(string[index]);
    }

}
