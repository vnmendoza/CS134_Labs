#pragma once
#include "Enemy.h"
class Pentagon : public Enemy
{
private:
	float lastShotTime, fireRate;

public:
	Pentagon();
	void move(glm::vec3 heroPos);
	void move(glm::vec2);
	void update();
	void update(glm::vec3 heroPos);
	void shoot(glm::vec3 heroPos);
	void update(glm::vec2);
	bool shouldShoot();

	void setFireRate(float fr);

};

