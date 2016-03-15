//PickupManager and Pickup classes created by Brent Spector and edited by Darrell Smith
#include "PickupManager.h"

#include "Game.h"

void Pickup::activate()
{
	switch (Type)
	{
	case PU_HEALTH:
		PLAYER.heal(HEALTH_REGAINED);
		break;
	case PU_INVULNERABLE:
		PLAYER.makeInvulnerable(INVULNERABLE_TIME);
		break;
	case PU_MISSILE:
		PLAYER.giveMissileAmmo(MISSILES_GIVEN);
		break;
	case PU_MINE:
		PLAYER.hurt(MINE_DAMAGE);
		break;
	}
}

void PickupManager::add(Pickup p)
{
	Pickups.push_front(p);
}

void PickupManager::update(const float dt)
{
	std::list<Pickup>::iterator it = Pickups.begin();
	while (it != Pickups.end())
	{
		//if marked as collided with the player
		if (it->isTaken())
		{
			it->activate();
			it = Pickups.erase(it);
		}
		//if marked as having gone off-screen
		else if (!it->isEnabled())
		{
			it = Pickups.erase(it);
		}
		else
		{
			++it;
		}
	}
}

