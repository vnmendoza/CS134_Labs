#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Particle.h"
#include "ParticleEmitter.h"



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

		ofEasyCam    cam;

		ofVec3f zeroVec = ofVec3f(0, 0, 0);
		// some simple sliders to play with parameters
		//
		bool bHide;
		ofxFloatSlider gravity;
		ofxFloatSlider damping;
		ofxFloatSlider radius;
		ofxVec3Slider velocity;
		ofxVec3Slider turbMin,turbMax;
		ofxFloatSlider lifespan;
		ofxFloatSlider rate;
		ofxPanel gui;
		ParticleSystem ps;
		ParticleEmitter pe = ParticleEmitter(&ps);
		TurbulenceForce tb = TurbulenceForce(zeroVec,zeroVec);
};
