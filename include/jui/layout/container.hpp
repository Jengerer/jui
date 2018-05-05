#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "jui/layout/component.hpp"
#include <containers/vector.hpp>

namespace JUI
{

	class Container : public Component
	{

	public:

		// Container constructor.
		JUI_API Container( void );
		JUI_API Container( int x, int y );

		// Container destructor.
		virtual JUI_API ~Container( void );

		// Container resource handling.
		virtual JUI_API bool add( Component *component );
		virtual JUI_API void remove( Component *component );
		virtual JUI_API bool reserve( unsigned int elements );

		// Drawing functions.
		virtual JUI_API void draw( Graphics2D* graphics );

		// Local/global child position handling.
		void JUI_API clamp_child( Component *child, int padding = 0.0f ) const;
		virtual JUI_API bool is_visible( Component* child ) const;
		virtual JUI_API bool is_within_bounds( Component* child ) const;

	protected:

		JUTIL::Vector<Component*> components_;

	};

}

#endif // CONTAINER_HPP
