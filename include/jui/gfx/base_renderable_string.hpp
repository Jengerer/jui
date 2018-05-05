#ifndef BASE_RENDERABLE_STRING_HPP
#define BASE_RENDERABLE_STRING_HPP

#include <string/string.hpp>
#include "jui/gfx/renderable_string_interface.hpp"

namespace JUI
{

	/*
	 * Class for maintaining a generic renderable string.
	 */
	template <class Type>
	class BaseRenderableString : public RenderableStringInterface
	{

	public:

		BaseRenderableString( const Type* string );

		// String functions.
		unsigned long get_character_code( size_t index ) const;
		size_t get_length( void ) const;

	private:

		const Type* string_;

	};

	// Type definitions for common string types.
	typedef BaseRenderableString<JUTIL::String> RenderableString;
	typedef BaseRenderableString<JUTIL::WideString> RenderableWideString;

	/*
	 * Base renderable string constructor by base string pointer.
	 * Assumes string object lifetime exceeds time required to cache string drawing.
	 */
	template <class Type>
	BaseRenderableString<Type>::BaseRenderableString( const Type* string )
	{
		string_ = string;
	}

	/*
	 * Get the character code at an index.
	 */
	template <class Type>
	unsigned long BaseRenderableString<Type>::get_character_code( size_t index ) const
	{
		unsigned long character_code = static_cast<unsigned long>(string_->get_character( index ));
		return character_code;
	}

	/*
	 * Get length of string.
	 */
	template <class Type>
	size_t BaseRenderableString<Type>::get_length( void ) const
	{
		return string_->get_length();
	}

}

#endif // BASE_RENDERABLE_STRING_HPP
