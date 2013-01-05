#ifndef HORIZONTAL_SPLIT_CONTAINER_HPP
#define HORIZONTAL_SPLIT_CONTAINER_HPP

#include "jui/layout/layout.hpp"
#include "jui/layout/horizontal_layout.hpp"

namespace JUI
{

	class __declspec(dllexport) HorizontalSplitLayout: public Layout
	{

	public:

		// Creation.
		HorizontalSplitLayout( int width );

		// Layout packing functions.
		virtual void pack( void );
		bool set_left( Component* component );
		bool set_right( Component* component );

	private:

		Component* left_;
		Component* right_;

	};

}

#endif // HORIZONTAL_SPLIT_CONTAINER_HPP
