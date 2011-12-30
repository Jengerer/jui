#include "jui/layout.h"

Layout::Layout( unsigned int spacing )
{
	// Layout created.
	set_parent( nullptr );
	set_spacing( spacing );
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

void Layout::set_spacing( int spacing )
{
	spacing_ = spacing;
}

int Layout::get_spacing( void ) const
{
	return spacing_;
}

void Layout::set_parent( Container *parent )
{
	parent_ = parent;
}

const Container* Layout::get_parent( void ) const
{
	return parent_;
}