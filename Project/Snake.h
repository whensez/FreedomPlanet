#pragma once
#include "Enemy.h"

#define SNAKEBODY 30

enum BOSSPHASE
{
	BP_EASY,
	BP_NORMAL,
	BP_HARD,
};
enum BOSSPATTERN
{
	BP_IDLE,
	BP_FOLLOW,
	BP_RSPIN,
	BP_LSPIN,
	BP_8Height,
	BP_8Width,
	BP_CENTER,
};

struct tagBody
{
	float _angle;
	float _x, _y;
	RECT _rc;
	bool _isDamage;
};

class Snake : public Enemy
{
	float patternTimer;
	bool isOverPI;

	image* _headImg;
	image* _bodyImg;
	BOSSPATTERN _currentPattern;
	BOSSPATTERN _nextPattern;
	BOSSPATTERN _prevPattern;
	BOSSPHASE _phase;

	tagBody _body[SNAKEBODY];
	float _radius;

	float _patternInterval;

	virtual HRESULT init(Player* player, Stage* stage, int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	void bodyMove();
	virtual void rcMake();

	void move();
	void attack();
	void damage();


	void setPattern(BOSSPATTERN pattern);
	void setPhase(BOSSPHASE phase);
	void phaseSetting();

};

