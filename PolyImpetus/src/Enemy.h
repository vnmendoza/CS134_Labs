#pragma once
#include "ofMain.h"
#include "Player.h"

class Enemy : public Player
{
protected:
	int sides;
	glm::vec3 direction;
	float lifespan;
	float birthday;
	//bool alive;
public:
	Enemy();
	void setLifespan(float lspn);
	void setup(int shapeSize,int numSides,Weapon weapon,int speed, ofImage* enemyImage);
	void setup(int shapeSize, int numSides);
	//void move();
	void draw();
	float getBirthday();
	float getLifespan();


};
