#include "Pentagon.h"
#include "Bullet.h"


Pentagon::Pentagon() {
	lastShotTime = ofGetElapsedTimef();
	fireRate = 3;
}

void Pentagon::move(glm::vec3 heroPos)
{
	//Stay Still
}

void Pentagon::update()
{

}
void Pentagon::update(glm::vec3 heroPos)
{
	//Dont move
}

bool Pentagon::shouldShoot()
{
	if (fireRate < ofGetElapsedTimef() - lastShotTime)
	{
		lastShotTime = ofGetElapsedTimef();
		return true;
	}
	return false;
}

void Pentagon::setFireRate(float fr)
{
	fireRate = fr;
}

