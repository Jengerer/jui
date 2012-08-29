#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include "jui/layout/component.hpp"

namespace JUI
{

    class Constraint
    {
    public:

        // Constructor.
        __declspec(dllexport) Constraint( Component* component, float localX, float localY );
        
        // Add/modify constraint.
        __declspec(dllexport) void set_constraint( float localX, float localY );

        // Get constraint target.
        __declspec(dllexport) Component* get_component() const;

        // Constraint getters.
        __declspec(dllexport) float get_constraint_x() const;
        __declspec(dllexport) float get_constraint_y() const;

    private:

        Component* component_;
        float localX_;
        float localY_;

    };

}

#endif // CONSTRAINT_HPP
