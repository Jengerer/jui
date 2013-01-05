#include "jui/layout/container.hpp"
#include <memory/base_allocator.hpp>

namespace JUI
{

	/*
	 * Container constructor.
	 */
	Container::Container( void )
	{
		// Container created.
	}

	/*
	 * Container constructor.
	 */
	Container::Container( int x, int y ) : Component( x, y )
	{
		// Container created.
	}

	/*
	 * Container destructor; destroys all children.
	 */
	Container::~Container( void )
	{
		size_t i;
		size_t length = components_.get_length();
		for (i = 0; i < length; ++i) {
			Component* current = components_.get( i );
			JUTIL::BaseAllocator::destroy( current );
		}
	}

	/*
	 * Add an element to the container.
	 */
	bool Container::add( Component* component )
	{
		return components_.push( component );
	}

	/*
	 * Remove an element from the container (without destroying it).
	 */
	void Container::remove( Component* component )
	{
		components_.remove( component );
	}

	/*
	 * Draw this container (and all children).
	 */
	void Container::draw( Graphics2D* graphics )
	{
		// Draw all children.
		size_t i;
		size_t length = components_.get_length();
		for (i = 0; i < length; ++i) {
			Component* child = components_.get( i );

			// Don't draw if not visible.
			if (is_visible( child )) {
				child->draw( graphics );
			}
		}
	}

	/*
	 * Set the container's alpha and propogate call to children.
	 */
	void Container::set_alpha( int alpha )
	{
		Component::set_alpha( alpha );

		// Pass to children.
		size_t i;
		size_t length = components_.get_length();
		for (i = 0; i < length; ++i) {
			Component* child = components_.get( i );
			child->set_alpha( alpha );
		}
	}

	/*
	 * Check if component is within bounds of this one.
	 */
	bool Container::is_within_bounds( Component *component ) const
	{
		int child_x = component->get_x();
		int child_y = component->get_y();
		int parent_x = get_x();
		int parent_y = get_y();
		return (child_x > parent_x - component->get_width()) && 
			(child_x < parent_x + get_width()) && 
			(child_y > parent_y - component->get_height()) && 
			(child_y < parent_y + get_height());
	}

	/*
	 * Returns if a component is visible inside this one.
	 */
	bool Container::is_visible( Component *component ) const
	{
		return (component->get_alpha() != 0) && is_within_bounds( component );
	}

	/*
	 * Clamps a component to this container with a given padding.
	 * Makes sure the child's top-left is at least (padding, padding) and
	 * child's bottom-right is at most (width - padding, width - padding).
	 */
	void Container::clamp_child( Component *component, int padding ) const
	{
		int child_x = component->get_x();
		int child_y = component->get_y();
		int parent_x = get_x();
		int parent_y = get_y();
		
		// Generate bounds.
		int left_bound = parent_x + padding;
		int top_bound = parent_y + padding;

		// Clamp X position.
		if (child_x < left_bound) {
			child_x = left_bound;
		}
		else {
			int right_bound = parent_x + get_width() - component->get_width() - padding;
			if (child_x > right_bound) {
				child_x = right_bound;
			}
		}

		// Clamp Y position.
		if (child_y < top_bound) {
			child_y = top_bound;
		}
		else {
			int bottom_bound = parent_y + get_height() - component->get_height() - padding;
			if (child_y > bottom_bound) {
				child_y = bottom_bound;
			}
		}

		component->set_position( child_x, child_y );
	}

}
