#pragma once
#include "gameNode.h"

#include "StageManager.h"
#include "Player.h"

class GameScene : public gameNode
{
private:
	Player*			_player;
	StageManager*	_stageM;
	float _deadSceneTimer;
	int _deadSceneFrame;
	float _overloopTimer;
	float _overloopY;
public:
	GameScene() {}
	~GameScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

