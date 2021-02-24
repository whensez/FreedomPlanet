#include "stdafx.h"
#include "UIManager.h"
#include "Player.h"
#include "Stage.h"
HRESULT UIManager::init()
{
	IMGMANAGER->addImage("ui_milla1", "image/ui_milla1.bmp", 172, 92, true, MAGENTA);
	IMGMANAGER->addImage("ui_milla2", "image/ui_milla2.bmp", 172, 92, true, MAGENTA);
	IMGMANAGER->addImage("ui_milla3", "image/ui_milla3.bmp", 172, 92, true, MAGENTA);
	IMGMANAGER->addImage("ui_milla4", "image/ui_milla4.bmp", 172, 92, true, MAGENTA);

	IMGMANAGER->addImage("ui_HPBar0", "image/ui_HPBar0.bmp", 90, 12, true, MAGENTA);
	IMGMANAGER->addImage("ui_HPBar1", "image/ui_HPBar1.bmp", 90, 12, true, MAGENTA);
	IMGMANAGER->addImage("ui_HPBar2", "image/ui_HPBar2.bmp", 90, 12, true, MAGENTA);

	IMGMANAGER->addImage("ui_pause", "image/ui_pause.bmp", 75, 100, true, MAGENTA);

	_HPBar = IMGMANAGER->addImage("ui_HPBar3", "image/ui_HPBar3.bmp", 90, 12, true, MAGENTA);

	_dashBar = IMGMANAGER->addImage("ui_dashBar", "image/ui_dashBar.bmp", 300, 21, true, MAGENTA);
	_dashFrame = IMGMANAGER->addImage("ui_dashFrame", "image/ui_dashFrame.bmp", 348, 54, true, MAGENTA);

	_state = IMGMANAGER->findImage("ui_milla1");
	
	_life = IMGMANAGER->addImage("ui_life", "image/ui_life.bmp", 40, 40, true, MAGENTA);

	_minimapWidth = CAMERAMANAGER->GetMinimapWidth();
	_minimap = IMGMANAGER->addImage("ui_minimap", "image/ui_minimap.bmp", 250, 150, true, MAGENTA);
	_crystal = IMGMANAGER->addFrameImage("ui_crystal", "image/item_crystal.bmp", 132,42,6,1,true,MAGENTA);
	_number = IMGMANAGER->addFrameImage("ui_number", "image/ui_number.bmp", 300, 30, 10, 1, true, MAGENTA);
	_time = IMGMANAGER->addImage("ui_time", "image/ui_time.bmp", 348, 51, true, MAGENTA);

	_saveText = IMGMANAGER->addImage("ui_saveText","image/ui_saveText.bmp", 150, 30, true, MAGENTA, true);
	
	_saveTextAlpha = 0;

	_isActive = true;
	_isGaming = true;

	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
	if(_saveTextAlpha > 5) _saveTextAlpha -= 5;
	if (_saveText < 0) _saveText = 0;

	//Enter를 누르면 게임을 일시정지한다.
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) _isGaming = !_isGaming;

	//U를 누르면 UI를 열고 닫는다.
	if (KEYMANAGER->isOnceKeyDown('U')) _isActive = !_isActive;

	//M을 누르면 미니맵을 연다.
	if (KEYMANAGER->isOnceKeyDown('M')) CAMERAMANAGER->SetMinimapToggle();

	if(_player->GetInfo().state ==PS_DAMAGE) _state = IMGMANAGER->findImage("ui_milla4");
	else if (_player->GetInfo().state == PS_RUN) _state = IMGMANAGER->findImage("ui_milla3");
	else if (_player->GetInfo().state == PS_BEAM || _player->GetInfo().state == PS_ATTACK) _state = IMGMANAGER->findImage("ui_milla2");
	else  _state = IMGMANAGER->findImage("ui_milla1");
}

void UIManager::render(HDC hdc)
{
	if(!_isGaming) IMGMANAGER->findImage("ui_pause")->render(hdc, WINSIZEX / 2, WINSIZEY / 2);

	if (!_isActive)
	{
		return;
	}

	//캐릭터
	_state->render(hdc, 10, WINSIZEY - 102);

	//대쉬 바
	_dashBar->render(hdc, 32, 24, 0, 0, ((float)_player->GetInfo().gauge / _player->GetInfo().gaugeMax) * _dashBar->getWidth(), _dashBar->getHeight());
	_dashFrame->render(hdc, 10, 20);

	//미니맵
	if (CAMERAMANAGER->GetIsActiveMinimap()) _minimap->render(hdc, WINSIZEX - _minimapWidth - 25, 15);

	//생명
	for (int i = 0; i < _player->GetInfo().life; i++) _life->render(hdc, 20 + i * 40, 80);

	//크리스탈
	_crystal->frameRender(hdc, WINSIZEX / 2-80, 35, 2, 0);

	//개수
	_number->frameRender(hdc, WINSIZEX / 2-40, 40, (_player->GetInfo().crystal/100), 0);
	_number->frameRender(hdc, WINSIZEX/2, 40, (_player->GetInfo().crystal /10)%10, 0);
	_number->frameRender(hdc, WINSIZEX / 2+40, 40, _player->GetInfo().crystal %10, 0);

	//시간
	_time->render(hdc, WINSIZEX - 350, WINSIZEY-110);
	_number->frameRender(hdc, WINSIZEX - 60, WINSIZEY - 105, (int)_stage->getStageTimer() % 10, 0);
	_number->frameRender(hdc, WINSIZEX - 100, WINSIZEY - 105, (int)(_stage->getStageTimer() / 10)%6, 0);
	_number->frameRender(hdc, WINSIZEX - 170, WINSIZEY - 105, (int)(_stage->getStageTimer() / 60)%10, 0);
	_number->frameRender(hdc, WINSIZEX - 210, WINSIZEY - 105, (int)(_stage->getStageTimer() / 600)%6, 0);

	//저장 글자
	_saveText->alphaRender(hdc, WINSIZEX / 2, WINSIZEY - 50,_saveTextAlpha);
}

void UIManager::ProgressBarRender(HDC hdc, image * img, int x, int y, float current, float Max)
{
	_HPBar->render(hdc, x - img->getWidth() / 2, y);

	img->stRender(hdc, x- img->getWidth()/2, y, ((float)current / Max) * img->getWidth(), img->getHeight());
}

void UIManager::ProgressBarRender(HDC hdc, image * img, int x, int y, float current, float Max, float xRatio, float yRatio)
{
	_HPBar->stRender(hdc, x - img->getWidth()*xRatio / 2, y, img->getWidth()*xRatio, img->getHeight()*yRatio, 0, 0, img->getWidth(), img->getHeight());

	img->stRender(hdc, x - img->getWidth()*xRatio / 2, y, ((float)current / Max) * img->getWidth()*xRatio, img->getHeight()*yRatio,0,0,img->getWidth(), img->getHeight());
}