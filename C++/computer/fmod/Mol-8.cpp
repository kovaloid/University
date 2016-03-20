#include "stdafx.h"
#include <conio.h> 
#include <windows.h>
#include "inc\fmod.hpp"
#include "inc\fmod_errors.h"
#include <iostream>
#pragma comment(lib, "fmodex_vc.lib")

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	// FMOD 4	
	FMOD_RESULT result;
	FMOD::System * system; 
	result = FMOD::System_Create(&system);
	result = system->init(16, FMOD_INIT_NORMAL, 0);
	FMOD::Sound * sound; // sound
	FMOD::Channel * channel; // sound channel
	result = system->createSound("jules.mp3", FMOD_3D, 0, &sound); // creating sound
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, 0);

	for (int i=-10000; i<10000; i++) {
		FMOD_VECTOR listenerpos = {i/2000, 0.0f, 0.0f};
		result = system->set3DListenerAttributes(0,&listenerpos, 0, 0, 0);
		result = system->update();
		std::cout<<i<<", ";
	}

	// playing sound (assigning it to a channel)
	//channel->setPaused(false); // actually play sound

	getch();
	return 0;
}

