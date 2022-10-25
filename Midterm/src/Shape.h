#pragma once
#include "ofMain.h"

class Shape {
public:
	Shape() {}
	virtual void draw() {}
	virtual bool inside(glm::vec3 p) {
		return true;
	}
	glm::mat4 getMatrix() {
		glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
		glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), scaler );
		return (trans * rot *scale );
	}
	glm::mat4 getRotScaMatrix() {
		glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), scaler );
		return (rot *scale );
	}
	glm::vec3 pos = glm::vec3(0, 0, 0);
	float rotation = 0.0;    // degrees 
	glm::vec3 scaler = glm::vec3(1.0);

	glm::vec3 transl8(glm::vec3 trans);
};

class LeafShape : public Shape {
private:
	// General Parameters go here...
	//
	float imgWidth, imgHeight;
	glm::vec3 scaler;
	ofImage *leafImg;
	bool selected,rotationDir;
	float timer,damping,mass, rotationTime, 
		angleRange,turbTime;
	float turbRtime = 3.0;
	glm::vec3 velocity,turbulance,gravity, angle,origTurb;
public:
	// Constructor(s) go here; this is a default one; you may want to add some additional constructor(s) to make
	// it convenient to create new leaves as specific location on the screen.
	//
	LeafShape(glm::vec3 pos, ofImage *image);
	// Some function(s) you might need to develop.  Note: if functions are more than 4-5 lines long,
	// then suggest moving their implementation to the .cpp file.
	//
	void draw();
	bool inside(glm::vec3 p);
	void select(bool clicked);
	void setScale(float scale);
	bool getSelect();
	void setRotate(float rot);
	void move(glm::vec3 postion);
	float getImgWidth();
	void drawBoundBox();

	// Physics data goes here...
	//
	bool checkCollision();
	void integrate();
	void setGravity(float gravity);
	void setTurbulance(ofVec3f turb);
	void setTurbulance(glm::vec3 turb);
	void setTimer(float time);
	void setAngleRange(float angleRange);
	void rotationSim();
	void turbSim();

	
};


