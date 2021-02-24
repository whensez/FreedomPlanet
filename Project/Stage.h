#pragma once
#include "gameNode.h"

#include "Hog.h"
#include "Slime.h"
#include "Turret.h"

#include "FireFly.h"

#include "Bullet.h"
#include "Item.h"

#include <vector>

#include "StageObject.h"

enum POSITION;
class Player;

class Stage : public gameNode
{
protected:

	typedef vector<Middleground*> vMiddleground;
	typedef vector<Terrain*> vTerrain;
	typedef vector<Object*> vObject;
	typedef vector<Enemy*> vEnemy;

	vMiddleground _vMiddleGround;
	vTerrain _vTerrain;
	vObject _vObject;
	vEnemy _vEnemy;
	
	Cannon* _cannon;
	Item* _item;

	int _timer;
	float _itemTimer;
	float _stageTime;
	float _stageTimer;
	float _sceneTimer;
	bool _isClear;
	bool _isScene;

	Background* _background;

	Player* _player;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void SetbackGround() = 0;
	virtual void SetTerrain() = 0;
	virtual void SetObject() = 0;
	virtual void SetEnemy() = 0;
	virtual void SetBullet() = 0;
	virtual void SetItem() = 0;


	virtual void StartEvent() = 0;

	void SetPlayerAddressLink(Player* player) { _player = player; }

	//getter
	vTerrain& getvTerrain() { return _vTerrain; }
	Cannon* getBullet() { return _cannon; }
	Item* getItem() { return _item; }
	float getStageTimer() { return _stageTimer; }
	bool getIsClear() { return _isClear; }
};