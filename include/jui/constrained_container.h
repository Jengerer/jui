#ifndef CONSTRAINT_CONTAINER_H
#define CONSTRAINT_CONTAINER_H

#include <map>
#include "jui/constraint.h"
#include "jui/container.h"

class ConstrainedContainer : public Container
{
public:

	__declspec(dllexport) ConstrainedContainer( float x = 0.0f, float y = 0.0f );
	__declspec(dllexport) virtual ~ConstrainedContainer();

	// Component override.
	__declspec(dllexport) virtual void set_position( float x, float y );

	// Container overrides.
	__declspec(dllexport) virtual void remove( Component* child );
	
	// Constraint management.
	__declspec(dllexport) Constraint* set_constraint( Component* child, float localX, float localY );
	__declspec(dllexport) void remove_constraint( Component* child );
	__declspec(dllexport) void remove_all_constraints();
	__declspec(dllexport) void apply_constraint( Constraint* constraint );
	__declspec(dllexport) void apply_constraints();

private:

	std::map<Component*, Constraint*> constraints_;

};

#endif // CONSTRAINT_CONTAINER_H