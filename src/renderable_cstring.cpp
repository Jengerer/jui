#include "jui/renderable_cstring.h"

RenderableCString::RenderableCString( const char* str, size_t length ) : RenderableString( length )
{
	str_ = str;
}

unsigned long RenderableCString::char_code_at( size_t index ) const
{
	return static_cast<unsigned long>(str_[index]);
}