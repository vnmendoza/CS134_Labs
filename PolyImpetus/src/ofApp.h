#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "Player.h"
#include "Hero.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Triangle.h"
#include "Pentagon.h"
#include "LevelController.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void draw_lives();

		void checkPlayerCollisions();

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
		void drawStart();
		void update_bullets();
		void check_bullet_collisions();
		void spawnEnemies();
		void drawElapsedTime();
		//Level
		LevelController lc;

	ofImage heroImg, bulletImage,enemyBullet,bgImg;
	ofTrueTypeFont myFont, my32Font,fonty;
	ofxPanel gui;
	ofxLabel label;
	ofxButton button;
	ofxToggle spriteToggle;
	ofParameterGroup mainGroup;
	ofParameter<int> levelSlider;
	//Hero
	ofParameterGroup heroGroup;
	ofParameter<int> heroSpeedSlider;
	ofParameter<float> heroRotationSpeedSlider, heroSizeSlider;
	ofParameter<int> bulletSpeedSlider;
	float timeAlive,startTime;
	//Enemies
	ofParameterGroup enemyGroup;
	ofParameter<int> enemySpeedSlider,eSpawnAmnt;
	ofParameter<float> eSpawnRate,eLifespan,eFireRate;
	//Enemy triangle;
	vector<Triangle> triangles;
	vector<Pentagon> pentagons;
	vector<Enemy> enemies;
	vector<PlayerBullet> playerBullets;
	vector<EnemyBullet> enemyBullets;


	//MainMenu and Setup
	int rotation, enterWidth, instWidth,gameOverWidth,
	instHeight,circum,shapeDegRot,shapeSize;
	glm::vec3 center, tester;
	string instructions, enter, gameOver;
	bool death=false;
	enum GameState {Title, Play, End};
	GameState gs;
	string endtime,spaceText;
	Hero hero;
	Triangle tri;
	Pentagon pentagon;
	bool bHide = false;

	
};
