#include "ofApp.h"



//Enemy square;


//--------------------------------------------------------------

void ofApp::setup() {
	gs = Title;

	//Test
	tester = glm::vec3(100, 200,0);
	ofSetFrameRate(30);

	//GUI
	//Hero Sliders
	heroGroup.setName("Hero");
	heroGroup.add(heroSpeedSlider.set("Hero Speed", 9, 0, 50));
	heroGroup.add(heroRotationSpeedSlider.set("Hero Rotation Speed", 5, 0, 10));
	heroGroup.add(heroSizeSlider.set("Hero Size", 0.75, 0, 3));
	gui.setup(heroGroup);
	//EnemySliders
	enemyGroup.setName("Enemies");
	enemyGroup.add(enemySpeedSlider.set("Enemy Speed", 5, 0, 50));
	enemyGroup.add(eSpawnRate.set("Enemy Spawn Rate", 3, 0.5, 15));
	enemyGroup.add(eSpawnAmnt.set("Enemy Spawn Amount", 1, 1, 10));
	enemyGroup.add(eLifespan.set("Enemy Lifespan", 4, 0, 10));
	enemyGroup.add(eFireRate.set("Enemy FireRate", 3, 0.5, 10));
	//General Sliders
	mainGroup.add(levelSlider.set("Level", 1, 1, 3));
	gui.add(spriteToggle.setup("Show Sprite", true));
	//Add to gui
	mainGroup.add(heroGroup);
	mainGroup.add(enemyGroup);
	gui.setup(mainGroup);

	ofSetWindowTitle("PolyImpetus");
	ofSetFrameRate(60);
	ofSetBackgroundColor(0);
	heroImg.load("Hero_ship.png");
	bulletImage.load("bullet.png");
	bulletImage.resize(50, 50);
	enemyBullet.load("EnemyProjectile.png");

	//image.load("SpiralCircle.jpg");
	bgImg.load("background.png");
	rotation = 0;
	shapeDegRot = 45;
	shapeSize = 40;
	center = glm::vec3(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2,0);

	//Create Hero
	hero.setup(&heroImg);
	hero.setPos(center);
	hero.setShapeColor(ofColor::paleVioletRed);

	//Instuctions
	myFont.load("Hexgon-2xwv.otf", 28, true, true);
	fonty.load("Caveat-Regular.ttf", 32, true, true);
	my32Font.load("Hexgon-2xwv.otf", 32, true, true);
	instructions = "     WASD to move\nleft click to shoot";
	enter = "push SPACE to begin";
	instWidth = my32Font.stringWidth(instructions) / 2;
	instHeight = my32Font.stringHeight(instructions) / 2;
	enterWidth = myFont.stringWidth(enter) / 2;
	circum = instWidth + shapeDegRot;
	gameOver = "Game Over";
	gameOverWidth = myFont.stringWidth(gameOver);
	}

//--------------------------------------------------------------
void ofApp::update() {
	hero.setSpeed(heroSpeedSlider);
	hero.setRotationSpeed(heroRotationSpeedSlider);
	hero.setSize(heroSizeSlider);
	lc.setup(eSpawnRate,eSpawnAmnt);
	lc.setLevel(levelSlider);
	

	/*
	for (int i = 0; i< enemies.size(); i++)
	{
		enemies[i].setSpeed(enemySpeedSlider);
		if (ofGetElapsedTimef() - enemies[i].getBirthday() > enemies[i].getLifespan())
		{
			enemies.erase(enemies.begin() + i);
		}
	}
*/
	for (int i = pentagons.size()-1; i>=0; i--)
	{
		pentagons[i].setSpeed(enemySpeedSlider);
		pentagons[i].setFireRate(eFireRate);
		pentagons[i].setLifespan(eLifespan);
		if (ofGetElapsedTimef() - pentagons[i].getBirthday() > pentagons[i].getLifespan())
			pentagons.erase(pentagons.begin() + i);
		if (pentagons[i].shouldShoot())
		{
			EnemyBullet eb;
			eb.setup(pentagons[i].getPos(), 2, 0, &enemyBullet);
			eb.setDirection(hero.getPos());
			enemyBullets.push_back(eb);
		}
	}
	for (int i = 0; i < triangles.size(); i++)
	{

		triangles[i].setLifespan(eLifespan);
		triangles[i].setSpeed(enemySpeedSlider);
		if (ofGetElapsedTimef() - triangles[i].getBirthday() > triangles[i].getLifespan())
			triangles.erase(triangles.begin() + i);
	}
	switch (gs)
	{
	case Title:
		rotation += 1;
		break;
	case Play:
		hero.update();
		for (int i = 0; i < pentagons.size(); i++)
			pentagons[i].update();
		for (int i = 0; i < triangles.size(); i++)
			triangles[i].update(hero.getPos());
		update_bullets();
		checkPlayerCollisions();
		spawnEnemies();
		break;
	case End:
		break;
	default:
		break;
	}

}

