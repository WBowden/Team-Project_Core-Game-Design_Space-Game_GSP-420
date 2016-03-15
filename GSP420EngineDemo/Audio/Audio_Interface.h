#pragma once
//#include <stdio.h>
//#pragma comment(lib, "winmm.lib")

//////////////////////////////////////////////////////////////////////////
// Audio & Video headers and libraries required
//////////////////////////////////////////////////////////////////////////
#include "Audio.h"

namespace AudioCore
{
	class Audio_Interface
	{

		Sound*				Laser;
		Sound*				AutoFire;
		Sound*				CannonFire;
		Sound*				AsteriodExploding;
		Sound*				ButtonSelect;


	public:
		//////////////////////////////////////////////////////////////////////////
		// Init and Shutdown are preferred to constructors and destructor,
		// due to having more control when to explicitly call them when global.
		//////////////////////////////////////////////////////////////////////////
		Audio_Interface(void);
		~Audio_Interface(void);
		void Laser_SFX();
		void AutoFire_SFX();
		void CannonFire_SFX();
		void AsteriodExploding_SFX();
		void ButtonSelect_SFX();


		//////////////////////////////////////////////////////////////////////////
		// Name:		Init
		// Parameters:	HWND hWnd - Handle to the window for the application
		//				HINSTANCE hInst - Handle to the application instance
		//				bool bWindowed - Boolean to control windowed or full-screen
		// Return:		void
		// Description:	Ran once at the start.  Initialize DirectX components and 
		//				variables to control the application.  
		//////////////////////////////////////////////////////////////////////////
		void Init();
	};
}