#include "AI.h"
#include "../EngineDemo/Game.h"
#include <math.h>

AI::AI(void)
{
	waveTime = 30.0f;
	spawnTime = float(rand() % ENEMY_SPAWN_RATE);
	spawnState = WAVE1;
}


AI::~AI(void)
{
}

void AI::update(const float dt, GSP420::ABC *player)
{
	// Iterate through the list of enemies and update their AI based on their type
	std::list<Enemy> enemies = ENEMIES.getEnemies();
	std::list<Enemy>::iterator enemyIt = enemies.begin();
	while (enemyIt != enemies.end())
	{
		switch (enemyIt->getObjectType())
		{
		case OT_ENEMY1:
		{
			enemy1Update(*enemyIt, player, dt);
		} break;
		case OT_ENEMY2:
		{
			enemy2Update(*enemyIt, dt);
		} break;
		case OT_ENEMY3:
		{
			enemy3Update(*enemyIt, dt);
		} break;
		case OT_ENEMYBOSS:
		{
			enemyBossUpdate(*enemyIt, dt);
		} break;
		}

		enemyIt++;
	}

	// Iterate through the list of projectiles and update their AI based on their type
	std::list<Missile*> missiles = PROJECTILES.getMissiles();
	std::list<Missile*>::iterator missileIt = missiles.begin();
	while (missileIt != missiles.end())
	{
		switch ((*missileIt)->getObjectType())
		{
		case OT_PLAYER_MISSILE:
		{
			playerMissUpdate(*(*missileIt), &enemies, player);
		} break;
		case OT_ENEMY_MISSILE:
		{
			enemyMissUpdate(*(*missileIt), player, dt);
		} break;
		}

		missileIt++;
	}
}

//////// Spawn new enemies into the game   ////////
//////// based on game time and wave state ////////
void AI::spawn(const float dt)
{
	// Decrease our spwanTime counter based on game time
	// If it reaches 0 spawn a new enemy and then reset spawnTime
	if (spawnState != BOSS)
	{
		spawnTime -= dt;
		waveTime -= dt;
	}

	if (spawnTime <= 0.0f)
	{
		switch (spawnState)
		{
		case WAVE1:
		{
			ENEMIES.add(Enemy(D3DXVECTOR3(0.0f, 50.0f, 0.0f), OT_ENEMY1)); // TODO: Modify for game width and height
			spawnTime = float(rand() % ENEMY_SPAWN_RATE);
			if (waveTime <= 0.0f)
			{
				spawnState = WAVE2;
				waveTime = 50.0f;
			}
		} break;
		case WAVE2:
		{
			float x = float(rand() % 50) - 25.0f; // TODO: Modify for game width constant
			ENEMIES.add(Enemy(D3DXVECTOR3(x, 50.0f, 0.0f), OT_ENEMY2)); // TODO: Modify for game width and height
			spawnTime = float(rand() % ENEMY_SPAWN_RATE);
			if (waveTime <= 0.0f)
			{
				spawnState = WAVE3;
				waveTime = 100.0f;
			}
		} break;
		case WAVE3:
		{
			ENEMIES.add(Enemy(D3DXVECTOR3(0.0f, 50.0f, 0.0f), OT_ENEMY3)); // TODO: Modify for game width and height
			spawnTime = float(rand() % ENEMY_SPAWN_RATE);
			if (waveTime <= 0.0f)
			{
				spawnState = BOSS;
				spawnTime = 0.0f;
			}
		} break;
		case BOSS:
		{
			ENEMIES.add(Enemy(D3DXVECTOR3(0.0f, 50.0f, 0.0f), OT_ENEMYBOSS)); // TODO: Modify for game width and height
			spawnTime = 10.0f;
		} break;
		}
	}
}

/////// This enemy behavior seeks out the player ////////
/////// until they reach a set Y value at which  ////////
/////// point they simply fly straight.          ////////
void AI::enemy1Update(Enemy &enemy, GSP420::ABC *player, const float dt)
{
	// Check if enemy Y position is higher than half the game height
	if (enemy.getPosition().y > 0.0f) // TODO: Modify for exact game height constant
	{
		D3DXVECTOR3 tempVel;
		// Get new enemy direction based on player position
		tempVel = player->getPosition() - enemy.getPosition();
		D3DXVec3Normalize(&tempVel, &tempVel);

		// Multiply enemy direction by its speed to get its velocity
		tempVel *= ENEMY_SPEED;
		enemy.setVelocity(tempVel);
	}

	// Uncomment if needed
	//enemy.setPosition(enemy.getPosition() += enemy.getVelocity() * dt);

	// Check if enemy should fire a bullet
	float bFireRate = enemy.getBulletFireRate();
	enemy.setBulletFireRate(bFireRate -= dt);
	if (bFireRate <= 0.0f)
	{
		enemy.fireBullet(D3DXVECTOR3(0.0f, -5.0f, 0.0f)); // TODO: Modify for a fixed bullet speed constant
		enemy.setBulletFireRate(ENEMY_BULLET_FR);
	}
}