void ofApp::drawElapsedTime()
{

	ofPushMatrix();
	ofSetColor(ofColor::white);
	string time = "Time Alive: " + ofToString(ofGetElapsedTimef() - startTime);
	ofDrawBitmapString(time, ofGetWindowWidth()/2, 50);
	ofPopMatrix();
}

void ofApp::drawStart()
{
		//Start Screen
		ofSetColor(255);
		my32Font.drawString(instructions, center.x - instWidth, center.y - instHeight);
		myFont.drawString(enter, center.x - enterWidth, center.y +  instHeight);
		//Draw Enemies Circling
		ofTranslate(center);
		ofRotateDeg(rotation);
		ofFill();
		//Triangle
		ofPushMatrix();
		ofTranslate(circum, 0, 0);
		ofSetCircleResolution(3);
		ofSetColor(ofColor::paleVioletRed);
		ofDrawCircle(0,0, shapeSize);
		ofPopMatrix();
		//Rectangle
		ofPushMatrix();
		ofRotateDeg(shapeDegRot);
		ofTranslate(circum, 0, 0);
		ofSetColor(ofColor::aqua);
		ofSetCircleResolution(4);
		ofDrawCircle(0, 0, shapeSize);
		ofPopMatrix();
		//Pentagon
		ofPushMatrix();
		ofRotateDeg(shapeDegRot*2);
		ofTranslate(circum, 0, 0);
		ofSetColor(ofColor::moccasin);
		ofSetCircleResolution(5);
		ofDrawCircle(0, 0, shapeSize);
		ofPopMatrix();
		//Hexagon
		ofPushMatrix();
		ofRotateDeg(shapeDegRot * 3);
		ofTranslate(circum, 0, 0);
		ofSetColor(ofColor::green);
		ofSetCircleResolution(6);
		ofDrawCircle(0, 0, shapeSize);
		ofPopMatrix();
		//Heptagon
		ofPushMatrix();
		ofRotateDeg(shapeDegRot * 4);
		ofTranslate(circum, 0, 0);
		ofSetColor(ofColor::magenta);
		ofSetCircleResolution(7);
		ofDrawCircle(0, 0, shapeSize);
		ofPopMatrix();
		//Octogon
		ofPushMatrix();
		ofRotateDeg(shapeDegRot * 5);
		ofTranslate(circum, 0, 0);
		ofSetColor(ofColor::yellow);
		ofSetCircleResolution(8);
		ofDrawCircle(0, 0, shapeSize);
		ofPopMatrix();
		//Nonogon
		ofPushMatrix();
		ofRotateDeg(shapeDegRot * 6);
		ofTranslate(circum, 0, 0);
		ofSetColor(ofColor::blue);
		ofSetCircleResolution(9);
		ofDrawCircle(0, 0, shapeSize);
		ofPopMatrix();
		//Decagon
		ofPushMatrix();
		ofRotateDeg(shapeDegRot * 7);
		ofTranslate(circum, 0, 0);
		ofSetColor(ofColor::silver);
		ofSetCircleResolution(10);
		ofDrawCircle(0, 0, shapeSize);
		ofPopMatrix();
		//Image
		//image.draw(0, 0);
		//bulletImage.draw(0, 0);
		// Add background music
		// Add Start sound

}
//--------------------------------------------------------------
void ofApp::draw() {
	ofPushMatrix();
	ofSetColor(ofColor::white);
	bgImg.draw(0, 0);
	string frameRate = "Frame Rate: " + ofToString(ofGetFrameRate());
	ofDrawBitmapString(frameRate, ofGetWindowWidth() - 200,  100);
	ofPopMatrix();
	//Background
	switch (gs)
	{
	case Title:
		drawStart();
		break;
	case Play:
		drawElapsedTime();
		if (spriteToggle)
			hero.draw();
		else
			hero.drawTriangle();
		//hero.drawHeading();
		for (int i = 0; i < pentagons.size(); i++)
			pentagons[i].draw();
		for (int i = 0; i < triangles.size(); i++)
			triangles[i].draw();
		for (int i = 0; i <playerBullets.size(); i++)
			playerBullets[i].draw();
		for (int i = 0; i < enemyBullets.size(); i++)
			enemyBullets[i].draw();
		if(!bHide) gui.draw();
		draw_lives();
		break;
	case End:
		my32Font.drawString("Game Over", center.x - gameOverWidth/2, center.y);
		if (!death)
			timeAlive = ofGetElapsedTimef() - startTime;
		endtime = "Time Alive: " + ofToString(timeAlive);
		fonty.drawString(endtime, center.x-fonty.stringWidth(endtime)/2, center.y + 40);
		spaceText = "Press SPACE to return to Main Menu";
		fonty.drawString(spaceText, center.x-fonty.stringWidth(spaceText)/2, center.y + 80);
		death = true;
		break;
	default:
		cout << "An error occured in draw";
	}

}

