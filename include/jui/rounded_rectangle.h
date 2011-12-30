#ifndef ROUNDED_RECTANGLE_H
#define ROUNDED_RECTANGLE_H

#include "jui/component.h"

enum EStrokeType {
	STROKE_TYPE_OUTER,
	STROKE_TYPE_INNER,
	// STROKE_TYPE_MIDDLE
};

class RoundedRectangle : public Component
{

public:

	RoundedRectangle( int width, int height, int radius, const Colour& colour );
	virtual ~RoundedRectangle( void );

	virtual void	draw( Graphics2D* graphics );

	void			SetStroke( int size, const Colour& colour );
	void			set_stroke_type( EStrokeType strokeType );
	const Colour&	get_colour( void ) const;
	void			set_colour( const Colour& colour );
	virtual void	set_size( int width, int height );
	void			get_stroke_type( int radius );

	// TODO: Maybe make Generate protected, but a friend of IPrecachable.
	void			generate( Graphics2D* graphics );
	Texture*		get_texture( void ) const;
	void			remove_texture( void );

private:

	// Handling texture.
	void		UnsetTexture( void );

	// Private getters.
	const Colour& get_stroke_colour( void ) const;
	int			get_stroke_size( void ) const;
	EStrokeType	get_stroke_type( void ) const;

private:

	int			radius_;

	Colour		colour_;
	Colour		strokeColour_;
	int			strokeSize_;
	EStrokeType	strokeType_;

	Texture		*roundedRect_;

};

#endif // ROUNDED_RECTANGLE_H