void AI::enemy2Update(Enemy &enemy, const float dt)
{
	//this will represent the max distance the enemy can moe up and down
	float maxAmplitude = 0.0f;

	//create a vector to change for the new enemy position
	D3DXVECTOR3 tempVel = enemy.getPosition();

	//increment the y-position to follow a sine curve
	tempVel.y = maxAmplitude * sin(dt * 0.5f * PI);

	//increment the Xposition by the EnemySpeed
	tempVel.x = tempVel.x += ENEMY_SPEED;

	//normalize the vector
	D3DXVec3Normalize(&tempVel, &tempVel);

	tempVel *= ENEMY_SPEED;

	enemy.setVelocity(tempVel);

	// Check if enemy should fire a missile
	float missFireRate = enemy.getMissileFireRate();
	enemy.setMissileFireRate(missFireRate -= dt);
	if (missFireRate <= 0.0f)
	{
		enemy.fireMissile(D3DXVECTOR3(0.0f, -5.0f, 0.0f)); // TODO: Modify for a fixed missile speed constant
		enemy.setMissileFireRate(ENEMY_MISSILE_FR);
	}
}

void AI::enemy3Update(Enemy &enemy, const float dt)
{
	//create the radius if the circle you want the enemy to move
	float radius = 5.0f;

	//set the angle to the current time settings so it continous to incrememnt 
	//as the enemy is on the screen
	float angle = dt;

	//create a vector that represents the enemies current position
	D3DXVECTOR3 tempVel = enemy.getPosition();

	//set the enemy position as the center of the circle
	D3DXVECTOR3 origin = tempVel;

	//make the new enemy position depending on sin and cos curves
	tempVel.x = origin.x + cos(angle) * radius;
	tempVel.y = origin.y + sin(angle) * radius;

	D3DXVec3Normalize(&tempVel, &tempVel);

	tempVel *= ENEMY_SPEED;

	enemy.setVelocity(tempVel);

	// Check if enemy should drop a mine
	float mineFireRate = enemy.getMineFireRate();
	enemy.setMineFireRate(mineFireRate -= dt);
	if (mineFireRate <= 0.0f)
	{
		enemy.dropMine();
		enemy.setMineFireRate(ENEMY_MINE_FR);
	}
}

//////// Boss moves down into game screen ////////
//////// then begins its attack run       ////////
void AI::enemyBossUpdate(Enemy &enemy, const float dt)
{
	// Move into game screen
	if (enemy.getPosition() < D3DXVECTOR3(0.0f, 20.0f, 0.0f)) // TODO: Modify for constant Y position value
	{
		D3DXVECTOR3 vel = D3DXVECTOR3(0.0f, -5.0f, 0.0f);
		enemy.setVelocity(vel);
		// Uncomment if needed
		//enemy.setPosition(enemy.getPosition() += vel * dt);
	}
	else
	{
		// Begin attack run
		// Fire bullets
		float bFireRate = enemy.getBulletFireRate();
		enemy.setBulletFireRate(bFireRate -= dt);
		if (bFireRate <= 0.0f)
		{
			float x = -20.0f;
			for (int i = 0; i < 4; i++)
			{
				enemy.fireBullet(D3DXVECTOR3(x, -20.0f, 0.0f));
				x += 10.0f;
			}

			enemy.setBulletFireRate(1.0f);
		}

		// Fire missiles
		float missFireRate = enemy.getMissileFireRate();
		enemy.setMissileFireRate(missFireRate -= dt);
		if (missFireRate <= 0.0f)
		{
			enemy.fireMissile(D3DXVECTOR3(0.0f, -20.0f, 0.0f));
			enemy.setMissileFireRate(10.0f);
		}

		// Fire mines
		// Cannot specify where to drop mine
		// Mines are listed as a pickup, are they intended to be picked up by the player?
		/*float mineFireRate = enemy.getMineFireRate();
		enemy.setMineFireRate(mineFireRate -= dt);
		if (mineFireRate <= 0.0f)
		{

		}*/
	}
}

