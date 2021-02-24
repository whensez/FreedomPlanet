#include "stdafx.h"
#include "HardStage.h"
#include "Player.h"

HRESULT HardStage::init()
{
	Stage::init();

	return S_OK;
}

void HardStage::release()
{
}

void HardStage::update()
{
	Stage::update();
	CAMERAMANAGER->SetPos(_player->GetInfo().x, _player->GetInfo().y, 0, 100, 3);

	if (++_timer % 2 == 0)
	{
		_timer = 0;

		_background->_loopX -= 1;
	}
}

void HardStage::render()
{
	//뒷배경
	_background->_img->loopRender(getMapDC(), &CAMERAMANAGER->GetMapRect(), 0, 0);
	_background->_img->loopRender(getMinimapDC(), &CAMERAMANAGER->GetMapRect(), 0, 0);

	Stage::render();
}

void HardStage::SetbackGround()
{
	CAMERAMANAGER->SetMap(*this, 1280, 1280);

	//뒷 배경
	_background = new Background;
	_background->_img = IMGMANAGER->findImage("background7");

}

void HardStage::SetTerrain()
{
	//지형
	for (int i = 0; i < 8; i++)
	{
		Terrain* terrain = new Terrain;
		_vTerrain.push_back(terrain);
	}

	_vTerrain[0]->SetGround(5, 0, 1000, P_GROUND, GT_ROAD);
	_vTerrain[1]->SetGround(2, 100, 870, P_PLATFORM, GT_ROAD);
	_vTerrain[2]->SetGround(1, 300, 740, P_PLATFORM, GT_ROAD);
	_vTerrain[3]->SetGround(0, 150, 610, P_PLATFORM, GT_ROAD);
	_vTerrain[4]->SetGround(2, 500, 500, P_PLATFORM, GT_ROAD);
	_vTerrain[5]->SetGround(1, 400, 360, P_PLATFORM, GT_ROAD);
	_vTerrain[6]->SetGround(0, 700, 220, P_PLATFORM, GT_ROAD);
	_vTerrain[7]->SetGround(1, 600, 110, P_PLATFORM, GT_ROAD);
}

void HardStage::SetObject()
{
	//오브젝트
}

void HardStage::SetEnemy()
{
	for (int i = 0; i < 3; i++)
	{
		Enemy* firefly = new FireFly;
		_vEnemy.push_back(firefly);

		Enemy* turret = new Turret;
		_vEnemy.push_back(turret);
	}
	_vEnemy[0]->init(_player, this, _vTerrain[1]->getCollision().rc);
	_vEnemy[1]->init(_player, this, _vTerrain[4]->getCollision().rc);
	_vEnemy[2]->init(_player, this, _vTerrain[7]->getCollision().rc);

	_vEnemy[3]->init(_player, this, _vTerrain[2]->getCollision().rc);
	_vEnemy[4]->init(_player, this, _vTerrain[5]->getCollision().rc);
	_vEnemy[5]->init(_player, this, _vTerrain[6]->getCollision().rc);
}

void HardStage::SetBullet()
{
	//총알
	_cannon = new Cannon;
	_cannon->init("bullet1", 5, 500);
	_cannon->SetPlayerAddressLink(_player);
	_cannon->SetStageAddressLink(this);
}

void HardStage::SetItem()
{
	//아이템
	_item = new Item;
	_item->init();
	_item->SetPlayerAddressLink(_player);

	for (int j = 1; j < 8; j++)
	{
		for (int i = 0; i < (_vTerrain[j]->getCollision().rc.right - _vTerrain[j]->getCollision().rc.left) / 100; i++)
		{
			_item->make(_vTerrain[j]->getCollision().rc.left + 100 * i + 80, _vTerrain[j]->getCollision().rc.top - 30, I_CRYSTAL, true);
		}
	}
}

void HardStage::StartEvent()
{
}
