#include "jui/layout/container.hpp"

namespace JUI
{
    #include <algorithm>

    Container::Container( float localX, float localY ) : Component( localX, localY )
    {
        // Container created.
    }

    Container::~Container( void )
    {
        // Container destroyed.
        std::vector<Component*>::iterator i;
        for (i = components_.begin(); i != components_.end(); i = components_.erase( i )) {
            delete *i;
        }
    }

    void Container::add( Component* component )
    {
        components_.push_back( component );
    }

    void Container::remove( Component* component )
    {
        std::vector<Component*>::iterator i = find( components_.begin(), components_.end(), component );
        if (i != components_.end()) {
            components_.erase( i );
        }
    }

    void Container::draw( Graphics2D* graphics )
    {
        // Draw all children.
        for (auto i = components_.begin(), end = components_.end(); i != end; ++i) {
            Component* child = *i;

            // TASK: make visibility optional; not all components have fixed width/height.
            child->draw( graphics );
        }
    }

    void Container::set_alpha( int alpha )
    {
        Component::set_alpha( alpha );
        for (auto i = components_.begin(), end = components_.end(); i != end; ++i) {
            Component* child = *i;
            child->set_alpha( alpha );
        }
    }

    bool Container::is_within_bounds( Component *component ) const
    {
        float childX = component->get_x();
        float childY = component->get_y();
        float parentX = get_x();
        float parentY = get_y();
        return (childX > parentX - component->get_width()) && 
            (childX < parentX + get_width()) && 
            (childY > parentY - component->get_height()) && 
            (childY < parentY + get_height());
    }

    bool Container::is_visible( Component *component ) const
    {
        return is_within_bounds( component );
    }

    void Container::clamp_child( Component *component, float padding ) const
    {
        float childX = component->get_x();
        float childY = component->get_y();
        float parentX = get_x();
        float parentY = get_y();
        
        // Generate bounds.
        float leftBound = parentX + padding;
        float topBound = parentY + padding;

        // Clamp X position.
        if (childX < leftBound) {
            childX = leftBound;
        }
        else {
            float rightBound = parentX + get_width() - component->get_width() - padding;
            if (childX > rightBound) {
                childX = rightBound;
            }
        }

        // Clamp Y position.
        if (childY < topBound) {
            childY = topBound;
        }
        else {
            float bottomBound = parentY + get_height() - component->get_height() - padding;
            if (childY > bottomBound) {
                childY = bottomBound;
            }
        }

        component->set_position( childX, childY );
    }

}
