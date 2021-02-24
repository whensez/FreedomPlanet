#include "stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init()
{
	_background = IMGMANAGER->addFrameImage("background8", "image/backGround8.bmp", 2560, 1500, 2, 1, false, MAGENTA);
	return S_OK;
}

void EndingScene::release()
{
}

void EndingScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) SCENEMANAGER->changeScene("title");

	if (TIMEMANAGER->getWorldTime() - _backTimer > 0.5f)
	{
		_backTimer = TIMEMANAGER->getWorldTime();
		_background->setFrameX(0);
	}
	else if (TIMEMANAGER->getWorldTime() - _backTimer > 0.25f)
	{
		_background->setFrameX(1);
	}
	
}

void EndingScene::render()
{
	_background->frameRender(getBackDC(), 0, 0);
}
