#ifndef WRAPPED_TEXT_HPP
#define WRAPPED_TEXT_HPP

#include "jui/gfx/text.hpp"

namespace JUI
{

    class WrappedText : public Text
    {

    public:

        __declspec(dllexport) WrappedText( FontInterface *font, int text_width );
        __declspec(dllexport) virtual ~WrappedText( void );

        __declspec(dllexport) virtual void pack( RenderableString* render_string );

        __declspec(dllexport) int get_text_width( void ) const;
        __declspec(dllexport) void set_text_width( int text_width );

        __declspec(dllexport) DWORD	get_text_formatting( void ) const;
        __declspec(dllexport) void set_text_formatting( DWORD formatting );

    private:

        int		text_width_;
        DWORD	formatting_;

    };

}

#endif // WRAPPED_TEXT_HPP
