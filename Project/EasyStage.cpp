#include "stdafx.h"
#include "EasyStage.h"
#include "Player.h"
#include "Enums.h"


HRESULT EasyStage::init()
{
	Stage::init();
	//_isScene = true;
	return S_OK;
}

void EasyStage::release()
{
	Stage::release();
}

void EasyStage::update()
{
	Stage::update();
	
	if (++_timer % 3 == 0)
	{
		_timer = 0;
		_background->_loopX -= 1;
	}
	
	//중간 배경
	_vMiddleGround[0]->_rc = RectMake(0, CAMERAMANAGER->GetY() + WINSIZEY / 2 - _vMiddleGround[0]->_img->getHeight(), CAMERAMANAGER->GetMapXSize(), _vMiddleGround[0]->_img->getHeight());
	_vMiddleGround[1]->_rc = RectMake(0, CAMERAMANAGER->GetY() - WINSIZEY / 2 - 100, CAMERAMANAGER->GetMapXSize(), _vMiddleGround[1]->_img->getHeight());

	if(_isScene) StartEvent();
	else CAMERAMANAGER->SetPos(_player->GetInfo().x, _player->GetInfo().y, 0, 100, 3);
}

void EasyStage::render()
{
	//뒷 배경
	_background->_img->loopRender(getMapDC(), &CAMERAMANAGER->GetMapRect(), _background->_loopX, 0);
	_background->_img->loopRender(getMinimapDC(), &CAMERAMANAGER->GetMapRect(), 0, 0);

	//중간 배경
	_vMiddleGround[0]->_img->loopRender(getMapDC(), &_vMiddleGround[0]->_rc, _player->GetInfo().x / 3, 0);
	_vMiddleGround[1]->_img->loopRender(getMapDC(), &_vMiddleGround[1]->_rc, _player->GetInfo().x / 5, 0);

	Stage::render();
}

void EasyStage::SetbackGround()
{
	CAMERAMANAGER->SetMap(*this, 4000, 900);

	//뒷 배경
	_background = new Background;
	_background->_img = IMGMANAGER->findImage("background2");

	//중간 배경
	for (int i = 0; i < 2; i++)
	{
		Middleground* _middleground = new Middleground;
		_vMiddleGround.push_back(_middleground);
	}
	_vMiddleGround[0]->_img = IMGMANAGER->findImage("middleground5");
	_vMiddleGround[1]->_img = IMGMANAGER->findImage("middleground2");
}

void EasyStage::SetTerrain()
{
	//지형
	for (int i = 0; i < 13; i++)
	{
		Terrain* terrain = new Terrain;
		_vTerrain.push_back(terrain);
	}

	_vTerrain[0]->SetGround(10, 0, 720, P_GROUND, GT_GRASS);
	_vTerrain[1]->SetGround(0, 100, 610, P_PLATFORM, GT_GRASS);
	_vTerrain[2]->SetGround(0, 200, 480, P_PLATFORM, GT_GRASS);
	_vTerrain[3]->SetGround(1, 520, 520, P_PLATFORM, GT_GROUND);
	_vTerrain[4]->SetGround(2, 1000, 360, P_PLATFORM, GT_GRASS);
	_vTerrain[5]->SetGround(1, 1200, 600, P_PLATFORM, GT_GROUND);
	_vTerrain[6]->SetGround(3, 1800, 470, P_PLATFORM, GT_GRASS);
	_vTerrain[7]->SetGround(0, 2500, 600, P_PLATFORM, GT_GRASS);
	_vTerrain[8]->SetGround(0, 3100, 350, P_PLATFORM, GT_GROUND);
	_vTerrain[9]->SetGround(1, 3200, 600, P_PLATFORM, GT_GRASS);
	_vTerrain[10]->SetGround(1, 3400, 380, P_PLATFORM, GT_GROUND);
	_vTerrain[11]->SetGround(1, 2300, 220, P_PLATFORM, GT_GROUND);
	_vTerrain[12]->SetGround(0, 2800, 320, P_PLATFORM, GT_GROUND);
}

