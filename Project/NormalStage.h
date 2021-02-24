#pragma once
#include "Stage.h"

class NormalStage : public Stage
{

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void SetbackGround();
	virtual void SetTerrain();
	virtual void SetObject();
	virtual void SetEnemy();
	virtual void SetBullet();
	virtual void SetItem();


	virtual void StartEvent();
};

