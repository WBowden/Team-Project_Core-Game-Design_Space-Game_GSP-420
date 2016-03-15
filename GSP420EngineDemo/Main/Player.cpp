//Player class created by Darrell Smith and edited by Brent Spector
#include "Player.h"

#include "Game.h"
#include "GFX.h"

void Player::fireBullet()
{
	//create bullet with velocity and position
	if (lastBullet <= 0)
	{
		Bullet* b = new Bullet(OT_PLAYER_BULLET);
		static int id = 0;
		++id;
		string name = "PlayerBullet" + to_string(id);
		gamePhysics->GameObjectManager->addBoxDynamicRigidBody(name,
			physObj.x, physObj.y, BULLET_SIZE, BULLET_SIZE, true, &b->physObj);
	//	b.physObj.setCollissionCategory((uint16)gameObjectCollissionCategory::gocMISSLE);
	//	b.physObj.setCollissionMask((uint16)gocENEMY | gocBOUNDARY);
		b->physObj.applyImpulseFromCenter(BULLET_START_DIRECTION.x, BULLET_START_DIRECTION.y);

		PROJECTILES.addBullet(b);
		lastBullet = BULLET_COOL_DOWN;
	}
}

void Player::fireMissile()
{
	if (lastMissile <= 0 && missileAmmo > 0)
	{
		//create missile with velocity, position, and target
		//Missile* m = new Missile(position, OT_PLAYER_MISSILE);
		Missile* m = new Missile(OT_PLAYER_MISSILE);

		//m.init(1, 1); need to find out what to use for IDs from graphics
		static int id = 0;
		++id;

		std::string missileNme = "PlayerMissile" + to_string(id);
		
		gamePhysics->GameObjectManager->addBoxDynamicRigidBody(missileNme,
												physObj.x, physObj.y, MISSILE_RADIUS, MISSILE_RADIUS, true, &m->physObj);
// 		m->physObj.setCollissionCategory((uint16)gameObjectCollissionCategory::gocMISSLE); // I am a missile
// 		m->physObj.setCollissionMask((uint16)gocBOUNDARY || gocENEMY); // i can collide with 
		m->physObj.applyImpulseFromCenter(0.0f, MISSILE_SPEED);

		PROJECTILES.addMissile(m);
		--missileAmmo;
		lastMissile = MISSILE_COOL_DOWN;
	}
}

void Player::heal(int h)
{
	//set to minimum of (health + h) and maxHealth without branching
	int newHealth = nHealth + h;
	nHealth = maxHealth + ((newHealth - maxHealth) & ((newHealth - maxHealth) >> 31));
}

void Player::hurt(int h)
{
	if (invulnerable <= 0.f)//only if player isn't invulnerable
	{
		nHealth -= h;//set health
		//see if dead
		if (nHealth <= 0)
		{
			endGame();
		}
		//set invulnerability when hit again
		invulnerable = HURT_INVULNERABILITY;
	}
}

void Player::move(D3DXVECTOR3 move)
{
	//rather than set position, we set velocity so that physics can check for collisions
	//before they are moved
	D3DXVec3Normalize(&velocity, &move);
}

void Player::endGame()
{
	//end game
	bEnabled = false;
}

void Player::update(const float dt)
{
	//make sure we don't go offscreen
	int screenRadX = (GFX->windowWidth()) / 2 - 20;
	int screenRadY = (GFX->windowHeight()) / 2 - 20;

	/*

	 should not change player x and y it will mess with physics. 
	if (physObj.x < -screenRadX)	physObj.x = -screenRadX;
	if (physObj.x > screenRadX)		physObj.x = screenRadX;
	if (physObj.y < -screenRadY)	physObj.y = -screenRadY;
	if (physObj.y > screenRadY)		physObj.y = screenRadY;

	*/

	//Instead apply an force to keep it from going 
	if (physObj.x < -screenRadX) physObj.applyForceFromCenter(PLAYER_SPEED, 0.0);
	if (physObj.x > screenRadX)	 physObj.applyForceFromCenter(-PLAYER_SPEED, 0.0);
	if (physObj.y < -screenRadY) physObj.applyForceFromCenter(0.00, PLAYER_SPEED);
	if (physObj.y > screenRadY)	 physObj.applyForceFromCenter(0.00, -PLAYER_SPEED);

	//count timers
	if (invulnerable > 0.f)
		invulnerable -= dt;
	if (lastBullet > 0.f)
		lastBullet -= dt;
	if(lastMissile > 0.f)
		lastMissile -= dt;

}

void Player::shutdown()
{
	// TODO: Fix later, for now just to test missiles
	missileAmmo = 5;
	/*missileAmmo = */score = 0; 
	nHealth = maxHealth = 25; 
	invulnerable = lastBullet = lastMissile = 0.f;
}

void Player::makeInvulnerable(float secs)
{ 
	if(secs > invulnerable)
		invulnerable = secs; 
}
