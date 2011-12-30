#ifndef TEXT_H
#define TEXT_H

#include "jui/component.h"
#include "jui/ifont.h"

class Text : public Component
{

public:

	__declspec(dllexport) Text( IFont *font );
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

	IFont*			get_font( void ) const;
	void			set_font( IFont *font );

protected:

	IFont		*font_;
	RenderableString* str_;
	GLuint		list_;

private:

	Colour colour_;

};

#endif // TEXT_H