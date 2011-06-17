#include <string>
#include <iostream>

#include "Timer.h"

#define TIMER nsUtil::Timer

TIMER::Timer(void) {
	//Initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
	std::cout << "Timer ()" << std::endl;
}

TIMER::~Timer(void) {
}

void TIMER::start(void) {
	//Start the timer
	started = true;

	//Unpause the timer
	paused = false;

	//Get the current clock time
	startTicks = SDL_GetTicks();

	std::cout << "Timer started" << std::endl;
}

void TIMER::stop(void) {
	//Stop the timer
	started = false;

	//Unpause the timer
	paused = false;
}

void TIMER::pause(void) {
	//If the timer is running and isn't already paused
	if ((started == true) && (paused == false)) {
		//Pause the timer
		paused = true;

		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void TIMER::unpause(void) {
	//If the timer is paused
	if (paused == true) {
		//Unpause the timer
		paused = false;

		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

int TIMER::getTicks(void) {
	//If the timer is running
	if (started == true) {
		//If the timer is paused
		if (paused == true) {
			//Return the number of ticks when the timer was paused
			return pausedTicks;
		} else {
			//Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}

	//If the timer isn't running
	return 0;
}

bool TIMER::isStarted(void) {
	return started;
}

bool TIMER::isPaused(void) {
	return paused;
}

#undef TIMER
