#pragma once
#include "Enemy.h"
class Triangle : public Enemy
{
private:
public:
	Triangle();
	void move(glm::vec3);
	void update(glm::vec3 heroPosition);
};

