#include <Arduino.h>
#include <Montiey_Util.h>
#include <Enemy.h>
#include <Gamebuino.h>

#define enemySize 4

const byte enemy[] PROGMEM = {
	4, 4,
	B01100000,
	B10010000,
	B10010000,
	B01100000,
};

Enemy::Enemy(bool startAlive){
	alive = startAlive;
	hitBoxX = 84-enemySize;
	hitBoxY = 48-enemySize;
	vX = random(-100, 100)/100.0;
	vY = random(-100, 100)/100.0;
}

const void Enemy::update(const Gamebuino &enemyGameObj){
	if(alive){
		posX += vX/100;
		posY += vY/100;
		if(clampBounds(posX, hitBoxX, 0)){
			vX *= -1;
			vX *= random(90, 110)/100.0;
			vY *= random(90, 110)/100.0;
		}
		if(clampBounds(posY, hitBoxY, 0)){
			vY *= -1;
		}
		enemyGameObj.display.drawBitmap(posX, posY, enemy);
	}
}
