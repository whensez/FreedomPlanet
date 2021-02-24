#include "stdafx.h"
#include "NormalStage.h"
#include "Enums.h"
#include "Player.h"

#include "Spore.h"

HRESULT NormalStage::init()
{
	Stage::init();
	return S_OK;
}

void NormalStage::release()
{
	Stage::release();
}

void NormalStage::update()
{
	Stage::update();
	CAMERAMANAGER->SetPos(_player->GetInfo().x, _player->GetInfo().y, 0, 100, 3);

	if (++_timer % 3 == 0)
	{
		_timer = 0;
		_background->_loopX -= 1;
	}

	//중간 배경
	_vMiddleGround[0]->_rc = RectMake(0, CAMERAMANAGER->GetY() + WINSIZEY / 2 - _vMiddleGround[0]->_img->getHeight(), CAMERAMANAGER->GetMapXSize(), _vMiddleGround[0]->_img->getHeight());
	_vMiddleGround[1]->_rc = RectMake(0, CAMERAMANAGER->GetMapYSize() - WINSIZEY-50, CAMERAMANAGER->GetMapXSize(), CAMERAMANAGER->GetMapYSize() - WINSIZEY-50+_vMiddleGround[1]->_img->getHeight());
}

void NormalStage::render()
{
	//뒷배경
	_background->_img->loopRender(getMapDC(), &CAMERAMANAGER->GetMapRect(), 0, _background->_loopX);
	_background->_img->loopRender(getMinimapDC(), &CAMERAMANAGER->GetMapRect(), 0, 0);

	//중간 배경
	_vMiddleGround[0]->_img->loopRender(getMapDC(), &_vMiddleGround[0]->_rc, _player->GetInfo().x / 2, 0 );
	_vMiddleGround[1]->_img->loopRender(getMapDC(), &_vMiddleGround[1]->_rc, _player->GetInfo().x / 4, 0);

	Stage::render();
}

void NormalStage::SetbackGround()
{
	CAMERAMANAGER->SetMap(*this, 1500, 2000);

	//뒷 배경
	_background = new Background;
	_background->_img = IMGMANAGER->findImage("background6");

	//중간 배경
	for (int i = 0; i < 2; i++)
	{
		Middleground* _middleground = new Middleground;
		_vMiddleGround.push_back(_middleground);
	}
	_vMiddleGround[0]->_img = IMGMANAGER->findImage("middleground7");
	_vMiddleGround[1]->_img = IMGMANAGER->findImage("middleground6");
}

void NormalStage::SetTerrain()
{
	//지형
	for (int i = 0; i < 10; i++)
	{
		Terrain* terrain = new Terrain;
		_vTerrain.push_back(terrain);
	}

	_vTerrain[0]->SetGround(4, 0, 1700, P_GROUND, GT_ROAD);
	_vTerrain[1]->SetGround(0, 320, 1580, P_PLATFORM, GT_GRASS);
	_vTerrain[2]->SetGround(1, 500, 1490, P_PLATFORM, GT_GROUND);
	_vTerrain[3]->SetGround(0, 400, 1350, P_PLATFORM, GT_GROUND);
	_vTerrain[4]->SetGround(1, 600, 1250, P_PLATFORM, GT_GRASS);
	_vTerrain[5]->SetGround(0, 450, 1120, P_PLATFORM, GT_GROUND);
	_vTerrain[6]->SetGround(1, 500, 980, P_PLATFORM, GT_GRASS);
	_vTerrain[7]->SetGround(0, 700, 850, P_PLATFORM, GT_GROUND);
	_vTerrain[8]->SetGround(1, 400, 720, P_PLATFORM, GT_GROUND);
	_vTerrain[9]->SetGround(0, 550, 590, P_PLATFORM, GT_GRASS);
}

void NormalStage::SetObject()
{
	//오브젝트


}

void NormalStage::SetEnemy()
{
	for (int i = 0; i < 4; i++)
	{
		Enemy* slime = new Slime;
		_vEnemy.push_back(slime);

		Enemy* spore = new Spore;
		_vEnemy.push_back(spore);
	}

	_vEnemy[0]->init(_player, this, _vTerrain[1]->getCollision().rc);
	_vEnemy[1]->init(_player, this, _vTerrain[2]->getCollision().rc);
	_vEnemy[2]->init(_player, this, _vTerrain[3]->getCollision().rc);
	_vEnemy[3]->init(_player, this, _vTerrain[4]->getCollision().rc);

	_vEnemy[4]->init(_player, this, _vTerrain[5]->getCollision().rc);
	_vEnemy[5]->init(_player, this, _vTerrain[6]->getCollision().rc);
	_vEnemy[6]->init(_player, this, _vTerrain[7]->getCollision().rc);
	_vEnemy[7]->init(_player, this, _vTerrain[8]->getCollision().rc);

}

void NormalStage::SetBullet()
{
	//총알
	_cannon = new Cannon;
	_cannon->init("bullet1", 5, 500);
	_cannon->SetPlayerAddressLink(_player);
	_cannon->SetStageAddressLink(this);
}

void NormalStage::SetItem()
{
	//아이템
	_item = new Item;
	_item->init();
	_item->SetPlayerAddressLink(_player);

	for (int j = 1; j < 10; j++)
	{
		for (int i = 0; i < (_vTerrain[j]->getCollision().rc.right - _vTerrain[j]->getCollision().rc.left) / 100; i++)
		{
			_item->make(_vTerrain[j]->getCollision().rc.left + 100 * i + 80, _vTerrain[j]->getCollision().rc.top - 30, I_CRYSTAL, true);
		}
	}
}

void NormalStage::StartEvent()
{
}
