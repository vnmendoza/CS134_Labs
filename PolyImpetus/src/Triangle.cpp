#include "Triangle.h"


Triangle::Triangle() {}

void Triangle::move(glm::vec3 heroPos)
{

	direction = pos - heroPos;
	//normalize
	direction = glm::normalize(direction);
	//multiply by speed
	direction *= -speed;
	//add to position
	pos += direction;

}

void Triangle::update(glm::vec3 mousePos)
{
	move(mousePos);
	//rotation
	//cout << glm::degrees(glm::orientedAngle(heading(), direction, glm::vec3(0, 0, 1)))<<endl;
	ofSetColor(ofColor::gray);
	drawHeading();
	float deg =  glm::degrees(glm::orientedAngle(glm::vec3(0,1,0), glm::normalize(direction), glm::vec3(0, 0, 1)));
	//the 30 is for a weird offset.
	rotation = deg - 30;
}


