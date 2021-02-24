#pragma once
#include "gameNode.h"

class Player;

enum STAGETYPE
{
	ST_EASY,
	ST_NORMAL,
	ST_HARD,
	ST_BOSS,
};

class StageManager : public gameNode
{
private:
	STAGETYPE _currentStage;

	Stage* _easy;
	Stage* _normal;
	Stage* _hard;
	Stage* _boss;
	
	Stage* _stage;
	Player* _player;

public:
	void SetPlayerAddressLink(Player* player) { _player = player; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void SetStage(STAGETYPE type);

	Stage*& getStage() { return _stage; }
	STAGETYPE getCurrentStage() { return _currentStage; }
};

