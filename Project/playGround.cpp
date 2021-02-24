#include "stdafx.h"
#include "playGround.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "EndingScene.h"

playGround::playGround()
{
}

playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	//¾À Ãß°¡
	SCENEMANAGER->addScene("title", new TitleScene);
	SCENEMANAGER->addScene("game", new GameScene);
	SCENEMANAGER->addScene("ending", new EndingScene);

	//Å¸ÀÌÆ² ¾À ¼¼ÆÃ
	SCENEMANAGER->changeScene("title");
	//SCENEMANAGER->changeScene("ending");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

}

void playGround::update()
{
	gameNode::update();

	//¾À ¾÷µ¥ÀÌÆ®
	SCENEMANAGER->update();
}

void playGround::render()
{
	PatBlt(getBackDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	
	//================ ·»´õ ½ÃÀÛ =================
	//¾À ·»´õ
	SCENEMANAGER->render();
	//================= µð¹ö±ë ¿ë =================
	//FPS È®ÀÎ
	if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getBackDC());

	//================= ÀÌÁß ¹öÆÛ¸µ =================
	_backBuffer->render(getHDC());
}

