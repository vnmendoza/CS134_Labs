#pragma once
#include "Player.h"
#include "Enemy.h"

Enemy::Enemy() 
{
	weapon = homing;
	sides = 3;
	width = 70;
	lifespan = 5;
	birthday = ofGetElapsedTimef();
}


void Enemy::draw()
{
	ofPushMatrix();
	ofSetColor(color);
	ofSetCircleResolution(sides);
	ofMultMatrix(getMatrix());
	ofDrawCircle(0,0, width);
	ofPopMatrix();
}

float Enemy::getBirthday()
{
	return birthday;
}

float Enemy::getLifespan()
{
	return lifespan;
}

void Enemy::setLifespan(float lspn)
{
	lifespan = lspn;
}
void Enemy::setup(int shapewidth, int numSides, Weapon weapon, int speed, ofImage* enemyImage)
{
	width = shapewidth;
	this->speed = speed;
	sides = numSides;
	this->weapon = weapon;
	pos = glm::vec3(ofRandom(width, ofGetWindowWidth() - width), ofRandom(width, ofGetWindowHeight() - width),0);
	rotation = ofRandom(0, 360);
	sprite = enemyImage;
	//width = img->getWidth();
}

void Enemy::setup(int shapeSize, int numSides)
{
	width = shapeSize;
	sides = numSides;
	rotation = ofRandom(0, 360);
	pos = glm::vec3(ofRandom(width, ofGetWindowWidth() - width), ofRandom(width, ofGetWindowHeight() - width),0);
}


/*
bool inside(glm::vec3, float width)
{
	
}
*/


