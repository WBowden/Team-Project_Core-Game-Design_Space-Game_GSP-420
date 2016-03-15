#include "EnemyManager.h"

#include "Game.h"
#include "Logger.h"

Enemy::Enemy(D3DXVECTOR3 pos, ObjType t) : ABC(pos, t), damage(0),
	bulletFireRate(-1.f), missileFireRate(-1.f), mineFireRate(-1.f)
{
	switch (t)
	{
	case OT_ENEMY1:
		nHealth = ENEMY_1_HEALTH;
		score = ENEMY_1_SCORE;
		break;
	case OT_ENEMY2:
		nHealth = ENEMY_2_HEALTH;
		score = ENEMY_2_SCORE;
		break;
	case OT_ENEMY3:
		nHealth = ENEMY_3_HEALTH;
		score = ENEMY_3_SCORE;
		break;
	case OT_ENEMYBOSS:
		nHealth = ENEMY_BOSS_HEALTH;
		score = ENEMY_BOSS_SCORE;
		break;
	default:
		LOGGER->Write(L"Enemy:Enemy: Invalid type of enemy!");
	}
}

void Enemy::fireBullet(D3DXVECTOR3 vel)
{
	Bullet* b = new Bullet(OT_ENEMY_BULLET);
	ENEMIES.incNextBulletID();
	string name = "EnemyBullet" + to_string(ENEMIES.getNextBulletID());
	GAMECLASS->GetPhysics()->GameObjectManager->addBoxDynamicRigidBody(name,
								physObj.x, physObj.y, BULLET_SIZE, BULLET_SIZE, true, &b->physObj);
	b->physObj.setCollissionCategory((uint16)gameObjectCollissionCategory::gocMISSLE);
	b->physObj.setCollissionMask((uint16)gocPLAYER | gocBOUNDARY);
	b->physObj.applyImpulseFromCenter(vel.x, vel.y);
	//create projectile starting at current position
	PROJECTILES.addBullet(b);
}

//Created by Darrell Smith and Brent Spector

void Enemy::fireMissile(D3DXVECTOR3 vel)//or auto-target the one existing player?
{
	//create missile with position and target, velocity will be determined by target
	//PROJECTILES.addMissile(&(Missile(position, OT_ENEMY_MISSILE)));
}

void Enemy::dropMine()
{
	PICKUPS.add(Pickup(position, PU_MINE));
}

void EnemyManager::add(Enemy e)
{
	Enemies.push_front(e);
}

void EnemyManager::update(const float dt)
{
	std::list<Enemy>::iterator it = Enemies.begin();
	while (it != Enemies.end())
	{
		//it->update(dt);
		if (it->getDamage() >= it->getHealth())
		{
			//check if any missiles are targeting it and  mark their target as NULL for re-targeting
			PROJECTILES.removeTarget(&*it);
			//give player score
			PLAYER.giveScore(it->getScore());
			//possibly give projectile
			int pickupChance = rand() % 100;
			if (pickupChance < GET_HEALTH_CHANCE)
				PICKUPS.add(Pickup(it->getPosition(), PU_HEALTH));
			else if (pickupChance < GET_HEALTH_CHANCE + GET_INVULNERABLE_CHANCE)
				PICKUPS.add(Pickup(it->getPosition(), PU_INVULNERABLE));
			else if (pickupChance < GET_HEALTH_CHANCE + GET_INVULNERABLE_CHANCE + GET_MISSILES_CHANCE)
				PICKUPS.add(Pickup(it->getPosition(), PU_MISSILE));
			//then delete
			it = Enemies.erase(it);
		}
		else
		{
			++it;
		}
	}
}

