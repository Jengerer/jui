#include "jui/layout/component.hpp"

namespace JUI
{

	/*
	 * Component constructor.
	 */
	Component::Component( void )
	{
		set_position( 0, 0 );
		set_size( 0, 0 );
		set_alpha( COMPONENT_MAX );
	}

	/*
	 * Component constructor.
	 */
	Component::Component( int x, int y )
	{
		set_position( x, y );
		set_size( 0, 0 );
		set_alpha( COMPONENT_MAX );
	}

	/*
	 * Default component destructor.
	 */
	Component::~Component( void )
	{
		// Component is destroyed.
	}

	/*
	 * Set component position.
	 */
	void Component::set_position( int x, int y )
	{
		x_ = x;
		y_ = y;
	}

	/*
	 * Get component width.
	 */
	int Component::get_width( void ) const
	{
		return width_;
	}

	/*
	 * Get component height.
	 */
	int Component::get_height( void ) const
	{
		return height_;
	}

	/*
	 * Set both component width and height.
	 */
	void Component::set_size( int width, int height )
	{
		width_ = width;
		height_ = height;
	}

	/*
	 * Get component X position.
	 */
	int Component::get_x( void ) const
	{
		return x_;
	}

	/*
	 * Get component Y position.
	 */
	int Component::get_y( void ) const
	{
		return y_;
	}

	/*
	 * Set component alpha (clamping invalid values).
	 */
	void Component::set_alpha( float alpha )
	{
		if (alpha > COMPONENT_MAX) {
			alpha_ = COMPONENT_MAX;
		}
		else if (alpha < COMPONENT_MIN) {
			alpha_ = COMPONENT_MIN;
		}
		else {
			alpha_ = alpha;
		}
	}

	/*
	 * Get clamped component alpha.
	 */
	float Component::get_alpha( void ) const
	{
		return alpha_;
	}

}
