#pragma once
#include "Enemy.h"

class Hog : public Enemy
{
private:

public:
	Hog() {}
	~Hog() {}

	virtual HRESULT init(Player* player, Stage* stage, RECT rc);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();
	virtual void rcMake();
};

