/*
 * Timer.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: covertcj
 */

#include "Timer.h"

float Timer::ms_fDT = 0;
unsigned long Timer::ms_lLastTick = 0;
unsigned long Timer::ms_lThisTick = 0;

Timer::Timer() {
	// TODO Auto-generated constructor stub

}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::Initialize(void) {
	// initialize the ticks to a value
	ms_lThisTick = SDL_GetTicks();
	ms_lLastTick = ms_lThisTick;

	ms_fDT = 0.0f;
}

void Timer::Update(void) {
	ms_lLastTick = ms_lThisTick;
	ms_lThisTick = SDL_GetTicks();

	// convert to change in seconds
	ms_fDT = (float) (ms_lThisTick - ms_lLastTick)
			/ 1000.0f;
}

void Timer::Destroy(void) {
	// do nothing
	return;
}

float Timer::GetDT(void) {
	return ms_fDT;
}

unsigned int Timer::GetDTMilliseconds(void) {
	return ms_lThisTick - ms_lLastTick;
}
