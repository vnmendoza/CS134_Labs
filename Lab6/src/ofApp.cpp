//  CS 134 - In-Class exercise - Getting started with Particle Physics
//
//  Kevin M. Smith - CS 134 - SJSU CS

#include "ofApp.h"






//--------------------------------------------------------------
//  Setup Application data
//
void ofApp::setup(){
	cam.setDistance(10);
	cam.setNearClip(.1);
	cam.setFov(65.5);   // approx equivalent to 28mm in 35mm format
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	cout << "test\n";
	// some simple sliders to play with parameters
	//
	gui.setup();
	gui.add(velocity.setup("Initial Velocity", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(100, 100, 100)));	
	gui.add(lifespan.setup("Lifespan", 2.0, .1, 10.0));
	gui.add(rate.setup("Rate", 1.0, .5, 60.0));
	gui.add(damping.setup("Damping", .99, .1, 1.0));
    gui.add(gravity.setup("Gravity", 10, 1, 20));

    gui.add(heightLimit.setup("Height", 0, 0, 20));

	gui.add(radius.setup("Radius", .05, .01, .3));
	gui.add(turbMin.setup("Turbulence Min", ofVec3f(0, 0, 0), ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20)));
	gui.add(turbMax.setup("Turbulence Max", ofVec3f(0, 0, 0), ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20)));
	gui.add(radialForceVal.setup("Radial Force", 1000, 100, 5000));

	bHide = false;

	// set up the emitter forces
	//
	turbForce = new TurbulenceForce(ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20));
	gravityForce = new GravityForce(ofVec3f(0, -10, 0));
	radialForce = new ImpulseRadialForce(1000.0);


	emitter.sys->addForce(turbForce);
	emitter.sys->addForce(gravityForce);
	emitter.sys->addForce(radialForce);

	orbitalEmitter.sys->addForce(turbForce);
	orbitalEmitter.sys->addForce(gravityForce);
	orbitalEmitter.sys->addForce(radialForce);

//	turbForce = new TurbulenceForce(ofVec3f(turbMin->x, turbMin->y, turbMin->z), ofVec3f(turbMax->x, turbMax->y, turbMax->z));
//	gravityForce = new GravityForce(ofVec3f(0, -gravity, 0));
//	radialForce = new ImpulseRadialForce(radialForceVal);



	emitter.setVelocity(ofVec3f(0, 0, 0));
	emitter.setOneShot(true);
	emitter.setEmitterType(RadialEmitter);
	emitter.setGroupSize(5000);

	orbitalEmitter.setVelocity(ofVec3f(0, 0, 0));
	orbitalEmitter.setOneShot(true);
	orbitalEmitter.setEmitterType(RadialEmitter);
	orbitalEmitter.setGroupSize(5000);


}

//--------------------------------------------------------------
//
void ofApp::update() {
	ofSeedRandom();

	radialForce->set(radialForceVal, heightLimit);

	emitter.setLifespan(lifespan);
	emitter.setVelocity(ofVec3f(velocity->x, velocity->y, velocity->z));
	emitter.setRate(rate);
	emitter.setParticleRadius(radius);


	emitter.update();

	orbitalEmitter.setLifespan(lifespan);
	orbitalEmitter.setVelocity(ofVec3f(velocity->x, 15, velocity->z));
	orbitalEmitter.setRate(rate);
	orbitalEmitter.setParticleRadius(radius);

	

	orbitalEmitter.update();

	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(ofColor::black);

	// draw the GUI
	if (!bHide) gui.draw();

	// begin drawing in the camera
	//
	cam.begin();

	// draw a grid
	//
	ofPushMatrix();
	ofRotateDeg(90, 0, 0, 1);
	ofSetLineWidth(1);
	ofSetColor(ofColor::dimGrey);
	ofDrawGridPlane();
	ofPopMatrix();

	// draw particle emitter here..
	//
	emitter.draw();
	orbitalEmitter.draw();

	//  end drawing in the camera
	// 
	cam.end();

	// draw screen data
	//
	string str;
	str += "Frame Rate: " + std::to_string(ofGetFrameRate());
	ofSetColor(ofColor::white);
	ofDrawBitmapString(str, ofGetWindowWidth() -170, 15);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
	case 'C':
	case 'c':
		if (cam.getMouseInputEnabled()) cam.disableMouseInput();
		else cam.enableMouseInput();
		break;
	case 'F':
	case 'b':
		break;
	case 'f':
		ofToggleFullscreen();
		break;
	case 'h':
		bHide = !bHide;
	case ' ':
		emitter.sys->reset();
		emitter.start();
		orbitalEmitter.sys->reset();
		orbitalEmitter.start();

		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
