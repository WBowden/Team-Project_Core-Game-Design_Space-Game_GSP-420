// AI core code by Spencer Allen and Michael Blake

#pragma once
using namespace std;
#include <list>
#include "../Main/EnemyManager.h"
#include "../Main/ProjectileManager.h"

enum SpawnState { WAVE1, WAVE2, WAVE3, BOSS };

static const int ENEMY_SPAWN_RATE = 7;
static const float ENEMY_MISSILE_TURN_RADIUS = 5.0f;
static const float ENEMY_MISSILE_SPEED = 5.0f;
static const float ENEMY_SPEED = 5.0f;

static const float ENEMY_BULLET_FR = 3.0f;
static const float ENEMY_MISSILE_FR = 3.0f;
static const float ENEMY_MINE_FR = 2.0f;

static const float PI = 3.14159f;

class AI
{
public:
	AI(void);
	~AI(void);
	//void init() {}
	void update(const float, GSP420::ABC*);
	void spawn(const float);
	//void shutdown() {}

	void enemy1Update(Enemy&, GSP420::ABC*, const float);
	//void enemy2Update(Enemy&, GSP420::ABC*, const float);
	void enemy2Update(Enemy&, const float);
	void enemy3Update(Enemy&, const float);
	void enemyBossUpdate(Enemy&, const float);
	void playerMissUpdate(Missile&, std::list<Enemy>*, GSP420::ABC*);
	void enemyMissUpdate(Missile&, GSP420::ABC*, const float);
private:
	float spawnTime, waveTime;
	SpawnState spawnState;
};