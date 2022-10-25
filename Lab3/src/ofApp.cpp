#include "ofApp.h"

float y,x = 1.0;
bool drag = false;
glm::mat4 myMat;
int mouseX, mouseY;
glm::vec3 displacement;
bool ctrlPressed=false;
Player hero;
bool triPressed = true;

map<int, bool> keymap;



void TriangleShape::draw() {


	ofSetColor(triColor);
	ofFill();
	ofPushMatrix();
	ofMultMatrix( getMatrix() );
	ofDrawTriangle(verts[0], verts[1], verts[2]);
	ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::setup(){

	//Import Image
	shipImg.loadImage("ship.png");

	//Create Player
	hero = Player(glm::vec3(-50, 50, 0), glm::vec3(50, 50, 0), glm::vec3(0, -50, 0));
	hero.setScale(2.0);
	hero.pos = glm::vec3(ofGetWindowWidth()/2.0-100, ofGetWindowHeight()/2.0-100, 0);
	hero.triColor - ofColor::red;
	hero.setImg(&shipImg);
	//Slider Setup
	gui.setup();
	gui.add(shipScaleSlider.setup("Scale",1,0.0001,7));
	gui.add(speedSlider.setup("Ship Speed",10,0.0001,50));
	gui.add(rotationSpeedSlider.setup("Rotation Speed",1,0.0001,20));
	gui.add(triButton.setup("Triangle"));
	gui.add(spriteButton.setup("Sprite"));
	gui.add(headingToggle.setup("Heading",true));

}

//--------------------------------------------------------------
void ofApp::update(){
	if (ctrlPressed && drag)
		hero.rotation++;
	hero.setScale(shipScaleSlider);
	hero.setSpeed(speedSlider);
	hero.setRotationSpeed(rotationSpeedSlider);
	if (triButton)
		triPressed = true;
	if (spriteButton)
		triPressed = false;
	hero.move(keymap);
}

//--------------------------------------------------------------
void ofApp::draw(){
	if(headingToggle)
		hero.drawHeading();
	if (triPressed)
		hero.draw();
	else
		hero.drawShip();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	keymap[key] = true;
	ctrlPressed = keymap[OF_KEY_CONTROL];
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	keymap[key] = false;
	ctrlPressed = keymap[OF_KEY_CONTROL];
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	//cout << x << " " << y << endl;
	if (hero.inside(glm::vec3(x, y, 0)) && !drag)
	{
		hero.triColor = ofColor::orange;
	}
	else if (!hero.inside(glm::vec3(x, y, 0)))
	{
		hero.triColor = ofColor::red;
	}
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//cout << "dragging" << endl;
	if (drag)
	{
		hero.pos = glm::vec3(x, y, 1) + displacement;
		hero.triColor = ofColor::blue;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	cout << "Click" << endl;
	if (hero.inside(glm::vec3(x, y, 0)))
	{
		cout << "inside" << endl;
		drag = true;
		displacement = hero.pos - glm::vec3(x, y, 1);
	}
	cout << "matrix:\n"<<hero.getMatrix();
	glm::vec3 v1 = glm::vec3(1, 0, 0);
	glm::vec3 v2 = glm::vec3(-10, 10, 0);
	glm::vec3 v3 = glm::vec3(0, 0, 1);
	auto oa = glm::orientedAngle(glm::normalize(v1), glm::normalize(v2), v3);
	cout << "orient d: " << glm::degrees(oa) << endl;
	cout << "orient rad: " << oa << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	//drop triangle
	cout << "release" << endl;
	drag = false;
	hero.triColor = ofColor::orange;
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

