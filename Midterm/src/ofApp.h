#pragma once

#include "ofMain.h"
#include "ofxGUI.h"
#include "Shape.h"


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
	

		// state variables
		//
		bool bCtrlKeyDown = false;
		bool bShiftKeyDown = false;
		bool bStartSim = false;
		bool simulateAll = false;

		vector<LeafShape> leaves;
		glm::vec3 mousePressedPos, displacement;

		// GUI
		//

		bool bHide = true;
		ofxFloatSlider gravityVal;
		ofxVec3Slider turbulenceVal;
		ofxFloatSlider angleRangeVal;
		ofxPanel gui;

		// images
		//
		ofImage treeImage, leafImage;

};
