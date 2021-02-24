#include "stdafx.h"
#include "BossStage.h"
#include "Player.h"

#include "Snake.h"

HRESULT BossStage::init()
{
	Stage::init();

	return S_OK;
}

void BossStage::release()
{
}

void BossStage::update()
{
	Stage::update();

	if (_isClear)
	{
		CAMERAMANAGER->SetMagnification(1.4, 0.01f);
		_player->SetState(PS_SMILE);
		if(KEYMANAGER->isOnceKeyDown(VK_F5)) SCENEMANAGER->changeScene("ending");
	}

	CAMERAMANAGER->SetPos(_player->GetInfo().x, _player->GetInfo().y, 0, 100, 3);

	if (++_timer % 2 == 0)
	{
		_timer = 0;
		_background->_loopX -= 1;
	}

	_vMiddleGround[0]->_rc = RectMake(0, CAMERAMANAGER->GetMapYSize() - _vMiddleGround[0]->_img->getHeight() - 100, CAMERAMANAGER->GetMapXSize(), _vMiddleGround[0]->_img->getHeight());
	_vMiddleGround[1]->_rc = RectMake(0, CAMERAMANAGER->GetY() - WINSIZEY / 2, CAMERAMANAGER->GetMapXSize(), _vMiddleGround[1]->_img->getHeight());

}

void BossStage::render()
{
	//뒷배경
	_background->_img->loopRender(getMapDC(), &CAMERAMANAGER->GetMapRect(), _background->_loopX, 0);
	_background->_img->loopRender(getMinimapDC(), &CAMERAMANAGER->GetMapRect(), 0, 0);

	//중간 배경
	for (int i = 0; i < _vMiddleGround.size(); i++) _vMiddleGround[i]->_img->loopRender(getMapDC(), &_vMiddleGround[i]->_rc, _vMiddleGround[i]->_loopX, 0);

	Stage::render();
}

void BossStage::SetbackGround()
{
	CAMERAMANAGER->SetMap(*this, 1800, 900);

	//뒷 배경
	_background = new Background;
	_background->_img = IMGMANAGER->findImage("background1");

	//중간 배경
	for (int i = 0; i < 2; i++)
	{
		Middleground* _middleground = new Middleground;
		_vMiddleGround.push_back(_middleground);
	}

	_vMiddleGround[0]->_img = IMGMANAGER->findImage("middleground1");
	_vMiddleGround[1]->_img = IMGMANAGER->findImage("middleground7");

}

void BossStage::SetTerrain()
{
	//지형
	for (int i = 0; i < 7; i++)
	{
		Terrain* terrain = new Terrain;
		_vTerrain.push_back(terrain);
	}

	_vTerrain[0]->SetGround(10, 5, 750, P_GROUND, GT_GROUND);
	_vTerrain[1]->SetGround(1, 300, 650, P_PLATFORM, GT_GROUND);
	_vTerrain[2]->SetGround(2, 400, 450, P_PLATFORM, GT_GROUND);
	_vTerrain[3]->SetGround(0, 100, 550, P_PLATFORM, GT_GROUND);
	_vTerrain[4]->SetGround(1, 700, 330, P_PLATFORM, GT_GROUND);
	_vTerrain[5]->SetGround(1, 1000, 620, P_PLATFORM, GT_GROUND);
	_vTerrain[6]->SetGround(0, 1400, 500, P_PLATFORM, GT_GROUND);

}

void BossStage::SetObject()
{
}

void BossStage::SetEnemy()
{
	Enemy* _Snake = new Snake;
	_Snake->init(_player, this, 0, 900);
	_vEnemy.push_back(_Snake);
}

void BossStage::SetBullet()
{
	//총알
	_cannon = new Cannon;
	_cannon->init("bullet1", 5, 500);
	_cannon->SetPlayerAddressLink(_player);
	_cannon->SetStageAddressLink(this);
}

void BossStage::SetItem()
{
	//아이템
	_item = new Item;
	_item->init();
	_item->SetPlayerAddressLink(_player);

	_item->make(WINSIZEX / 2, WINSIZEY - 300, I_BUBBLE, true);

}

void BossStage::StartEvent()
{
}
