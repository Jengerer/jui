#ifndef GRID_LAYOUT_HPP
#define GRID_LAYOUT_HPP

#include "jui/layout/layout.hpp"

namespace JUI
{

	/*
	 * Layout that inserts equally sized elements into a grid format
	 * given a certain number of elements per row.
	 */
	class GridLayout : public Layout
	{

	public:

		JUI_API GridLayout( void );
		JUI_API virtual ~GridLayout( void );

		// Layout packing.
		JUI_API virtual void pack( unsigned int width, unsigned int spacing );

	};

}

#endif // GRID_LAYOUT_HPP
