#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include "jui/component.h"

class Container : public Component
{

public:

	// Container constructor.
	__declspec(dllexport) Container( float x = 0.0f, float y = 0.0f );

	// Container destructor.
	__declspec(dllexport) virtual ~Container();

	// Container resource handling.
	__declspec(dllexport) virtual void add( Component *component );
	__declspec(dllexport) virtual void remove( Component *component );

	// Drawing functions.
	__declspec(dllexport) virtual void draw( Graphics2D* graphics );
	__declspec(dllexport) virtual void set_alpha( int alpha );

	// Local/global child position handling.
	__declspec(dllexport) void clamp_child( Component *child, float padding = 0.0f ) const;
	__declspec(dllexport) virtual bool is_visible( Component* child ) const;
	__declspec(dllexport) virtual bool is_within_bounds( Component* child ) const;

protected:

	// Vector of components.
	std::vector<Component*>	components_;

};

#endif // CONTAINER_H