#ifndef SIDE_TYPE_H_
#define SIDE_TYPE_H_

#include "sprite_state.h"

namespace sides
{
    enum SideType
    {
        TOP_SIDE,
        BOTTOM_SIDE,
        LEFT_SIDE,
        RIGHT_SIDE
    };

    inline SideType opposite_side(SideType side)
    {
        switch (side)
        {
            case TOP_SIDE:    return BOTTOM_SIDE;
            case BOTTOM_SIDE: return TOP_SIDE;
            case LEFT_SIDE:   return RIGHT_SIDE;
            case RIGHT_SIDE:  return LEFT_SIDE;
        }
    }

    inline bool vertical(SideType side)
    {
        return side == TOP_SIDE || side == BOTTOM_SIDE;
    }

    inline bool horizontal(SideType side)
    {
        return !vertical(side);
    }

    inline SideType from_facing(HorizontalFacing horizontal_facing,
                                VerticalFacing vertical_facing)
    {
        if (vertical_facing == UP)
        {
            return TOP_SIDE;
        }
        else if (vertical_facing == DOWN)
        {
            return BOTTOM_SIDE;
        }
        else if (horizontal_facing == LEFT)
        {
            return LEFT_SIDE;
        }
        return RIGHT_SIDE;
    }

    inline bool is_max(SideType side)
    {
        return side == RIGHT_SIDE || side == BOTTOM_SIDE;
    }

    inline bool is_min(SideType side)
    {
        return !is_max(side);
    }
}

#endif // SIDE_TYPE_H_
