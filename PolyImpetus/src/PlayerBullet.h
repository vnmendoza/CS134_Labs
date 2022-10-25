#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include "Bullet.h"

class PlayerBullet : public Bullet
{
protected:
	float accuracy;
public:
	PlayerBullet();
	PlayerBullet(glm::vec2 position, int speed, float accuracy, float rotation ,ofImage* bulletImage);
	void setup(bool f_p, glm::vec2 position, float speed,float acc, float rotate,ofImage* bullet_image);
	void setDirection(glm::vec2 mousePos);
	void move();
	void update(glm::vec2);
	void update();
};

