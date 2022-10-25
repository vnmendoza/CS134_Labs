#pragma once
#include "ofMain.h"

class LevelController
{
private:
	float startTime;
	float spawnRate;
	int spawnAmount;
	int level;
public:
	LevelController();
	bool shouldSpawn();
	void setup(float spawn_rate, int spawn_amount);
	void setup(float spawn_rate, int spawn_amount, int lvl);
	void setSpawnAmount(int amount);
	int getSpawnAmount();
	int getLevel();
	void setLevel(int lvl);

};