void ofApp::spawnEnemies()
{
	if (lc.shouldSpawn())
	{
		for (int i = 0; i < lc.getSpawnAmount(); i++)
		{
			Triangle t;
			Pentagon p;
			switch (lc.getLevel())
			{
			case 1:
				t.setup(shapeSize, 3);
				triangles.push_back(t);
				//enemies.push_back(t);
				break;
			case 2:
				p.setup(shapeSize, 5, homing, 0,&heroImg);
				pentagons.push_back(p);
				//enemies.push_back(p);
				break;
			case 3:
				t.setup(shapeSize, 3);
				triangles.push_back(t);
				p.setup(shapeSize, 5, homing, 0,&heroImg);
				pentagons.push_back(p);
				//enemies.push_back(t);
				//enemies.push_back(p);
				break;
			default:
				break;

			}
		}
	}
}

void ofApp::draw_lives() {
	for (int i = 0; i < hero.getNRG(); i++) {
		ofPushMatrix();
		ofSetColor(hero.getColor());
		heroImg.setAnchorPoint(heroImg.getWidth() / 2, heroImg.getHeight() / 2);
		heroImg.draw(ofGetWindowWidth() - (i * 100) + 100, 250, 100, 100);
		ofPopMatrix();
	}
}



void ofApp::checkPlayerCollisions() {

	for (int i = 0; i < triangles.size(); ++i)
	{
		//if player & triganle collision
		bool col = triangles[i].collisionCheck(hero.getPos(), hero.getWidth());
		if (col)
		{
			//decrement life
			hero.loseNRG();
			//destroy triangle
			triangles.erase(triangles.begin() + i);
		}
	}
	for (int i = 0; i < pentagons.size(); ++i)
	{
		//if player & triganle collision
		bool col = pentagons[i].collisionCheck(hero.getPos(), hero.getWidth());
		if (col)
		{
			//decrement life
			hero.loseNRG();
			//destroy triangle
			pentagons.erase(pentagons.begin() + i);
		}
	}

	//Check if out of lives to end game 
	if (hero.getNRG() == 0)
		gs = End;


	//triangle to triangle collision
	if (triangles.size() > 1)
	{
		for (int i = 0; i < triangles.size()-1; ++i)
		{
			for (int j = i + 1; j < triangles.size(); ++j)
			{
				bool col = triangles[i].collisionCheck(triangles[j].getPos(), triangles[j].getWidth());
				if (col)
				{
					glm::vec3 colVec = triangles[i].getPos() - triangles[j].getPos();
					triangles[i].setPos(triangles[i].getPos() + colVec);
					cout << "collide" << endl;
				}
				//triangles[i].update(hero.getPos());
			}
		}

	}

}

void ofApp::check_bullet_collisions() {

	for (int e = triangles.size() - 1; e >= 0; e--) {
		for (int i = 0; i < playerBullets.size(); ++i) {
			float bullet2Enemy = ofDist(playerBullets[i].getPos().x, playerBullets[i].getPos().y, triangles[e].getPos().x, triangles[e].getPos().y);
			float imgWidthCompensation = (triangles[e].getWidth() + playerBullets[i].getWidth())/2;
			if ( bullet2Enemy <  imgWidthCompensation) {
				triangles.erase(triangles.begin() + e);
				playerBullets.erase(playerBullets.begin() + i);

			}
		}
	}
//~~~~~~~~~~~~~~~~~~~~~
	for (int e = pentagons.size() - 1; e >= 0; e--) {
		for (int i = 0; i < playerBullets.size(); ++i) {
			float bullet2Enemy = ofDist(playerBullets[i].getPos().x, playerBullets[i].getPos().y, pentagons[e].getPos().x, pentagons[e].getPos().y);
			float imgWidthCompensation = (pentagons[e].getWidth() + playerBullets[i].getWidth())/2;
			if ( bullet2Enemy <  imgWidthCompensation) {
				pentagons.erase(pentagons.begin() + e);
				playerBullets.erase(playerBullets.begin() + i);

			}
		}
	}
	for (int i = enemyBullets.size()-1; i>=0 ;i--)
	{
		if (ofDist(enemyBullets[i].getPos().x, enemyBullets[i].getPos().y, hero.getPos().x, hero.getPos().y) < (enemyBullets[i].getWidth() + hero.getWidth()) / 2) {
			enemyBullets.erase(enemyBullets.begin() + i);
			hero.loseNRG();
			if (hero.getNRG() <= 0) 
				gs = End;
		}
	}

}

