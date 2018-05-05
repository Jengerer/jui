#ifndef HORIZONTAL_SPLIT_CONTAINER_HPP
#define HORIZONTAL_SPLIT_CONTAINER_HPP

#include "jui/layout/layout.hpp"
#include "jui/layout/horizontal_layout.hpp"

namespace JUI
{

	class HorizontalSplitLayout: public Layout
	{

	public:

		// Creation.
		JUI_API HorizontalSplitLayout( int width );

		// Layout packing functions.
		JUI_API virtual void pack( void );
		JUI_API bool set_left( Component* component );
		JUI_API bool set_right( Component* component );

	private:

		Component* left_;
		Component* right_;

	};

}

#endif // HORIZONTAL_SPLIT_CONTAINER_HPP
