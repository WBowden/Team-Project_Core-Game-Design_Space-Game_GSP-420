//Projectile Manager, Bullet, and Missile classes created by Darrell Smith and Brent Spector
#include "ProjectileManager.h"

#include "Game.h"
#include "GFX.h"

void ProjectileManager::update(const float dt)
{
	int screenRadX = (GFX->windowWidth()) / 2 + 10;
	int screenRadY = (GFX->windowHeight()) / 2 + 10;

	std::list<Bullet*>::iterator it1 = Bullets.begin();
	while (it1 != Bullets.end())
	{
		if (!(*it1)->isEnabled() )
		{
			delete *it1;
			*it1 = NULL;
			it1 = Bullets.erase(it1);
		}
		else
		{	
			(*it1)->setPosition(D3DXVECTOR3((*it1)->getPhys().x, (*it1)->getPhys().y, 0.0f)/*it1->getPhys().x + it1->getVelocity() * BULLET_SPEED * dt*/);
			(*it1)->init(nBulletModelId, nBulletTextureId);
			GFX->addToModelRenderList(*it1);
			++it1;
		}
	}
	std::list<Missile*>::iterator it2 = Missiles.begin();
	while (it2 != Missiles.end())
	{
		if (!(*it2)->isEnabled()) {
			delete *it2;
			*it2 = NULL;
			it2 = Missiles.erase(it2);
		}
		else {
			(*it2)->setPosition(D3DXVECTOR3((*it2)->getPhys().x, (*it2)->getPhys().y, 0.0f));
			(*it2)->init(nMissileModelId, nMissileTextureId);
			GFX->addToModelRenderList(*it2);
			++it2;
		}
	}
}

void ProjectileManager::removeTarget(Enemy* targ)
{
	for (std::list<Missile*>::iterator it = Missiles.begin(), end = Missiles.end();
	it != end; ++it)
	{
		//if it is a player missile and has a matching target, set the target to NULL instead
		if ((*it)->getEnemyTarget() == targ)
		{
			(*it)->setEnemyTarget(NULL);
		}
	}
}

void ProjectileManager::initBulletProjectiles(const int modelId, const int textureId)
{
	nBulletModelId = modelId;
	nBulletTextureId = textureId;
}

void ProjectileManager::initMissileProjectiles(const int modelId, const int textureId)
{
	nMissileModelId = modelId;
	nMissileTextureId = textureId;
}

void ProjectileManager::clear()
{
	std::list<Bullet*>::iterator bItr;
	for (bItr = Bullets.begin(); bItr != Bullets.end(); ++bItr) {
		if (*bItr) {
			delete *bItr;
			*bItr = NULL;
		}
	}

	std::list<Missile*>::iterator mItr;
	for (mItr = Missiles.begin(); mItr != Missiles.end(); ++mItr) {
		if (*mItr) {
			delete *mItr;
			*mItr = NULL;
		}
	}

	Bullets.clear(); 
	Bullets.resize(0);
	Missiles.clear(); 
	Missiles.resize(0);
}

//Missile::Missile(const D3DXVECTOR3 pos, const ObjType t, Enemy* targ/* = NULL*/) :
//ABC(pos, D3DXVECTOR3(0.f, 0.f, 0.f), t), target(targ)
//{
// 	static int id = 0;
// 	physObj.x = pos.x;
// 	physObj.y = pos.y;
// 	std::string missileNme = "PlayerMissile" + to_string(id);
// 	++id;
// 	GAMECLASS->GetPhysics()->GameObjectManager->addBoxDynamicRigidBody(missileNme, 0, 0, 5, 5, true, &physObj);
// 	physObj.setCollissionCategory((uint16)gameObjectCollissionCategory::gocMISSLE); // I am a missile
// 	physObj.setCollissionMask((uint16)gocBOUNDARY || gocENEMY); // i can collide with 

//}
