#pragma once


#include "singletonBase.h"

class Player;
class StageManager;

class SaveLoadManager : public singletonBase <SaveLoadManager>
{

private:
	Player* _player;
	StageManager* _stageM;

public:
	SaveLoadManager() {};
	~SaveLoadManager() {};

	void update();
	void save();
	void load();


	void SetPlayerAddressLink(Player* player) { _player = player; }
	void SetStageAddressLink(StageManager* stage) { _stageM = stage; }

	vector<string> vSave;

	void pushData(vector<string>* vector, int x);
};

