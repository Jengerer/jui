#ifndef GRID_LAYOUT_HPP
#define GRID_LAYOUT_HPP

#include "jui/layout/layout.hpp"

namespace JUI
{

	/*
	 * Layout that inserts equally sized elements into a grid format
	 * given a certain number of elements per row.
	 */
	class __declspec(dllexport) GridLayout : public Layout
	{

	public:

		GridLayout( void );
		virtual ~GridLayout( void );

		// Layout packing.
		virtual void pack( unsigned int width, unsigned int spacing );

	};

}

#endif // GRID_LAYOUT_HPP
