#pragma once
#include "ofMain.h"
#include "Player.h"

class Bullet
{
protected:
	glm::vec3 pos,vel;
	float speed, rotation;
	float imgWidth,imgHeight;
	//bool from_player;
	float damage;
	ofImage* img;
	glm::vec3 scaler = glm::vec3(1.0, 1.0, 1.0);
public:
	Bullet();
	Bullet(glm::vec3, ofImage*);
	void setup(glm::vec3 p,  ofImage* bullet_image);
	virtual	void update();
	void draw();
	glm::vec3 getPos();
	float getWidth();
	float getDamage();
	void setDamage(float);
	glm::mat4 getMatrix();
	void setDirection(glm::vec3 mousePos);
};

class PlayerBullet : public Bullet
{
protected:
	float accuracy;
public:
	PlayerBullet();
	PlayerBullet(glm::vec3 position, int speed, float accuracy, float rotation ,ofImage* bulletImage);
	PlayerBullet(glm::vec3 position, int speed, float accuracy, ofImage* bulletImage);
	void setup(bool f_p, glm::vec3 position, float speed,float acc, float rotate,ofImage* bullet_image);
	void move();
	void update(glm::vec3);
	void update();
};

class EnemyBullet : public Bullet
{
protected: 
public:
	EnemyBullet();
	void setup(glm::vec3 position, Weapon weapon, float rotate, ofImage* bullet);
	void setup(glm::vec3 position, int speed, float rotate, ofImage* bulletImg);

	void update();


};

