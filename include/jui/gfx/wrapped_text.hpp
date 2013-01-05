#ifndef WRAPPED_TEXT_HPP
#define WRAPPED_TEXT_HPP

#include "jui/gfx/text.hpp"

namespace JUI
{

	class __declspec(dllexport) WrappedText : public Text
	{

	public:

		WrappedText( FontInterface *font, int text_width );
		virtual ~WrappedText( void );

		// Text packing function.
		virtual void pack( RenderableStringInterface* render_string );

		// Text width management.
		int get_text_width( void ) const;
		void set_text_width( int text_width );

		// Text formatting parameters.
		DWORD get_text_formatting( void ) const;
		void set_text_formatting( DWORD formatting );

	private:

		int     text_width_;
		DWORD   formatting_;

	};

}

#endif // WRAPPED_TEXT_HPP
