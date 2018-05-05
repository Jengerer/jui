#ifndef RENDERABLE_STRING_INTERFACE_HPP
#define RENDERABLE_STRING_INTERFACE_HPP

namespace JUI
{

	/*
	 * Interface for rendering a generic string.
	 */
	class RenderableStringInterface
	{

	public:

		virtual unsigned long get_character_code( size_t index ) const = 0;
		virtual size_t get_length( void ) const = 0;

	};

}

#endif // RENDERABLE_STRING_INTERFACE_HPP