void ofApp::update_bullets() {
	check_bullet_collisions();
	for (int i = 0; i <playerBullets.size(); ++i) {
		playerBullets[i].update();
		if (playerBullets[i].getPos().y -playerBullets[i].getWidth() / 2 < 0 ||playerBullets[i].getPos().y +playerBullets[i].getWidth() / 2 > ofGetHeight()) {
			playerBullets.erase(playerBullets.begin() + i);
		}
	}
	for (int i = 0; i <enemyBullets.size(); ++i) {
		enemyBullets[i].update();
		if (enemyBullets[i].getPos().y -enemyBullets[i].getWidth() / 2 < 0 ||enemyBullets[i].getPos().y +enemyBullets[i].getWidth() / 2 > ofGetHeight()) {
			enemyBullets.erase(enemyBullets.begin() + i);
		}
	}
	// we'll call a collision check function here shortly
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (gs)
	{
	case Title:
		if (key == OF_KEY_RETURN || key == ' ')
		{
			startTime = ofGetElapsedTimef();
			lc.setLevel(1);
			gs = Play;
		}
		break;
	case Play:
		if (key == OF_KEY_UP || key == 'w') 
			hero.setUpPressed(true);
		if (key == OF_KEY_LEFT || key == 'a') 
			hero.setLeftPressed(true);
		if (key == OF_KEY_DOWN || key == 's') 
			hero.setDownPressed(true);
		if (key == OF_KEY_RIGHT || key == 'd') 
			hero.setRightPressed(true);
		if (key == ' ') {
			cout << "space" << endl;
		}
		if (key == 'p')
		{
			Pentagon p;
			p.setup(shapeSize, 5, homing, 0,&heroImg);
			pentagons.push_back(p);
			//enemies.push_back(p);
		}
		if (key == 't')
		{
			Triangle t;
			t.setup(shapeSize, 3, sCannon, 10,&heroImg);
			//t.setup(shapeSize, 3);
			triangles.push_back(t);
			//enemies.push_back(t);
		}
		if (key == 'h' || key == 'H')
		{
			bHide = !bHide;
		}

		break;
	case End:
		if (key == ' ')
		{
			death = false;
			enemyBullets.clear();
			playerBullets.clear();
			pentagons.clear();
			triangles.clear();
			hero.setPos(glm::vec3(ofGetWidth()/2, ofGetHeight()/2, 0));
			hero.setNRG(5);
			gs = Title;
		}
		break;
	default:
		cout << "error in keyPressed" << endl;
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == OF_KEY_UP || key == 'w') {
		hero.setUpPressed(false);
	}
	if (key == OF_KEY_LEFT || key == 'a') {
		hero.setLeftPressed(false);
	}
	if (key == OF_KEY_DOWN || key == 's') {
		hero.setDownPressed(false);
	}
	if (key == OF_KEY_RIGHT || key == 'd') {
		hero.setRightPressed(false);
	}
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	/*
	switch (button)
	{
	case 0:
		PlayerBullet pb(hero.getPos(), hero.getSpeed(), 1.0, &bulletImage);
		pb.setDirection(glm::vec3(x, y));
		break;
	case 2:

		break;
	default:
		break;
	}
*/

	if (button == 0 && gs == Play)
	{
		//hero matrix - click matrix to get heading
		// heading normalized ++

		//float rot = glm::orientedAngle(,glm::vec3(0,1,0),glm::vec3(0,0,1))
		PlayerBullet pb(hero.getPos(), 1 , 1.0,  &bulletImage);
		pb.setDirection(glm::vec3(x, y,0));
		playerBullets.push_back(pb);
	}
	if (button == 2)
	{

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
