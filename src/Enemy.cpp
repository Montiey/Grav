#include <Arduino.h>
#include <Montiey_Util.h>
#include <Enemy.h>
#include <Gamebuino.h>

#define enemyDefaultSpeed 200
#define reboundDeltaV 10

#define enemySize 4
#define hitBoxX (84-enemySize) * 100
#define hitBoxY (48-enemySize) * 100

int getDeltaV(){
	return random(100-reboundDeltaV, 100+reboundDeltaV);
}

Enemy::Enemy(bool startAlive){
	alive = startAlive;

	vX = enemyDefaultSpeed;
	vY = enemyDefaultSpeed;

	posX = hitBoxX/2;
	posY = hitBoxY/2;
}

void Enemy::update(const Gamebuino &enemyGameObj){
	if(alive){
		posX += vX;
		posY += vY;

		if(clampBounds(posX, 20, hitBoxX)){
			vX = getDeltaV();
			vX *= -1;
			enemyGameObj.sound.playTick();
		}
		if(clampBounds(posY, 20, hitBoxY)){
			vY = getDeltaV();
			vY *= -1;
			enemyGameObj.sound.playTick();
		}

		enemyGameObj.display.drawBitmap(posX/100, posY/100, enemy);
	}
}

void Enemy::reset(bool makeAlive){
	alive = makeAlive;
	posX = hitBoxX/2;
	posY = hitBoxY/2;
	vX = getDeltaV();
	vY = getDeltaV();
}
