//PickupManager and Pickup classes created by Brent Spector and edited by Darrell Smith
#pragma once

#include <list>
#include "ABC.h"
using namespace GSP420;

const static int HEALTH_REGAINED = 10;
const static float INVULNERABLE_TIME = 10.f;
const static int MISSILES_GIVEN = 5;
const static int MINE_DAMAGE = 10;
//chance of getting particular pickup when enemy dies
//these values are the chance it will occur out of 100
const static int GET_HEALTH_CHANCE = 10;
const static int GET_INVULNERABLE_CHANCE = 5;
const static int GET_MISSILES_CHANCE = 15;

enum PICKUP_TYPE { PU_HEALTH, PU_INVULNERABLE, PU_MISSILE, PU_MINE };

class Pickup : public GSP420::ABC
{
public:
	Pickup(D3DXVECTOR3 pos, PICKUP_TYPE t) : ABC(pos, OT_PICKUP), taken(false), Type(t) {}
	void update(const float) {}
	//bool init(const int modelId, const int textureId) { return true; }
	void shutdown() {}
	void activate();
	inline void take() { taken = true; }
	inline bool isTaken() { return taken; }
private:
	PICKUP_TYPE Type;
	bool taken;//if taken by player. If it has been, then it will be activated on removal
	//depending on the type of pick up, this could be amount of health gained,
	//seconds of invulnerability gained, or missile ammo received
	int Value;
};


class PickupManager
{
	friend class AI;
	friend class D3DCore;
	friend class Physics;
public:
	void add(Pickup);
	void update(const float);
	inline void clear() { Pickups.clear(); }
private:
	inline std::list<Pickup>& getPickups() { return Pickups; }
	std::list<Pickup> Pickups;
};

