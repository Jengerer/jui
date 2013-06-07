#include "jui/layout/layout.hpp"

namespace JUI
{

	Layout::Layout( void )
	{
		// Layout created.
		set_parent( nullptr );
	}

	Layout::~Layout( void )
	{
		// Layout destroyed.
	}

	bool Layout::is_visible( Component *component ) const
	{
		const Container *parent = get_parent();
		if ( parent != nullptr ) {
			return parent->is_visible( component );
		}

		return Container::is_visible( component );
	}

	void Layout::set_parent( Container *parent )
	{
		parent_ = parent;
	}

	const Container* Layout::get_parent( void ) const
	{
		return parent_;
	}

}
