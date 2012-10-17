#ifndef TEXT_HPP
#define TEXT_HPP

#include "jui/layout/component.hpp"
#include "jui/gfx/font_interface.hpp"
#include <string/constant_string.hpp>
#include <string/constant_wide_string.hpp>

namespace JUI
{

    class __declspec(dllexport) Text : public Component
    {

    public:

        Text( FontInterface *font );
        virtual ~Text( void );

        virtual void draw( Graphics2D* graphics );

        void set_text( const JUTIL::String* string );
        void set_text( const JUTIL::WideString* string );
        void set_colour( const Colour* colour );
        const Colour* get_colour( void ) const;
        virtual void set_alpha( int alpha );

    private:

        virtual void pack( RenderableStringInterface* render_string );
        FontInterface* get_font( void ) const;
        void set_font( FontInterface *font );

    protected:

        FontInterface		*font_;
        GLuint		        list_;

    private:

        Colour colour_;

    };

}

#endif // TEXT_HPP
