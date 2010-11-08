/*
 * Level.h
 *
 *  Created on: Nov 7, 2010
 *      Author: covertcj
 */

#ifndef LEVEL_H_
#define LEVEL_H_

class Level {
public:
	Level(void);
	virtual ~Level(void);

	void Initialize(void);

	void Update(void);
	void Draw(void);
};

#endif /* LEVEL_H_ */
