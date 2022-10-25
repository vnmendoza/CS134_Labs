#pragma once
#include "ofMain.h"
#include "Player.h"


class Hero : public Player
{
private:

	bool is_left_pressed, is_right_pressed, is_down_pressed, is_up_pressed;
	int weaponSlots[5];
	float rotSpeed;

public:
	Hero();
	Hero(int);
	void update();
	void draw();
	void drawTriangle();
	void setSize(float size);
	void setup(ofImage *mySprite);
	void setRotationSpeed(float rotationSpeed);
	void setUpPressed(bool);
	void setLeftPressed(bool);
	void setDownPressed(bool);
	void setRightPressed(bool);
	void loseNRG();
	int getNRG();
	void setNRG(int energy);
	void move();

	//float getMouseX();
	//float getMouseY();
};

