#include "Player.h"
#include "Hero.h"

Hero::Hero() : Player()
{
	width = 5;
	speed = 5;
	nEnergy = 5;
	is_up_pressed = false;
	is_left_pressed = false;
	is_down_pressed = false;
	is_right_pressed = false;

}

Hero::Hero(int s) : Player(s)
{
	speed = 10;
	is_up_pressed = false;
	is_left_pressed = false;
	is_down_pressed = false;
	is_right_pressed = false;

}

void Hero::setup(ofImage *mySprite)
{
	sprite = mySprite;
	imgWidth = sprite->getWidth() * 0.5;
	imgHeight = sprite->getHeight() * 0.5;
	sprite->setAnchorPoint(imgWidth / 2, imgHeight / 2);
	rotSpeed = 10;
	speed = 10;
	nEnergy = 5;
	is_up_pressed = false;
	is_left_pressed = false;
	is_down_pressed = false;
	is_right_pressed = false;
	width = imgWidth/3;
}

void Hero::setRotationSpeed(float rots)
{
	rotSpeed = rots;
}

void Hero::update()
{

	move();
	//wall collisions
	if (pos.x > ofGetWidth() - width) {
		pos.x = ofGetWidth()-width;
	}

	if (pos.x < width) {
		pos.x = width;
	}

	if (pos.y > ofGetHeight()-width) {
		pos.y = ofGetHeight()-width;
	}

	if (pos.y < width) {
		pos.y = width;
	}
}

void Hero::draw()
{
	ofPushMatrix();
	ofSetColor(color);
	ofMultMatrix(getMatrix());
	sprite->setAnchorPoint(imgWidth/2, imgHeight/2);
	sprite->draw(0,0,imgWidth,imgHeight);
	ofPopMatrix();
}

void Hero::drawTriangle()
{
	ofPushMatrix();
	ofSetColor(color);
	ofMultMatrix(getMatrix());
	ofSetCircleResolution(128);
	ofDrawCircle(0,0, width);
	ofPopMatrix();
	drawHeading();
}

void Hero::setSize(float size)
{
	scaler = glm::vec3(size, size, size);
	imgWidth = sprite->getWidth() * size;
	imgHeight = sprite->getHeight() * size;
}

void Hero::setLeftPressed(bool b)
{
	is_left_pressed = b;
}

void Hero::setUpPressed(bool b)
{
	is_up_pressed = b;
}

void Hero::setDownPressed(bool b)
{
	is_down_pressed = b;
}

void Hero::setRightPressed(bool b)
{
	is_right_pressed = b;
}

void Hero::loseNRG()
{
	nEnergy--;
}

int Hero::getNRG()
{
	return nEnergy;
}

void Hero::setNRG(int energy)
{
	nEnergy = energy;
}

void Hero::move()
{
	if (is_up_pressed)
	{
		vel = speed * heading();
		pos += vel;
	}
	if (is_left_pressed)
	{
		rotation -= rotSpeed;
	}
	if (is_down_pressed)
	{
		vel = speed * heading();
		pos -= vel;
	}
	if (is_right_pressed)
	{
		rotation += rotSpeed;
	}
}





