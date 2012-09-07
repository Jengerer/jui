#ifndef TEXT_HPP
#define TEXT_HPP

#include "jui/layout/component.hpp"
#include "jui/gfx/font_interface.hpp"

namespace JUI
{

    class Text : public Component
    {

    public:

        __declspec(dllexport) Text( FontInterface *font );
        __declspec(dllexport) virtual ~Text( void );

        __declspec(dllexport) virtual void draw( Graphics2D* graphics );

        __declspec(dllexport) void set_text( const std::string& text );
        __declspec(dllexport) void set_text( const wchar_t* text, size_t length );
        __declspec(dllexport) void set_colour( const Colour& colour );
        __declspec(dllexport) const Colour& get_colour( void ) const;
        __declspec(dllexport) virtual void set_alpha( int alpha );

        // Drawing functions.
        __declspec(dllexport) virtual void pack( void );

    private:

        FontInterface*			get_font( void ) const;
        void			set_font( FontInterface *font );

    protected:

        FontInterface		*font_;
        RenderableString* str_;
        GLuint		list_;

    private:

        Colour colour_;

    };

}

#endif // TEXT_HPP
