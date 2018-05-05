#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include "jui/layout/component.hpp"

namespace JUI
{

	class JUI_API Constraint
	{
	public:

		// Constructor.
		Constraint( Component* component, int x, int y );
		
		// Add/modify constraint.
		void set_constraint( int x, int y );

		// Get constraint target.
		Component* get_component( void ) const;

		// Constraint getters.
		int get_x( void ) const;
		int get_y( void ) const;

	private:

		Component* component_;
		int x_;
		int y_;

	};

}

#endif // CONSTRAINT_HPP
