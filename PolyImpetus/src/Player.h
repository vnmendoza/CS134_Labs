#pragma once
#include "ofMain.h"


enum Weapon {sCannon, lCannon, homing,mines,razor,muon,particleBeam};
class Player
{
protected:
	glm::vec3 pos;
	int speed, nEnergy;
	ofColor color;
	Weapon weapon;
	float width,rotation;
	glm::vec3 scaler = glm::vec3(1.0, 1.0, 1.0);
	ofImage *sprite;
	float imgWidth, imgHeight;
	glm::vec3 vel;
	//bool alive;

public:
	//enum Weapon {sCannon, lCannon, homing,mines,razor,muon,particleBeam};
	Player();
	Player(int);
	Player(ofImage *mySprite);
//	virtual ~Player() = 0;
	int getSpeed();
	void setSpeed(int);
	void setPos(glm::vec3);
	glm::vec3 getPos();
	bool collisionCheck(glm::vec3 objPos, float objWidth);
	float getWidth();
	glm::vec3 heading();
	void drawHeading();
	glm::vec3 translate(glm::vec3 trans);
	void setShapeColor(ofColor);
	glm::mat4 getMatrix();
	ofColor getColor();

	//float getMouseX();
	//float getMouseY();
};

