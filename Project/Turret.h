#pragma once
#include "Enemy.h"

class Turret : public Enemy
{
private:


public:
	Turret(){}
	~Turret(){}

	virtual HRESULT init(Player* player, Stage* stage, RECT rc);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void rcMake();
	virtual void attack();
};

