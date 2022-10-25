#pragma once

#include "ofMain.h"
#include "ofxGui.h"



class Shape {
public:
	ofColor triColor;
	glm::vec3 scaler = glm::vec3(1.0,1.0,1.0);
	Shape() {}
	virtual void draw() {}
	virtual bool inside(glm::vec3 p) {
		return true;
	}
	glm::mat4 getMatrix() {
		glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
		glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), scaler);
		return (trans * rot * scale);
	}
	glm::vec3 pos;
	float rotation = 0.0;    // degrees 

	vector<glm::vec3> verts;
};

class TriangleShape : public Shape {
public:
	TriangleShape() {}
	TriangleShape(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
		verts.push_back(p1);
		verts.push_back(p2);
		verts.push_back(p3);  
	}
	void draw();
	bool inside(glm::vec3 p) {
		//cout << glm::inverseTranspose(p) << endl;

		glm::vec3 transformed = glm::vec3(glm::inverse(getMatrix()) * glm::vec4(p, 1.0));
		//cout << "current mouse position after the trigangle was transformed: "<<p << endl;
		//cout << "mouse position after inverse transform: "<<transformed << endl;
		//cout << glm::inverse(glm::mat4() << endl;

		return inside(transformed, verts[0], verts[1], verts[2]);
	}

	bool inside(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
		glm::vec3 v1 = glm::normalize(p1 - p);
		glm::vec3 v2 = glm::normalize(p2 - p);
		glm::vec3 v3 = glm::normalize(p3 - p);
		float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
		float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
		float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
		if (a1 < 0 && a2 < 0 && a3 < 0) return true;
		else return false;
	}
	//------
	void scale(float x, float y)
	{
		scaler.x = x;
		scaler.y = y;
	}
	//for dragging use vectors
	//apply the vector arithmetically to the position
};

// ~~~~~~~~~~~PLAYER~~~~~~~~~~~~~
class Player : public TriangleShape {
protected:
	float speed,width,height,rotSpeed;
	bool fwd, back, left, right = false;
	glm::vec3 vel;
	ofImage* shipPic;
	glm::vec3 origin = glm::vec3(0, 0, 0);
	
public:
	Player() {
		speed = 5;
		fwd = back = left = right = false;
	}

	Player(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) : TriangleShape(p1, p2, p3) {
		speed = 5;
		fwd = back = left = right = false;
	}

	glm::vec3 heading()
	{
		glm::vec3 triPoint = translate(verts[2]);
		glm::vec3 center = translate(glm::vec3(0, 0, 0));
		return glm::normalize(triPoint - center);
	}
	glm::vec3 translate(glm::vec3 trans)
	{
		return glm::vec3(getMatrix() * glm::vec4(trans, 1.0));
	}

	void setScale(float scale)
	{
		scaler = glm::vec3(scale, scale, scale);
	}
	void drawHeading()
	{
		glm::vec3 end = origin - glm::vec3(0, 75, 0);
//		glm::vec3 start = getMatrix() * glm::vec4(verts[2], 1.0);
		glm::vec3 start = translate(origin);
		end = getMatrix() * glm::vec4(end, 1.0);
		ofDrawLine(start,end);

	}
	void setFwdPressed(bool k)
	{
		fwd = k;
	}
	void setBackPressed(bool k)
	{
		back = k;
	}
	void setLeftPressed(bool k)
	{
		left = k;
	}
	void setRightPressed(bool k)
	{
		right = k;
	}
	void setImg(ofImage* image)
	{
		shipPic = image;
		//width = shipPic->width;
		width = shipPic->getWidth();
		height = shipPic->getHeight();
	}
	void drawShip()
	{

		float picWidth = width * scaler.x*2;
		float picHeight = height * scaler.x*2;
		//cout << width << endl;
		//cout << height << endl;
		//pos.x = pos.x - picWidth/2;
		//pos.y = pos.y - picHeight / 2;

		ofPushMatrix();
		ofTranslate(translate(glm::vec3(0,0,0)));
		ofRotateZ(rotation);
		ofSetColor(ofColor::white);
		shipPic->draw(-picWidth/2.0,-picHeight/2.0,picWidth,picHeight);
		ofPopMatrix();
		//shipPic->draw(pos,width,height);
	}

	void setSpeed(float spd)
	{
		speed = spd;
	}
	void move(map<int,bool> km)
	{
		if (km['w'] || km[OF_KEY_UP])
		{
			
			vel = speed * heading();
			pos += vel;
		}
		if (km['s'] || km[OF_KEY_DOWN])
		{
			vel = speed * heading();
			pos -= vel;
		}
		if (km['a'] || km[OF_KEY_LEFT])
			rotation -= rotSpeed;
		if (km['d'] || km[OF_KEY_RIGHT])
			rotation+= rotSpeed;

	}
	void setRotationSpeed(float spd)
	{
		rotSpeed = spd;
	}
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	TriangleShape tri;
	ofImage shipImg;
	ofxPanel gui;
	ofxFloatSlider speedSlider,shipScaleSlider,rotationSpeedSlider;
	ofxButton spriteButton,triButton;
	ofxToggle headingToggle;


		
};