void EasyStage::SetObject()
{
	//오브젝트
	for (int i = 0; i < 10; i++)
	{
		Object* object = new Object;
		_vObject.push_back(object);
	}
	_vObject[0]->SetObject(520, 170, OT_CLOUD);
	_vObject[1]->SetObject(1100, 100, OT_CLOUD);
	_vObject[2]->SetObject(1620, 220, OT_CLOUD);
	_vObject[3]->SetObject(2200, 120, OT_CLOUD);
	_vObject[4]->SetObject(2800, 50, OT_CLOUD);
	_vObject[5]->SetObject(300, 650, OT_TREE1);
	_vObject[6]->SetObject(900, 600, OT_TREE2);
	_vObject[7]->SetObject(1500, 650, OT_TREE3);
	_vObject[8]->SetObject(2100, 650, OT_TREE1);
	_vObject[9]->SetObject(2700, 600, OT_TREE2);

}

void EasyStage::SetEnemy()
{
	//에너미
	for (int i = 0; i < 4; i++)
	{
		Enemy* hog = new Hog;
		_vEnemy.push_back(hog);

		Enemy* turret = new Turret;
		_vEnemy.push_back(turret);
	}

	_vEnemy[0]->init(_player, this, _vTerrain[0]->getCollision().rc);
	_vEnemy[1]->init(_player, this, _vTerrain[3]->getCollision().rc);
	_vEnemy[2]->init(_player, this, _vTerrain[5]->getCollision().rc);
	_vEnemy[3]->init(_player, this, _vTerrain[6]->getCollision().rc);

	_vEnemy[4]->init(_player, this, _vTerrain[0]->getCollision().rc);
	_vEnemy[5]->init(_player, this, _vTerrain[4]->getCollision().rc);
	_vEnemy[6]->init(_player, this, _vTerrain[6]->getCollision().rc);
	_vEnemy[7]->init(_player, this, _vTerrain[9]->getCollision().rc);

}

void EasyStage::SetBullet()
{
	//총알
	_cannon = new Cannon;
	_cannon->init("bullet1", 5, 500);
	_cannon->SetPlayerAddressLink(_player);
	_cannon->SetStageAddressLink(this);
}

void EasyStage::SetItem()
{
	//아이템
	_item = new Item;
	_item->init();
	_item->SetPlayerAddressLink(_player);

	for (int j = 1; j < 12; j++)
	{
		for (int i = 0; i < (_vTerrain[j]->getCollision().rc.right - _vTerrain[j]->getCollision().rc.left) / 100; i++)
		{
			_item->make(_vTerrain[j]->getCollision().rc.left + 100 * i + 80, _vTerrain[j]->getCollision().rc.top - 30, I_CRYSTAL, true);
		}
	}
}

void EasyStage::StartEvent()
{
	//카메라 이동 이벤트
	if (_stageTimer > 14.0f)
	{
		CAMERAMANAGER->SetPos(_player->GetInfo().x, _player->GetInfo().y, 0, 100, 3);
		CAMERAMANAGER->ActiveMinimap(true);
		UIMANAGER->SetIsActive(true);
		_player->SetControl(true);
		_isScene = false;
		_stageTime = TIMEMANAGER->getWorldTime();
	}
	else if (_stageTimer > 13.0f)
	{
		CAMERAMANAGER->SetPos(_player->GetInfo().x, _player->GetInfo().y, 0, 0, 0.5f);
	}
	else if (_stageTimer > 12.0f)
	{
		CAMERAMANAGER->SetPos(_player->GetInfo().x, _player->GetInfo().y, 0, 0, 3);
		CAMERAMANAGER->SetMagnification(1.0, 0.01);
	}
	else if (_stageTimer > 7.0f)
	{
		CAMERAMANAGER->SetPos(CAMERAMANAGER->GetMapXSize(), _player->GetInfo().y, 0, 0, 0.01);
	}
	else if (_stageTimer > 5.0f)
	{
		CAMERAMANAGER->SetPos(0, _player->GetInfo().y, 0, 0, 0.1f);
		CAMERAMANAGER->SetMagnification(1.2, 0.01);
	}
	else if (_stageTimer > 0.3f)
	{
		CAMERAMANAGER->SetPos(0, _player->GetInfo().y, 0, 0, 0.001f);
	}
	else
	{
		CAMERAMANAGER->SetPos(CAMERAMANAGER->GetMapXSize(), CAMERAMANAGER->GetMapYSize());
		UIMANAGER->SetIsActive(false);
		CAMERAMANAGER->ActiveMinimap(false);
		_player->SetControl(false);
	}

}
