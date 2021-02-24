#pragma once
#include "gameNode.h"

struct tagImg
{
	image* img;
	int loopX;
	int loopY;
	int alpha;
	RECT rc;
	bool isSelect;
};

class TitleScene : public gameNode
{
private:
	bool _isReverse;
	float _backTimer;
	tagImg _background;
	tagImg _title;
	tagImg* _menu;
	float _timer;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

