#pragma once
//#include <stdio.h>
//#pragma comment(lib, "winmm.lib")

#include <d3d9.h>
// #include <d3dx9.h>
// #include <DxErr.h>
// #pragma comment(lib, "dxerr.lib")
// #pragma comment(lib, "d3d9.lib")

//////////////////////////////////////////////////////////////////////////
// FMOD headers and libraries
// Note: Must have FMOD Ex installed, and copy the files listed below into
// your source directory for this project found in the following FMOD folder
// <Install Path>\FMOD SoundSystem\FMOD Programmers API Win32\api\inc, 
// <Install Path>\FMOD SoundSystem\FMOD Programmers API Win32\api\lib,
// <Install Path>\FMOD SoundSystem\FMOD Programmers API Win32\api\,
//////////////////////////////////////////////////////////////////////////
#include "fmod.hpp"
//#include "fmod_common.h"
#include <fmod_errors.h>
#pragma comment(lib, "fmodex_vc.lib")

// if the above includes aren't being found you need to make sure that you
// 1) have the fmod dll in the folder with the code
// 2) have put the fmod library and include files in the project properties
using FMOD::Channel;
using FMOD::Sound;
using FMOD::System;


// To use
// 1) #include this file
// 2) create a Sound variable member in the class needing the sound

// For sound effects:
// 3) use global SoundSystem variable to initialize sound variable
//    FR(gSound->getSystem()->createSound("file/location", FMOD_DEFAULT, 0, &soundVariable);
// 4) play sound effect when needed
//    gSound->getSystem()->playSound(FMOD_CHANNEL_FREE, soundVariable, flase, 0);
// For music
// 3) use global SoundSystem variable to initialize sound stream variable
//    FR(gSound->getSystem()->createStream("file/location", FMOD_DEFAULT, 0, &soundVariable);
// 4) end previous music and begin the new one
//    gSound->getChannel()->stop();
//    FR(gSound->getSystem()->playSound(FMOD_CHANNEL_FREE, soundVariable, false, NULL);

// 5) release sound or stream in destructor
//    FR(soundVariable->release());



namespace AudioCore
{

#if defined(DEBUG) | defined(_DEBUG)
#ifndef FR
#define FR(x)										\
	{													\
		FMOD_RESULT fr = x;								\
		if(fr != FMOD_OK)								\
														{												\
						wchar_t* wString = new wchar_t[1024]; \
						MultiByteToWideChar(CP_ACP, 0, FMOD_ErrorString(fr), -1, wString, 1024); \
						OutputDebugString(wString);	\
												}												\
	}
#endif
#else
#ifndef FR
#define FR(x) x;
#endif
#endif

	class AudioSystem
	{
		//////////////////////////////////////////////////////////////////////////
		// FMOD 
		//////////////////////////////////////////////////////////////////////////

		System				*mSystem;
		//channel for music
		Channel*			mChannel;
		FMOD_RESULT      	result;
		unsigned int     	version;
		int              	numdrivers;
		FMOD_SPEAKERMODE 	speakermode;
		FMOD_CAPS        	caps;


	public:
		AudioSystem();
		~AudioSystem();
		System* getSystem() { return mSystem; };
		Channel* getChannel() { return mChannel; }
	private:
		void init();
	};

	extern AudioSystem* gSound;

}