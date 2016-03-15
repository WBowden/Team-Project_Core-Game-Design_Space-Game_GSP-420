//GameState classes created by Darrell Smith and edited by Brent Spector
#pragma once


enum GAMESTATE { STATE_INIT, STATE_MENU, STATE_CREDIT, STATE_PLAY, STATE_EXIT };
const static int NUM_STATES = 5;

class GameState
{
	//only the game class can use the states
	friend class Game;
public:
	GameState() {}
	~GameState() {}
protected:
	virtual void init() {}
	virtual void update(const float) {}
	virtual void render() {}
	virtual void onLostDevice() {}
	virtual void onResetDevice() {}
	virtual void shutdown() {}
};

class InitState : public GameState
{
public:
	InitState() {}
	~InitState() {}
private:
	virtual void init();
	virtual void shutdown();
};

class MenuState : public GameState
{
public:
	MenuState() {}
	~MenuState() {}
private:
	virtual void init();
	virtual void update(const float);
	virtual void render();
	virtual void onLostDevice();
	virtual void onResetDevice();
	virtual void shutdown();
};

class CreditsState : public GameState
{
public:
	CreditsState() {}
	~CreditsState() {}
private:
	virtual void init();
	virtual void update(const float);
	virtual void render();
	virtual void onLostDevice();
	virtual void onResetDevice();
	virtual void shutdown();
};

class PlayState : public GameState
{
public:
	PlayState() {}
	~PlayState() {}
private:
	virtual void init();
	virtual void update(const float);
	virtual void render();
	virtual void onLostDevice();
	virtual void onResetDevice();
	virtual void shutdown();
};

class ExitState : public GameState
{
public:
	ExitState() {}
	~ExitState() {}
private:
	virtual void init();
};

