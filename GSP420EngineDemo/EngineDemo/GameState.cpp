//GameState classes created by Darrell Smith and edited by Brent Spector
#include "GameState.h"

//some things seem to be occurring the same in every state, so some of this may be moved
//back to the main methods in Game

#include "../D3D9Graphics/GFX.h"
#include "../Main/DirectInput.h"
#include "../Main/Logger.h"
#include "Game.h"

void InitState::init()
{
	LOGGER->open();
	INPUT->init(DISCL_NONEXCLUSIVE | DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

//	GAMECLASS->gameAudio.init();
//	GAMECLASS->gameUI.init();
}

void InitState::shutdown()
{
	//need to define because ChangeState automatically calls it, but don't actually need to do anything here
}

void MenuState::init()
{
	//?
}

void MenuState::update(const float dt)
{
	float x = 0, y = 0;
	//	GAMECLASS->gameAudio.update(dt);
	INPUT->Poll();
	// PHYSICS: add 
	int MOUSE_LEFT = 0;
	if (INPUT->MouseButtonDown(MOUSE_LEFT)) {
		x = INPUT->MouseDX(); 
		y = INPUT->MouseDY();
		x = 260; y = 360;
	}
	GAMECLASS->gameUI.update(PLAYER, STATE_MENU, GAMECLASS->paused, x, y);
	GAMECLASS->changeState(GAMECLASS->gameUI.checkStateChanges());
}

void MenuState::render()
{
	GFX->renderScene();
}

void MenuState::onLostDevice()
{
	GFX->onLostDevice();
	//GAMECLASS->gameAudio.onLostDevice();
}

void MenuState::onResetDevice()
{
	GFX->onResetDevice();
	//GAMECLASS->gameAudio.onResetDevice();
}

void MenuState::shutdown()
{
	//?
}

void CreditsState::init()
{
	//?
}

void CreditsState::update(const float dt)
{
	float x = 0, y = 0;
	//	GAMECLASS->gameAudio.update(dt);
	INPUT->Poll();
	// PHYSICS: add 
	int MOUSE_LEFT = 0;
	if (INPUT->MouseButtonDown(MOUSE_LEFT)) {
		x = INPUT->MouseDX();
		y = INPUT->MouseDY();
		x = 260; y = 360;
	}
	// PHYSICS: add update
	//GAMECLASS->gameAudio.update(dt);
	GAMECLASS->gameUI.update(PLAYER, STATE_CREDIT, GAMECLASS->paused, 0,0);
	GAMECLASS->changeState(GAMECLASS->gameUI.checkStateChanges());
}

void CreditsState::render()
{
	GFX->renderScene();
}

void CreditsState::onLostDevice()
{
	GFX->onLostDevice();
	//GAMECLASS->gameAudio.onLostDevice();
}

void CreditsState::onResetDevice()
{
	GFX->onResetDevice();
	//GAMECLASS->gameAudio.onResetDevice();
}

void CreditsState::shutdown()
{
	//?
}

void PlayState::init()
{
	//GAMECLASS->gameAI.init();
	//GAMECLASS->gamePhysics.init();
	GAMECLASS->player = Player();
	PLAYER.init(GAMECLASS->nPlayerModel, -1);
	//PLAYER.init(nPlayerModel, -1);
	PLAYER.setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	PLAYER.setFixedRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//player.toggleEnabled();

	PROJECTILES.initBulletProjectiles(GFX->createSphereMesh(5.0f, 25, 25), -1);
	PROJECTILES.initMissileProjectiles(GFX->createCylinderMesh(5.0f, 15.0f, 5.0f, 25, 25), -1);

	GFX->cameraSetLens(GFX->windowWidth(), GFX->windowHeight(), -1000.0f, 1000.0f);

	gamePhysics->GameObjectManager->addBoxDynamicRigidBody("player", 0, 0, 25, 25, true, &PLAYER.getPhys());
	//load model/texture resources
	//init player
	//PLAYER.init(1,1);//need to get what IDs to use from graphics
	//init graphics textures for ui and pause menu
}

void PlayState::update(const float dt)
{
	static float fixedtime = 0.0f;
	fixedtime += dt;

//	if (fixedtime >= 0.016666666667f)
	{
		//fixedtime -= 0.016666666667f;
		fixedtime = 0.0f;
		INPUT->Poll();

		static float pausecooldown = 0.f;
		if (pausecooldown > 0.f)
			pausecooldown -= dt;
		//GAMECLASS->gameAudio.update(dt);
		//listen for input
		if (INPUT->KeyDown(DIK_P) && pausecooldown <= 0.f)
		{
			GAMECLASS->togglePause();
			pausecooldown = .5f;
		}
		if (GAMECLASS->paused)
		{
			GAMECLASS->gameUI.update(PLAYER, STATE_PLAY, true, 0,0);
		}
		else
		{
			//only do any of this if the player is alive
			if (PLAYER.isEnabled())
			{
				//listen for player input
				//the cool down for bullet and missile firing is built into the player class
				

				// Z AND X Rotate the ship. need code to make allow it to move and face the correct direction : Darrel Hidle.
				if (INPUT->KeyDown(DIK_Z))
					PLAYER.physObj.applyTorqueFromCenter(-PLAYER_SPEED/10);

				if (INPUT->KeyDown(DIK_X))
					PLAYER.physObj.applyTorqueFromCenter(PLAYER_SPEED/10);
				
				if (INPUT->KeyDown(DIK_SPACE))
					PLAYER.fireBullet();
				else
					PLAYER.resetBulletTime();
				if (INPUT->KeyDown(DIK_F))
					PLAYER.fireMissile();
				//player movement
				float x, y;
				if (INPUT->KeyDown(DIK_W) || INPUT->KeyDown(DIK_UP))
					y = PLAYER_SPEED;
				else if (INPUT->KeyDown(DIK_S) || INPUT->KeyDown(DIK_DOWN))
					y = -PLAYER_SPEED;
				else
					y = 0.f;
				if (INPUT->KeyDown(DIK_A) || INPUT->KeyDown(DIK_LEFT))
					x = -PLAYER_SPEED;
				else if (INPUT->KeyDown(DIK_D) || INPUT->KeyDown(DIK_RIGHT))
					x = PLAYER_SPEED;
				else
					x = 0.f;

				PLAYER.getPhys().applyForceFromCenter(x, y);
				D3DXVECTOR3 pos;
				pos.x = (float)PLAYER.getPhys().x;
				pos.y = (float)PLAYER.getPhys().y;
				pos.z = 0.0f;
				PLAYER.setPosition(pos/*PLAYER.getPosition() + PLAYER.getVelocity() * dt * 100*/);
				PLAYER.setFixedRotation(D3DXVECTOR3(0.0, 0.0, PLAYER.physObj.body->GetAngularVelocity()));
			
				//update AI/physics first so they can flag objects
				//GAMECLASS->gameAI.update(dt);
				//GAMECLASS->gamePhysics.update(dt);
				//then we update the objects to see which are flagged
				GAMECLASS->gameUI.update(PLAYER, STATE_PLAY, GAMECLASS->paused, 0,0);
				PLAYER.update(dt);
				ASTEROIDS.update(dt);
				ENEMIES.update(dt);
				PICKUPS.update(dt);
				PROJECTILES.update(dt);
				//GAMECLASS->gameUI.update(dt, STATE_PLAY, GAMECLASS->paused, *INPUT);
				GFX->addToModelRenderList(&PLAYER);
			}
		}
		//after updating, check for any state changes due to UI things
		//GAMECLASS->changeState(GAMECLASS->gameUI.checkStateChanges());
	}
}

void PlayState::render()
{
	GFX->renderScene();
}

void PlayState::onLostDevice()
{
	GFX->onLostDevice();
	//GAMECLASS->gameAudio.onLostDevice();
}

void PlayState::onResetDevice()
{
	GFX->onResetDevice();
	//GAMECLASS->gameAudio.onResetDevice();
}

void PlayState::shutdown()
{
	//clear out previous play stuff from managers
	PLAYER.shutdown();
	ASTEROIDS.clear();
	ENEMIES.clear();
	PICKUPS.clear();
	PROJECTILES.clear();
	//unload models/textures for game play, UI, pause menu
	//GAMECLASS->gameAI.shutdown();
	//GAMECLASS->gamePhysics.shutdown();
}


void ExitState::init()
{
	
	
	LOGGER->close();
	//unload main graphics/UI/audio resources and then quit
	//GAMECLASS->gameUI.shutdown();
	//GAMECLASS->gameAudio.shutdown();
	GFX->shutdown();
	INPUT->shutdown(); 
//	GAMECLASS->gamePhysics.endWorld();
}


