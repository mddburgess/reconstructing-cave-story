#include "pickups.h"

#include "pickup.h"
#include "player.h"

void Pickups::handleCollisions(Player& player)
{
    for (auto iter = pickups_.begin(); iter != pickups_.end(); )
    {
        if (player.damageRectangle().collidesWith((*iter)->collisionRectangle()))
        {
            player.collectPickup(**iter);
            pickups_.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }
}

void Pickups::update(units::MS elapsed_time, const Map& map)
{
    for (auto iter = pickups_.begin(); iter != pickups_.end(); )
    {
        if ((*iter)->update(elapsed_time, map))
        {
            ++iter;
        }
        else
        {
            pickups_.erase(iter++);
        }
    }
}

void Pickups::draw(Graphics& graphics)
{
    for (auto pickup : pickups_)
    {
        pickup->draw(graphics);
    }
}
