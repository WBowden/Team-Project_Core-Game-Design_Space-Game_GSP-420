/* App class created by Darrell Smith and edited by Brent Spector*/

#pragma once

class App
{
public:
	
protected:
	App() {}
	virtual ~App() {}
	//framework methods for Game class to use
	virtual void init() { QuitNow = false; }//used upon game startup
	virtual void onLostDevice() {}//used when screen changes size or other event causes device to be lost
	virtual void onResetDevice() {}//used after onLostDevice to reaquire needed elements
	virtual void update(const float) {}//update the scene every frame, anything that is not rendering goes here
	virtual void render() {}//render all the visual elements of the game
	virtual void shutdown() {}//used upon game exit
								//other methods
	bool IsDeviceLost();//check to see if the device was lost
	//set to true when it's time to quit
	bool QuitNow;
private:
	//make copy and assignment operators private and empty so only one copy can be made
	App(App const&) {};
	App& operator=(App const&) {}
};

