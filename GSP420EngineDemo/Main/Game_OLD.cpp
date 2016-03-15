//Game class created by Darrell Smith and edited by Brent Spector

#include "Game.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "../D3D9Graphics/GFX.h"
#include "DirectInput.h"
#include "Logger.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, int)
{
	srand((unsigned)time(NULL));
	if (!GFX->initGFX(hInstance, L"Space Game"))
		LOGGER->Write(L"WinMain: Could not initialized graphics core", true);
	Game::Instance()->Run();
	Game::Instance()->Delete();
	return 1;
}

void Game::Run()
{
	
	//initialize timing
	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)& cntsPerSec);
	float secsPerCnt = 1.f / (float)cntsPerSec;
	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)& prevTimeStamp);
	//loop until it's time to quit
	init();
	while (!QuitNow)
	{
		//keep windows busy
		MSG msg;
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if(msg.message == WM_CLOSE || msg.message == WM_QUIT)
				QuitNow = true;
		}
		//check if device is lost, run code if it isn't, otherwise IsDeviceLost() will
		//reset things
		if (!IsDeviceLost())
		{
			__int64 currTimeStamp = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
			float dt = (currTimeStamp - prevTimeStamp)*secsPerCnt;
			update(dt);
			render();
			//current time stamp becomes the previous time stamp for the next iteration.
			prevTimeStamp = currTimeStamp;
		}
	}
	shutdown();
}

//global initialization to facilitate singleton design pattern
Game* Game::Singleton = NULL;

//retrieve singleton instance
Game* Game::Instance()
{
	if (Singleton == 0)
		Singleton = new Game;
	return Singleton;
}

void Game::Delete()
{
	if (Singleton)
	{
		delete Singleton;
		Singleton = NULL;
	}
}

void Game::init()
{
	App::init();
	States[STATE_INIT] = InitState();
	States[STATE_MENU] = MenuState();
	States[STATE_CREDIT] = CreditsState();
	States[STATE_PLAY] = PlayState();
	States[STATE_EXIT] = ExitState();
	//will always start with the Init and then Menu states
	States[STATE_INIT].init();
	States[STATE_MENU].init();
	State = STATE_MENU;
	QuitNow = false;

}

void Game::onLostDevice()
{
	States[State].onLostDevice();
}

void Game::onResetDevice()
{
	States[State].onLostDevice();
}

void Game::update(const float dt)
{
	States[State].update(dt);
}

void Game::render()
{
	States[State].render();
}

void Game::shutdown()
{
	//will always end by exiting through the menu state
	States[STATE_MENU].shutdown();
	States[STATE_EXIT].shutdown();

}

void Game::changeState(GAMESTATE newstate)
{
	if(newstate != State)
	{
		States[State].shutdown();
		State = newstate;
		States[State].init();
		paused = false;
	}
}
