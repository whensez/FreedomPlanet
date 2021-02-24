#include "stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init()
{
	GALLERYMANGER->init(_backBuffer);
	CAMERAMANAGER->init();
	SCENEMANAGER->init();
	UIMANAGER->SetIsActive(true);
	//생성
	_stageM = new StageManager;
	_player = new Player;

	//연결
	UIMANAGER->SetPlayerAddressLink(_player);
	SAVELOADMANAGER->SetPlayerAddressLink(_player);
	_player->SetStageMAddressLink(_stageM);
	_stageM->SetPlayerAddressLink(_player);

	//초기화
	_player->init();
	_stageM->init();

	_deadSceneTimer = 0;
	_deadSceneFrame = 0;
	_overloopY = 0;
	_overloopTimer = 0;
	IMGMANAGER->addImage("ui_gameover", "image/ui_gameover.bmp", 300, 160, true, MAGENTA);
	IMGMANAGER->addImage("ui_pressSpacebar", "image/ui_pressSpacebar.bmp", 300, 40, true, MAGENTA);
	
	return S_OK;
}

void GameScene::release()
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_stageM);
}

void GameScene::update()
{
	if (UIMANAGER->GetIsGaming())
	{
		_stageM->update();
		_player->update();
		EFFECTMANAGER->update();
	}

	GALLERYMANGER->update();
	UIMANAGER->update();
	SAVELOADMANAGER->update();

	if (_player->GetInfo().isDead)
	{
		UIMANAGER->SetIsActive(false);

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) SCENEMANAGER->changeScene("title");	//사망 시 스페이스 누르면 타이틀

	}

	if (TIMEMANAGER->getWorldTime() - _deadSceneTimer > 0.6f) _deadSceneFrame = 0;
	if (TIMEMANAGER->getWorldTime() - _deadSceneTimer > 1.2f)
	{
		_deadSceneTimer = TIMEMANAGER->getWorldTime();
		_deadSceneFrame = 1;
	}

	if (TIMEMANAGER->getWorldTime() - _overloopTimer > 0.5f) ++_overloopY;
	else --_overloopY;
	if (TIMEMANAGER->getWorldTime() - _overloopTimer > 1.0f) _overloopTimer = TIMEMANAGER->getWorldTime();

	
}

void GameScene::render()
{
	_stageM->render();			//스테이지
	if (_player->GetInfo().isDead)
	{
		IMGMANAGER->findImage("background8")->frameRender(getMapDC(), CAMERAMANAGER->GetX() - 1280 / 2, CAMERAMANAGER->GetY() - 720 / 2, _deadSceneFrame, 0);
		IMGMANAGER->findImage("ui_gameover")->render(getMapDC(), CAMERAMANAGER->GetX()-150, CAMERAMANAGER->GetY()-150 + _overloopY);
		IMGMANAGER->findImage("ui_pressSpacebar")->render(getMapDC(), CAMERAMANAGER->GetX()-150, CAMERAMANAGER->GetY()+300 - _overloopY);
	}
	_player->render();			//플래이어
	if (!_player->GetInfo().isDead) EFFECTMANAGER->render();	//이펙트

	//================= 맵, 미니맵, UI =================z
	CAMERAMANAGER->mapRender(_mapBuffer, getBackDC());
	CAMERAMANAGER->minimapRender(_miniMapBuffer, getBackDC());
	UIMANAGER->render(getBackDC());
	GALLERYMANGER->render();
}
