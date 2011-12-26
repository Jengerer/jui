#ifndef TEXT_H
#define TEXT_H

#include "jui/component.h"
#include "jui/font.h"

class Text : public Component
{

public:

	Text( Font *font );
	virtual ~Text( void );

	virtual void	draw( Graphics2D* graphics );

	void			SetText( const std::string& text );
	void			SetText( const wchar_t* text, size_t length );
	void			SetColour( const Colour& colour );
	const Colour&	GetColour( void ) const;
	virtual void	set_alpha( int alpha );

	// Drawing functions.
	Font*			GetFont( void ) const;
	void			SetFont( Font *font );
	virtual void	pack( void );

protected:

	Font		*font_;
	RenderableString* str_;
	GLuint		list_;

private:

	Colour colour_;

};

#endif // TEXT_H