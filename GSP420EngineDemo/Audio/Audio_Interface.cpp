#include "Audio_Interface.h"

using namespace AudioCore;

AudioCore::Audio_Interface::Audio_Interface(void)
{

}

AudioCore::Audio_Interface::~Audio_Interface(void)
{

}

void AudioCore::Audio_Interface::Init()
{

	gSound = new AudioSystem(); //Set Com for sound in APP window


								//////////////////////////////////////////////////////////////////////////
								// Initialize FMOD w/ FR wrapper
								//////////////////////////////////////////////////////////////////////////
								//Test sound by Paul
	FR(gSound->getSystem()->createSound("Laser.wav", FMOD_DEFAULT, 0, &Laser));
	FR(gSound->getSystem()->createSound("AutoFire.wav", FMOD_DEFAULT, 0, &AutoFire));
	FR(gSound->getSystem()->createSound("CannonFire.wav", FMOD_DEFAULT, 0, &CannonFire));
	FR(gSound->getSystem()->createSound("AsteriodExploding.wav", FMOD_DEFAULT, 0, &AsteriodExploding));
	FR(gSound->getSystem()->createSound("ButtonSelect.wav", FMOD_DEFAULT, 0, &ButtonSelect));




	//////////////////////////////////////////////////////////////////////////
	// Initialize DirectShow / directly add due to issues w/ wrapper HR
	//////////////////////////////////////////////////////////////////////////

	// Initialize COM
	CoInitialize(NULL);

}
void AudioCore::Audio_Interface::Laser_SFX()
{ //SAM: commented these out for they cause a compiler error
	//FR(gSound->getSystem->playsound(FMOD_CHANNEL_FREE, Laser, false, NULL))
}
void AudioCore::Audio_Interface::AutoFire_SFX()
{//SAM: commented these out for they cause a compiler error
	//FR(gSound->getSystem->playsound(FMOD_CHANNEL_FREE, AutoFire, false, NULL))
}
void AudioCore::Audio_Interface::CannonFire_SFX()
{//SAM: commented these out for they cause a compiler error
	//FR(gSound->getSystem->playsound(FMOD_CHANNEL_FREE, CannonFire, false, NULL))
}
void AudioCore::Audio_Interface::AsteriodExploding_SFX()
{//SAM: commented these out for they cause a compiler error
	//FR(gSound->getSystem->playsound(FMOD_CHANNEL_FREE, AsteriodExploding, false, NULL))
}
void AudioCore::Audio_Interface::ButtonSelect_SFX()
{//SAM: commented these out for they cause a compiler error
	//FR(gSound->getSystem->playsound(FMOD_CHANNEL_FREE, ButtonSelect, false, NULL))
}