//////// Missile locks on to closest enemy in front of player ////////
//////// Missile tracks enemy aggressively                    ////////
void AI::playerMissUpdate(Missile &proj, std::list<Enemy> *enemies, GSP420::ABC *player)
{
	// If missile has no target, get one
	if (proj.getEnemyTarget() == NULL)
	{
		float closestY = -100.0f;
		// Search through the enemy list for the one closest
		// to the player within a set field of view
		std::list<Enemy>::iterator enemyIt = enemies->begin();
		while (enemyIt != enemies->end())
		{
			if (enemyIt->getPosition().x > player->getPosition().x - 5.0f &&
				enemyIt->getPosition().x < player->getPosition().x + 5.0f &&
				enemyIt->getPosition().y > closestY)
			{
				closestY = enemyIt->getPosition().y;
				proj.setEnemyTarget(&*enemyIt);
			}

			enemyIt++;
		}
	}
	else // Otherwise track the enemy target
	{
		D3DXVECTOR3 newVel;
		Enemy *enemy = proj.getEnemyTarget();

		// Find the updated direction for the missile based on enemy position
		newVel = enemy->getPosition() - proj.getPosition();
		D3DXVec3Normalize(&newVel, &newVel);

		// Multiply direction vector by missile speed to obtain missile velocity
		newVel *= ENEMY_MISSILE_SPEED;
		proj.setVelocity(newVel);
	}
}

//////// Missile tracks player and follows them ////////
//////// Has a limited turning radius.          ////////
//////// Has a limited lifetime until it        ////////
//////// explodes								////////
void AI::enemyMissUpdate(Missile &proj, GSP420::ABC *player, const float dt)
{
	D3DXVECTOR3 currDir, newDir;
	// Get the missiles current direction from its velocity
	currDir = proj.getVelocity();
	D3DXVec3Normalize(&currDir, &currDir);

	// Get the missiles new direction according to player position
	newDir = player->getPosition() - proj.getPosition();
	D3DXVec3Normalize(&newDir, &newDir);

	// Find the angle between the two vectors
	float angle = D3DXVec3Dot(&currDir, &newDir);
	angle = acos(angle);

	// Re-use newDir vector for updating projectile velocity
	newDir = proj.getVelocity();

	D3DXMATRIX rotMat;
	// Check if angle is larger than our missile's turning radius
	// Then update the missiles velocity by rotating it in the
	// direction of the angle
	if (abs(angle) > ENEMY_MISSILE_TURN_RADIUS)
	{
		if (angle > 0.0f)
		{
			D3DXMatrixRotationY(&rotMat, ENEMY_MISSILE_TURN_RADIUS);
			newDir.x = (rotMat._11 * newDir.x) + (rotMat._12 * newDir.y) + (rotMat._13 * newDir.z);
			newDir.y = (rotMat._11 * newDir.x) + (rotMat._12 * newDir.y) + (rotMat._13 * newDir.z);
			newDir.z = (rotMat._11 * newDir.x) + (rotMat._12 * newDir.y) + (rotMat._13 * newDir.z);
			proj.setVelocity(newDir);
		}
		else
		{
			D3DXMatrixRotationY(&rotMat, -ENEMY_MISSILE_TURN_RADIUS);
			newDir.x = (rotMat._11 * newDir.x) + (rotMat._12 * newDir.y) + (rotMat._13 * newDir.z);
			newDir.y = (rotMat._11 * newDir.x) + (rotMat._12 * newDir.y) + (rotMat._13 * newDir.z);
			newDir.z = (rotMat._11 * newDir.x) + (rotMat._12 * newDir.y) + (rotMat._13 * newDir.z);
			proj.setVelocity(newDir);
		}
	}
	else
	{
		D3DXMatrixRotationY(&rotMat, angle);
		newDir.x = (rotMat._11 * newDir.x) + (rotMat._12 * newDir.y) + (rotMat._13 * newDir.z);
		newDir.y = (rotMat._11 * newDir.x) + (rotMat._12 * newDir.y) + (rotMat._13 * newDir.z);
		newDir.z = (rotMat._11 * newDir.x) + (rotMat._12 * newDir.y) + (rotMat._13 * newDir.z);
		proj.setVelocity(newDir);
	}

	// Uncomment if needed
	//proj.setPosition(proj.getPosition() += newDir * dt);

	// TODO: Modify orientation of projectile

	// TODO: Add check for missile lifetime to see if it has run out of time
}