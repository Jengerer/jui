#include "jui/layout/constraint.hpp"

namespace JUI
{

	/*
	 * Constraint constructor by component and offset.
	 */
	Constraint::Constraint( Component* component, int x, int y )
	{
		component_ = component;
		set_constraint( x, y );
	}

	/*
	 * Set constraint offsets for component.
	 */
	void Constraint::set_constraint( int x, int y )
	{
		x_ = x;
		y_ = y;
	}

	/*
	 * Get the component this constraint is modifying.
	 */
	Component* Constraint::get_component( void ) const
	{
		return component_;
	}

	/*
	 * Get the constraint X offset.
	 */
	int Constraint::get_x( void ) const
	{
		return x_;
	}

	/*
	 * Get the constraint Y offset.
	 */
	int Constraint::get_y( void ) const
	{
		return y_;
	}

}
