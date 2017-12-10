#include <Arduino.h>
#include <Gamebuino.h>

#ifndef ENEMY_H
#define ENEMY_H

const byte enemy[] PROGMEM = {
	4, 4,
	B01100000,
	B10010000,
	B10010000,
	B01100000,
};

class Enemy{
	public:
		bool alive;
		int posX;
		int posY;
		int vX;
		int vY;
		byte hitBoxX;
		byte hitBoxY;
		Gamebuino enemyGameObj;
		Enemy(bool);
		void update(const Gamebuino&);
		void reset(bool);
};

#endif
