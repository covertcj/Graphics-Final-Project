/*
 * Timer.h
 *
 *  Created on: Oct 28, 2010
 *      Author: covertcj
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <SDL/SDL.h>

class Timer {
public:
	Timer(void);
	virtual ~Timer(void);

	void static Initialize(void);
	void static Update(void);
	void static Destroy(void);

	/*!
	 * @return The seconds elapsed between the last two updates.
	 *
	 * Getter for the dt varaible.
	 */
	float static GetDT(void);
	/*!
	 * @return The milliseconds elapsed between the last two updates.
	 *
	 * Getter for the dt varaible.
	 */
	unsigned int static GetDTMilliseconds(void);

private:
	/*!
	 * The seconds elapsed between the last two updates.
	 */
	static float ms_fDT;
	/*!
	 * The milliseconds between SDL initialization and the last
	 * timer update.
	 */
	static unsigned long ms_lLastTick;
	/*!
	 * The milliseconds between SDL initialization and this most
	 * recent timer update.
	 */
	static unsigned long ms_lThisTick;
};

#endif /* TIMER_H_ */
