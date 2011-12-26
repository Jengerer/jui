#ifndef BOX_H
#define BOX_H

#include "jui/component.h"

class Box : public Component
{

public:
	
	// Constructor.
	Box();

	// IDrawable over-ride.
	virtual void draw( Graphics2D* graphics );

private:

	Colour colour_;

};

#endif // BOX_H