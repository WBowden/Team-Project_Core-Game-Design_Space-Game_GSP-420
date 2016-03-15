/* Asteroid Manager, SmallAsteroid, and LargeAsteroid created by Brent Spector and edited by 
Darrell Smith*/

#pragma once


#include "ABC.h"
using namespace GSP420;
#include <list>

class LargeAsteroid : public GSP420::ABC
{
public:
	LargeAsteroid(const D3DXVECTOR3 pos) : ABC(pos, OT_LARGE_ASTEROID) {}
	void update(const float) {}
	//bool init(const int modelId, const int textureId) { return true; }
	void shutdown() {}
private:
};

class SmallAsteroid : public GSP420::ABC
{
public:
	SmallAsteroid(const D3DXVECTOR3 pos) : ABC(pos, OT_SMALL_ASTEROID) {}
	void update(const float) {}
	//bool init(const int modelId, const int textureId) { return true; }
	void shutdown() {}
private:

};

class AsteroidManager
{
	friend class D3DCore;
	friend class Physics;
public:
	void update(const float);
	inline void add(LargeAsteroid a) { LargeAsteroids.push_front(a); }
	void shutdown() {}
	void clear();
private:
	inline std::list<LargeAsteroid>& getLargeAsteroids() { return LargeAsteroids; }
	inline std::list<SmallAsteroid>& getSmallAsteroids() { return SmallAsteroids; }
	std::list<LargeAsteroid> LargeAsteroids;
	std::list<SmallAsteroid> SmallAsteroids;
};

