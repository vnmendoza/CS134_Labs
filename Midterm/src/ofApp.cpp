#include "ofApp.h"





//--------------------------------------------------------------
void ofApp::setup() {


	
	//  Load tree image
	//
	if (!treeImage.load("images/tree.png")) {
		cout << "Can't load image" << endl;
		ofExit();
	}
	leafImage.load("images/leaf.png");
	ofSetBackgroundColor(ofColor::black);


	// some simple sliders to play with parameters (these are examples; actuall ranges/values required
	// may neeed to be adjusted
	//
	gui.setup();
	gui.add(gravityVal.setup("Gravity", 100, 0, 200));
	gui.add(turbulenceVal.setup("Turbulence Multiplier", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(200, 200, 200)));
	gui.add(angleRangeVal.setup("Angle Range Multiplier", 0, 0, 200));
}
	

//--------------------------------------------------------------
void ofApp::update() {
	if (bStartSim)
	{
		for (int i = 0; i < leaves.size(); i++)
		{
			if (leaves[i].pos.y < ofGetWindowHeight())
			{
				leaves[i].setAngleRange(angleRangeVal);
				leaves[i].setGravity(gravityVal);
				leaves[i].setTurbulance(ofVec3f(
					turbulenceVal->x,
					turbulenceVal->y,0));
				//trigger for all
				if(simulateAll)
					leaves[i].integrate();
				//trigger for 1 
				else
				{
					if (leaves[i].getSelect())
						leaves[i].integrate();
				}
			}
			
		}


		
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw background image;
	//
	ofSetColor(ofColor::white);
	treeImage.draw(0, 0);

	// draw the GUI
	if (!bHide) gui.draw();

	 
	// Simulation On/Off Status
	//
	string str, state,simStr,simAllState;
	state = (bStartSim ? "ON" : "OFF");
	simAllState = (simulateAll ? "ON" : "OFF");
	str += "Simulation : " + state;
	simStr = " Simulate All: " + simAllState;
	ofSetColor(ofColor::black);
	ofDrawBitmapString(str, ofGetWindowWidth() - 170, 15);
	ofDrawBitmapString(simStr, ofGetWindowWidth() - 170, 30);

	//Draw Leaves
	for (int i = 0; i < leaves.size(); i++)
	{
		leaves[i].draw();
		if (leaves[i].getSelect() && !bStartSim)
			leaves[i].drawBoundBox();
	}

}



//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'a':					// simulate all leaves at once
		simulateAll = !simulateAll;
		break;
	case 'r':					// clear (delete) all leaves
		leaves.clear();
		break;
	case 'h':					//  show/hide GUI
		bHide = !bHide;
		break;
	case 'L':
	case 'l':					// create a new leave at mouse location
		for (LeafShape& l : leaves)
			l.select(false);
		leaves.push_back(LeafShape(glm::vec3(mouseX, mouseY, 0),&leafImage));
		break;
	case OF_KEY_CONTROL:		// ctrl-left-mouse drag rotates the leaf
		bCtrlKeyDown = true;
		break;
	case OF_KEY_SHIFT:			// shift-left-mouse drag scales the leaf
		bShiftKeyDown = true;

		break;
	case ' ':					// space bar toggles simulation mode
	{
		bStartSim = !bStartSim;
		for (LeafShape& l : leaves)
			l.setTimer(ofGetElapsedTimef());
		break;
	}
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case OF_KEY_CONTROL:
		bCtrlKeyDown = false;
		break;
	case OF_KEY_SHIFT:
		bShiftKeyDown = false;
		break;
	default:
		break;
	}
}



//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	for (int i = 0; i < leaves.size(); i++)
	{
		bool selectedLeaf = leaves[i].getSelect();
		if (bShiftKeyDown && selectedLeaf)
		{
			float scaleBy = pow(mousePressedPos.y/float(y),0.5);
			leaves[i].setScale(scaleBy);
		}
		if (bCtrlKeyDown && selectedLeaf)
		{
			float displacement = mousePressedPos.x - float(x);
			leaves[i].setRotate(displacement);
		}
		if (!bCtrlKeyDown && !bShiftKeyDown && selectedLeaf)
		{
			leaves[i].move(glm::vec3(x, y,0) + displacement);
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mousePressedPos = glm::vec3(x, y, 0);

	for (int i = 0; i < leaves.size(); i++)
	{
		bool clicked = leaves[i].inside(mousePressedPos);
		leaves[i].select(clicked);
		if(clicked)
			displacement = leaves[i].pos - glm::vec3(x, y, 0);
	}
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
