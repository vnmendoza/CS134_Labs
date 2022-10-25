#include "Shape.h"

//translates normal vectors to the ones offset by the tranformation matrix that happened
// to each leaf
glm::vec3 Shape::transl8(glm::vec3 trans)
{
	return glm::vec3(getMatrix() * glm::vec4(trans, 1.0));
}











/// <summary>
/// Leaf Shape
/// </summary>
/// <param name="position"></param>
/// <param name="img"></param>
LeafShape::LeafShape(glm::vec3 position, ofImage *img) {
	leafImg = img;
	imgWidth = leafImg->getWidth();
	imgHeight = leafImg->getHeight();
	pos = position;
	scaler = glm::vec3(1.0);
	selected = true;
	velocity = glm::vec3(0.0);
	damping = .99;
	mass = 1.0;
	rotationTime = ofRandom(0.5,8.0) + ofGetElapsedTimef();
	turbTime = ofRandom(turbRtime) + ofGetElapsedTimef();
	rotationDir = floor(ofRandom(2));
}

void LeafShape::draw()
{
	//Orientation Lines
	/*
	ofSetColor(ofColor::red);
	ofDrawLine(pos, glm::vec3(pos.x +100,pos.y,0));
	ofSetColor(ofColor::blue);
	ofDrawLine(pos, glm::vec3(pos.x,pos.y +200,0));
	*/
	ofPushMatrix();
	ofTranslate(pos);
	ofRotateZ(rotation);
	ofSetColor(ofColor::white);
	leafImg->setAnchorPoint(imgWidth / 2, imgHeight / 2);
	leafImg->draw(0, 0, imgWidth, imgHeight);
	ofPopMatrix();
}

void LeafShape::drawBoundBox()
{
	ofPushMatrix();
	ofTranslate(pos);
	ofRotateZ(rotation);
	ofNoFill();
	ofSetColor(ofColor::grey);
	ofDrawRectangle(-imgWidth/2,-imgHeight/2, imgWidth, imgHeight);
	ofPopMatrix();
}

bool LeafShape::inside(glm::vec3 p)
{

	glm::vec3 pinv = glm::vec3(glm::inverse(getMatrix()) * glm::vec4(p, 1.0));
	glm::vec3 origPos = glm::vec3(glm::inverse(getMatrix()) * glm::vec4(pos, 1.0));

	float left = origPos.x - imgWidth / 2.0;
	float right = origPos.x + imgWidth / 2.0;
	float top = origPos.y - imgHeight / 2.0;
	float bottom = origPos.y + imgHeight / 2.0;

	if (pinv.x > left && pinv.x < right && pinv.y > top && pinv.y < bottom) 
		return true;
	return false;
}

void LeafShape::select(bool slct)
{
	selected = slct;
}

bool LeafShape::getSelect()
{
	return selected;
}

void LeafShape::setScale(float scale)
{
	scaler = glm::vec3(scale);
	imgWidth = leafImg->getWidth() * scaler.x;
	imgHeight = leafImg ->getHeight() * scaler.x;
}

void LeafShape::setRotate(float rot)
{
	angle.z= rot;
	rotation = rot;
}

void LeafShape::move(glm::vec3 p)
{
	pos = p;
}

void LeafShape::integrate()
{
	glm::vec3 totalForces = glm::vec3(0);
	float t = ofGetElapsedTimef();
	float timeElapsed = t - timer;
	//rotational motion
	rotationSim();
	//gravity force
	//f=ma
	totalForces += mass * gravity;

	//turbulance Force
	turbSim();
	totalForces += turbulance;
	totalForces *= damping;

	move(pos + totalForces * timeElapsed);

	timer = t;


}

void LeafShape::setGravity(float grav)
{
	gravity = glm::vec3(0, grav, 0);
}

void LeafShape::setTurbulance(ofVec3f turb)
{
	glm::vec3 turby = glm::vec3(turb);
	if (origTurb != turby)
	{
		origTurb = turby;
		turbulance.x = ofRandom(-turb.x, turb.x);
		turbulance.y = ofRandom(-turb.y, turb.y);
	}
}

void LeafShape::setTurbulance(glm::vec3 turb)
{
	turbulance.x = ofRandom(-turb.x, turb.x);
	turbulance.y = ofRandom(-turb.y, turb.y);

}
void LeafShape::turbSim()
{
	if (ofGetElapsedTimef() > turbTime)
	{
		setTurbulance(origTurb);
		turbTime = ofRandom(turbRtime) + ofGetElapsedTimef();
	}
}
void LeafShape::setTimer(float t)
{
	timer = t;
}

void LeafShape::setAngleRange(float ar)
{
	//angle vector consits of glm::vec3(minAngle,maxAngle,currentAngle)
	if (ar != angleRange)
	{
		//find min/max
		angle.x = angle.z - ar;
		angle.y = angle.z + ar;

	}
	angleRange = ar;
}

void LeafShape::rotationSim()
{
	if (ofGetElapsedTimef() < rotationTime)
	{
		if (rotationDir)
		{
			rotation--;
			angle.z = rotation;
			rotationDir = (angle.z > angle.x) ? rotationDir : !rotationDir;
		}

		else
		{
			rotation++;
			angle.z = rotation;
			rotationDir = (angle.z < angle.y) ? rotationDir : !rotationDir;
		}
	}
	else
	{
		rotationDir = !rotationDir;
		rotationTime = ofRandom(4.0) + ofGetElapsedTimef();
	}
}
float LeafShape::getImgWidth()
{
	return imgWidth;
}
