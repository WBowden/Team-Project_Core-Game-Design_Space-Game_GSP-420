/* App class created by Darrell Smith and edited by Brent Spector*/
#include "App.h"

#include <Windows.h>

#include "Logger.h"
#include "../D3D9Graphics/GFX.h"



bool App::IsDeviceLost()
{
	// Get the state of the graphics device.
	if (GFX->isDeviceLost())
	{
		onLostDevice();
		onResetDevice();
		return true;
	}
	return false;
}
