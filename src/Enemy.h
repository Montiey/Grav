#include <Arduino.h>
#include <Gamebuino.h>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
	public:
		bool alive;	//1u = 100
		int posX;
		int posY;
		int vX;
		int vY;
		byte hitBoxX;
		byte hitBoxY;
		Gamebuino enemyGameObj;
		Enemy(bool);
		const void update(const Gamebuino&);

	private:
};

#endif
