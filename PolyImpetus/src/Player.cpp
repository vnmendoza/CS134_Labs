#include "Player.h"

Player::Player()
{
	width = 10;
	speed = 10;
	rotation = 0;
}

Player::Player(int s)
{
	width = s;
	speed = 10;
}

Player::Player(ofImage* mySprite)
{
	sprite = mySprite;
	imgWidth = sprite->getWidth();
	imgHeight = sprite->getHeight();
	width = 10;
	speed = 10;
	rotation = 0;

}

void Player::setShapeColor(ofColor c)
{
	color = c;
}

ofColor Player::getColor()
{
	return color;
}

glm::mat4 Player::getMatrix()
{
	glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
    glm::mat4 scale = glm::scale(glm::mat4(1.0), scaler);
    return (trans * rot * scale);
}

int Player::getSpeed()
{
	return speed;
}

void Player::setSpeed(int s)
{
	speed = s;
}

void Player::setPos(glm::vec3 p)
{
	pos = p;
}


glm::vec3 Player::getPos()
{
	return pos;
}
bool Player::collisionCheck(glm::vec3 objPos, float objWidth)
{
	//see if were touching something
	//if its an enemy 
	float obj2me = glm::distance(objPos, pos);
	float imgWidthCompensation = (objWidth + width);
	return obj2me < imgWidthCompensation;


}

float Player::getWidth()
{
	return width;
}

glm::vec3 Player::heading()
{
	glm::vec3 triPoint = translate(glm::vec3(0,-10,0));
	glm::vec3 center = translate(glm::vec3(0, 0, 0));
	return glm::normalize(triPoint - center);
}

void Player::drawHeading()
{
	glm::vec3 triPoint = translate(glm::vec3(0,-120,0));
	glm::vec3 center = translate(glm::vec3(0, 0, 0));
	ofDrawLine(triPoint, center);
}

glm::vec3 Player::translate(glm::vec3 trans)
{
	return glm::vec3(getMatrix() * glm::vec4(trans, 1.0));
}



