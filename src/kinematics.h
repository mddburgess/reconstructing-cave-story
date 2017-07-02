#ifndef KINEMATICS_H_
#define KINEMATICS_H_

#include "units.h"

struct Kinematics
{
    units::Game position;
    units::Velocity velocity;

    Kinematics(units::Game position,
               units::Game velocity) :
        position(position),
        velocity(velocity)
    {
    }

    units::Game delta(units::MS elapsed_time)
    {
        return velocity * elapsed_time;
    }
};

#endif // KINEMATICS_H_
