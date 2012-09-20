#include "jui/layout/constrained_container.hpp"
#include <memory/base_allocator.hpp>

namespace JUI
{

    /*
     * Default constrainted container constructor.
     */
    ConstrainedContainer::ConstrainedContainer( float x, float y ) : Container( x, y )
    {
        // Constraint container.
    }

    /*
     * Constraint container destructor.
     */
    ConstrainedContainer::~ConstrainedContainer( void )
    {
        remove_all_constraints();
    }

    /*
     * Update children by constraints when moved.
     */
    void ConstrainedContainer::set_position( float x, float y )
    {
        Component::set_position( x, y );
        apply_constraints();
    }

    /*
     * Add a child and allocate a constraint for it.
     */
    bool ConstrainedContainer::add( Component* child )
    {
        // Generic add.
        if (!Container::add( child )) {
            return false;
        }

        // Allocate a constraint.
        Constraint* constraint;
        if (!JUTIL::BaseAllocator::allocate( &constraint )) {
            return false;
        }
        constraint = new (constraint) Constraint( child, 0.0f, 0.0f );

        // Add constraint.
        if (!constraints_.insert( child, constraint )) {
            JUTIL::BaseAllocator::destroy( constraint );
            return false;
        }
        return true;
    }

    /*
     * Remove a child and remove constraint if exists.
     */
    void ConstrainedContainer::remove( Component* child )
    {
        Container::remove( child );
        remove_constraint( child );
    }

    /*
     * Set constraint on child or update it if it exists.
     */
    Constraint* ConstrainedContainer::set_constraint( Component* child, float x, float y )
    {
        // Get, apply, return.
        Constraint* constraint = nullptr;
        if (constraints_.get( child, &constraint )) {
            constraint->set_constraint( x, y );
            apply_constraint( constraint );
        }
        return constraint;
    }

    /*
     * Remove constraint.
     */
    void ConstrainedContainer::remove_constraint( Component* child )
    {
        constraints_.remove( child );
    }

    /*
     * Clear all constraints.
     */
    void ConstrainedContainer::remove_all_constraints()
    {
        JUTIL::Map<Component*, Constraint*>::Iterator i;
        for (i = constraints_.begin(); i.has_next(); i.next()) {
            JUTIL::BaseAllocator::destroy( i.get_value() );
        }
        constraints_.clear();
    }

    /*
     * Apply constraint to the targetted child.
     */
    void ConstrainedContainer::apply_constraint( Constraint* constraint )
    {
        Component* component = constraint->get_component();
        float new_x = get_x() + constraint->get_constraint_x();
        float new_y = get_y() + constraint->get_constraint_y();
        component->set_position( new_x, new_y );
    }

    /*
     * Apply all constraints.
     */
    void ConstrainedContainer::apply_constraints( void )
    {
        JUTIL::Map<Component*, Constraint*>::Iterator i;
        for (i = constraints_.begin(); i.has_next(); i.next()) {
            apply_constraint( i.get_value() );
        }
    }

}
