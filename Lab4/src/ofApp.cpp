//  CS 134 - In-Class exercise - Getting started with Particle Physics
//
//  Kevin M. Smith - CS 134 - SJSU CS

#include "ofApp.h"

vector<Particle> particles;

Particle::Particle() {

	// initialize particle with some reasonable values first;
	//
	velocity.set(5, 5, 0);
	acceleration.set(0, 0, 0);
	position.set(0, 0, 0);
	lifespan = 5;
	birthtime = ofGetElapsedTimef();
	radius = 5;
	damping = .99;
	mass = 1;
	timer = birthtime;
	
}

void Particle::draw() {

	ofSetColor(ofColor::blue);
	ofDrawSphere(position, radius);
}

// write your own integrator here.. (hint: it's only 3 lines of code)
//
void Particle::integrate() {


	float t = ofGetElapsedTimef();
	// (1) update position from velocity and time interval
	float timeElapsed = t - timer;
	position = position + velocity * timeElapsed;
	// (2) update velocity (based on acceleration)
	velocity = velocity + acceleration * timeElapsed;
	// (3) multiply final result by the damping factor to sim drag
	velocity = velocity * damping;
	timer = t;
} 

void ofApp::launchParticle() {

	// Create initialize a new particle with values from sliders
	//
	Particle particle;


	particle.velocity.x = velocity->x;
	particle.velocity.y = velocity->y;
	particle.velocity.z = velocity->z;

	particle.acceleration.set(0, -gravity, 0);
	particle.damping = damping;
	particle.radius = radius;
	particle.birthtime = ofGetElapsedTimef();

	cout << "vel: " << particle.velocity << endl;
	cout << "accel: " << particle.acceleration << endl;
	cout << "damp: " << damping << endl;
	cout << "rad: " << radius << endl;
	cout << "get Elapsed time" << particle.birthtime;

	// save your particle here  - you can use an array
	// but make sure to clear() it first as we are using it for 
	// just one particle.
	particles.clear();
	particles.push_back(particle);

}

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setDistance(10);
	cam.setNearClip(.1);
	cam.setFov(65.5);   // approx equivalent to 28mm in 35mm format
	ofSetVerticalSync(true);
	framerate = ofGetFrameRate();

	// some simple sliders to play with parameters
	//
	gui.setup();
	gui.add(velocity.setup("Initial Velocity", ofVec3f(0, 20, 0), ofVec3f(0, 0, 0), ofVec3f(100, 100, 100)));	
	gui.add(damping.setup("Damping", .99, .1, 1.0));
    gui.add(gravity.setup("Gravity", 10, 1, 20));
	gui.add(radius.setup("Radius", .5, .1, 1.0));
	bHide = false;

}

//--------------------------------------------------------------
void ofApp::update() {
	//
	// need to call integrate() method in your particles here
	//  - loop through your 
	//
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].integrate();
		//erase if past lifespan
		if( ofGetElapsedTimef() - particles[i].birthtime > particles[i].lifespan)
			particles.erase(particles.begin() + i);
	}
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(ofColor::black);

	// draw the GUI
	if (!bHide) gui.draw();


	cam.begin();

	// draw a grid
	//
	ofPushMatrix();
	ofRotate(90, 0, 0, 1);
	ofSetLineWidth(1);
	ofSetColor(ofColor::dimGrey);
	ofDrawGridPlane();
	ofPopMatrix();

	// draw particle(s) here..
	//
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].draw();
	}

	cam.end();

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
	case 'f':
		ofToggleFullscreen();
		break;
	case ' ':
		launchParticle();
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
