#ifndef COLLISION_RECTANGLE_H_
#define COLLISION_RECTANGLE_H_

#include "rectangle.h"

struct CollisionRectangle
{
    virtual Rectangle boundingBox() const = 0;

    Rectangle collision(sides::SideType side,
                        units::Game x,
                        units::Game y,
                        units::Game delta) const
    {
        switch (side)
        {
            case sides::LEFT_SIDE:   return leftCollision(x, y, delta);
            case sides::RIGHT_SIDE:  return rightCollision(x, y, delta);
            case sides::TOP_SIDE:    return topCollision(x, y, delta);
            case sides::BOTTOM_SIDE: return bottomCollision(x, y, delta);
        }
    }

    virtual Rectangle leftCollision(units::Game x,
                                    units::Game y,
                                    units::Game delta) const = 0;

    virtual Rectangle rightCollision(units::Game x,
                                     units::Game y,
                                     units::Game delta) const = 0;

    virtual Rectangle topCollision(units::Game x,
                                   units::Game y,
                                   units::Game delta) const = 0;

    virtual Rectangle bottomCollision(units::Game x,
                                      units::Game y,
                                      units::Game delta) const = 0;

    virtual ~CollisionRectangle();
};

#endif // COLLISION_RECTANGLE_H_
