#include <Arduino.h>
#include <Gamebuino.h>
#include <EEPROM.h>
#include <Montiey_Util.h>

#include "Bitmaps.cpp"
#include <Enemy.h>

Gamebuino gb;

#define ballSize 4
#define hitBoxX (84-ballSize)
#define hitBoxY (48-ballSize)

#define targetSize 8
#define targetBoxX (84-targetSize)
#define targetBoxY (48-targetSize)

double gravAmmt = 0.1;
#define defaultGrav 0.1
#define targetSpeed 2
#define reboundAmmt 0.5

bool enableGrav = 0;

double ballX = 0;
double ballY = 0;

double ballVX = 0;
double ballVY = 0;

double targetX = hitBoxX/2;
double targetY = hitBoxY/2;

struct timer{
	unsigned long last;
	const unsigned long dur;
	bool active;
};

timer gravTick = {0, 500, 1};
timer textDisplay = {0, 250, 1};

Enemy E1(1);

char* oStr;

void setup() {
	gb.begin();
	gb.setFrameRate(20);
	Serial.begin(250000);
	Serial.println(EEPROM.length());
	titleScreen();
}

void loop() {
	if(gb.update()){

		if(gb.buttons.repeat(BTN_A, 0)) enableGrav = 1;
		else enableGrav = 0;

		if(gb.buttons.pressed(BTN_A)) gb.sound.playOK();
		if(gb.buttons.released(BTN_A)) gb.sound.playCancel();

		if(gb.buttons.pressed(BTN_B)){
			switch(gb.menu(gravMenu, 6)){
				case 0:
					gravAmmt = defaultGrav*1.0;
				break;
				case 1:
					gravAmmt = defaultGrav*2.0;
				break;
				case 2:
					gravAmmt = defaultGrav*4.0;
				break;
				case 3:
					gravAmmt = defaultGrav*8.0;
				break;
				case 4:
					gravAmmt = defaultGrav*16.0;
				break;
				case 5:
					resetBall(0);
					E1.reset(1);
				break;
			}
		}

		ballX += ballVX;
		ballY += ballVY;

		if(clampBounds(ballY, hitBoxY, 0)){
			ballVY *= -reboundAmmt;
		}
		if(clampBounds(ballX, hitBoxX, 0)){
			ballVX *= -reboundAmmt;
		}

		double distX = (targetX + targetSize/2) - (ballX + ballSize/2);
		double distY = (targetY + targetSize/2) - (ballY + ballSize/2);

		double dist = abs(distX) + abs(distY);

		if(enableGrav){
			ballVX += distX / dist * gravAmmt;
			ballVY += distY / dist * gravAmmt;

			gb.display.drawLineDotted(targetX+targetSize/2, targetY+targetSize/2, ballX+ballSize/2, ballY+ballSize/2);
		}

		gb.display.drawBitmap(ballX, ballY, ball);

		if(enableGrav) gb.display.drawBitmap(targetX, targetY, target1);
		else gb.display.drawBitmap(targetX, targetY, target2);

		if(gb.buttons.repeat(BTN_UP, 0)) targetY -= targetSpeed;
		if(gb.buttons.repeat(BTN_DOWN, 0)) targetY += targetSpeed;
		if(gb.buttons.repeat(BTN_LEFT, 0)) targetX -= targetSpeed;
		if(gb.buttons.repeat(BTN_RIGHT, 0)) targetX += targetSpeed;

		clampBounds(targetX, targetBoxX, 0);
		clampBounds(targetY, targetBoxY, 0);

		////////

		E1.update(gb);
	}

	if(gb.buttons.held(BTN_C, 10)) titleScreen();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void resetBall(bool enableV){
	ballX = random(0, hitBoxX);
	ballY = random(0, hitBoxY);
	if(enableV){
		ballVX = random(-200, 200)/100.0;
		ballVY = random(-200, 200)/100.0;
	}
	else{
		ballVX = 0;
		ballVY = 0;
	}
}

void titleScreen(){
	resetBall(0);
    gb.titleScreen(F("Gravity shenanigans"), logo);
	gb.battery.show = 0;
}


bool clampBounds(double &val, double high, double low){
	if(val >= high){
		val = high;
		return true;
	}
	if(val <= low){
		val = low;
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
