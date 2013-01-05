#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include "jui/layout/component.hpp"

namespace JUI
{

	class Constraint
	{
	public:

		// Constructor.
		__declspec(dllexport) Constraint( Component* component, int x, int y );
		
		// Add/modify constraint.
		__declspec(dllexport) void set_constraint( int x, int y );

		// Get constraint target.
		__declspec(dllexport) Component* get_component( void ) const;

		// Constraint getters.
		__declspec(dllexport) int get_x( void ) const;
		__declspec(dllexport) int get_y( void ) const;

	private:

		Component* component_;
		int x_;
		int y_;

	};

}

#endif // CONSTRAINT_HPP
