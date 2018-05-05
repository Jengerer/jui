#ifndef CONSTRAINT_CONTAINER_HPP
#define CONSTRAINT_CONTAINER_HPP

#include "jui/layout/constraint.hpp"
#include "jui/layout/container.hpp"
#include <containers/map.hpp>

namespace JUI
{

	class ConstrainedContainer : public Container
	{
	public:

		JUI_API ConstrainedContainer( void );
		JUI_API ConstrainedContainer( int x, int y );
		virtual JUI_API ~ConstrainedContainer( void );

		// Component override.
		virtual JUI_API void set_position( int x, int y );

		// Container overrides.
		virtual JUI_API bool add( Component* child );
		virtual JUI_API void remove( Component* child );
		
		// Constraint management.
		JUI_API Constraint* set_constraint( Component* child, int x, int y );
		JUI_API void remove_constraint( Component* child );
		JUI_API void remove_all_constraints( void );
		JUI_API void apply_constraint( Constraint* constraint );
		JUI_API void apply_constraints( void );

	private:

		JUTIL::Map<Component*, Constraint*> constraints_;

	};

}

#endif // CONSTRAINT_CONTAINER_HPP
