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

	//�� �߰�
	SCENEMANAGER->addScene("title", new TitleScene);
	SCENEMANAGER->addScene("game", new GameScene);
	SCENEMANAGER->addScene("ending", new EndingScene);

	//Ÿ��Ʋ �� ����
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

	//�� ������Ʈ
	SCENEMANAGER->update();
}

void playGround::render()
{
	PatBlt(getBackDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	
	//================ ���� ���� =================
	//�� ����
	SCENEMANAGER->render();
	//================= ����� �� =================
	//FPS Ȯ��
	if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getBackDC());

	//================= ���� ���۸� =================
	_backBuffer->render(getHDC());
}

