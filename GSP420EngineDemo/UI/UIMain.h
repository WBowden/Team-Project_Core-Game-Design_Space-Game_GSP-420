// UIMain.h
// Written by Chris Randall unless otherwise noted
#pragma once
#include "..\EngineDemo\GameState.h"
#include "..\D3D9Graphics\GFX.h"
#include "defines.h"
#include <vector>
#include "..\Main\DirectInput.h"
#include "..\Main\Player.h"
#include "..\EngineDemo\Game.h"
#include "..\EngineDemo\GameState.h"
using namespace std;
using GFXCore::SpriteData;


class UIMain {
protected:
	Player * player;
	GAMESTATE currentState;
	//GFXCore::Graphics gfx;
	// Stores the position of sprites that LoadSprite loads into an array so that they can be accessed later
	vector<int> menuSpriteIDs;
	vector<int> gameSpriteIDs;
	vector<int> pauseSpriteIDs;
	vector<int> exitSpriteIDs;
	int currentScore;
	int missileAmmo;
	RECT hpBarSize;

private:
	//Pseudocode written by Aaron Vienneau
	bool spriteClicked(float x, float y, int spriteID)
	{
		if (x >  GFXCore::Graphics::get()->getSpritePosX(spriteID) 
			&& x < GFXCore::Graphics::get()->getSpritePosX(spriteID) + GFXCore::Graphics::get()->getSpriteWidth(spriteID))
		{
			if (y > GFXCore::Graphics::get()->getSpritePosY(spriteID)
				&& y < GFXCore::Graphics::get()->getSpritePosY(spriteID) + GFXCore::Graphics::get()->getSpriteHeight(spriteID))
			{
				return true;
			}
		}
		return false;
	}
public:

	UIMain(): currentState(STATE_INIT), currentScore(0), missileAmmo(0) {
//		player = &(PLAYER);//Instance()->player);
		hpBarSize.top = 350;
		hpBarSize.bottom = 400;
		hpBarSize.left = 100;
		hpBarSize.right = 500;
	}
	~UIMain() {}

	
	void updateMenu(float x, float y) {
		// tells graphics what to draw
		GFX->addToSpriteRenderList(&menuSpriteIDs[0], menuSpriteIDs.size());

		// check for mouse input
		int MOUSE_LEFT = 0;
		if(spriteClicked(x, y, menuSpriteIDs[2]))
		{
			currentState = STATE_PLAY;
		}

		if (spriteClicked(x, y, menuSpriteIDs[3]))
		{
			currentState = STATE_CREDIT;
		}
	}

	// Game update written by Bill Bowden
	void updateGame(Player & player) {
		int healthSize = player.getMaxHealth();
		int currAmmo = player.getMissileAmmo();
		// tells graphics what to draw
		GFX->addToSpriteRenderList(&gameSpriteIDs[0], gameSpriteIDs.size());

		//Health bar update
		for (healthSize; healthSize > player.getHealth(); --healthSize) //reduce the health bar size from the difference.
		{
			hpBarSize.right = 500 * (healthSize / 100);
			// TODO: SAM: commented out tillI fix the background issue
			GFX->updateSprite(gameSpriteIDs.at(3), D3DXVECTOR3(350, 400, 0.0f), hpBarSize); // update the information
		}

		//Missle Bar Update
	}

	void updatePause(const bool paused) {
		if (paused)
		{
			GFX->addToSpriteRenderList(&pauseSpriteIDs[0], pauseSpriteIDs.size());
		}
	}
	void updateCredits(float x, float y) {
		// tell Graphics which sprites to draw
		GFX->addToSpriteRenderList(&exitSpriteIDs[0], exitSpriteIDs.size());
		currentState = STATE_CREDIT;

		if (spriteClicked(x, y, exitSpriteIDs[0])) {
			currentState = STATE_MENU;
		}
	}
	void updateExit() {
		// tell Graphics which sprites to draw
		//GFX->addToSpriteRenderList(&exitSpriteIDs[0], exitSpriteIDs.size());
		currentState = STATE_EXIT;
	}
};