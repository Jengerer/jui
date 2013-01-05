#ifndef CONSTRAINT_CONTAINER_HPP
#define CONSTRAINT_CONTAINER_HPP

#include "jui/layout/constraint.hpp"
#include "jui/layout/container.hpp"
#include <containers/map.hpp>

namespace JUI
{

	class __declspec(dllexport) ConstrainedContainer : public Container
	{
	public:

		ConstrainedContainer( void );
		ConstrainedContainer( int x, int y );
		virtual ~ConstrainedContainer( void );

		// Component override.
		virtual void set_position( int x, int y );

		// Container overrides.
		virtual bool add( Component* child );
		virtual void remove( Component* child );
		
		// Constraint management.
		Constraint* set_constraint( Component* child, int x, int y );
		void remove_constraint( Component* child );
		void remove_all_constraints( void );
		void apply_constraint( Constraint* constraint );
		void apply_constraints( void );

	private:

		JUTIL::Map<Component*, Constraint*> constraints_;

	};

}

#endif // CONSTRAINT_CONTAINER_HPP
