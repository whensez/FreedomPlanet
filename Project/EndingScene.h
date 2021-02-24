#pragma once
#include "gameNode.h"


class EndingScene : public gameNode
{

	float _backTimer;
	image* _background;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

