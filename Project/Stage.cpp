#include "stdafx.h"
#include "Stage.h"
#include "Enums.h"
#include "Player.h"


HRESULT Stage::init()
{
	_timer = 0;
	_itemTimer = 0;
	_stageTime = TIMEMANAGER->getWorldTime();
	_stageTimer = TIMEMANAGER->getWorldTime() - _stageTime;
	_isScene = false;

	_player->StageInit();

	SetbackGround();
	SetTerrain();
	SetObject();
	SetEnemy();
	SetBullet();
	SetItem();

	

	return S_OK;
}

void Stage::release()
{
	for (int i = 0; i < _vEnemy.size();)
	{
		SAFE_RELEASE(_vEnemy[i]);
		SAFE_DELETE(_vEnemy[i]);
		_vEnemy.erase(_vEnemy.begin() + i);
	}
	_cannon->release();
	_item->release();
}

void Stage::update()
{
	if (_vEnemy.empty()) _isClear = true;
	if(!_isClear) _stageTimer = TIMEMANAGER->getWorldTime() - _stageTime;

	//에너미
	for (int i = 0; i < _vEnemy.size();)
	{
		_vEnemy[i]->update();
		if (_vEnemy[i]->getIsDead())
		{
			SAFE_RELEASE(_vEnemy[i]);
			SAFE_DELETE(_vEnemy[i]);
			_vEnemy.erase(_vEnemy.begin() + i);
		}
		else i++;
	}
	//총알
	_cannon->update();
	_item->update();

	//아이템 랜덤 생성
	if (TIMEMANAGER->getWorldTime() - _itemTimer > RND->getFromFloatTo(5.0f, 10.0f))
	{
		_itemTimer = TIMEMANAGER->getWorldTime();
		int random = RND->getInt(2);
		if (random == 0) _item->make(_player->GetInfo().x + RND->getFromIntTo(300, 600), _player->GetInfo().y - RND->getFromIntTo(0, 100), (ITEMTYPE)RND->getInt(3), false);
		else _item->make(_player->GetInfo().x + RND->getFromIntTo(-600, -300), _player->GetInfo().y - RND->getFromIntTo(0, 100), (ITEMTYPE)RND->getInt(3), false);
	}

}

void Stage::render()
{
	//지형
	for (int i = 0; i < _vTerrain.size(); i++) _vTerrain[i]->render();

	//에너미
	for (int i = 0; i < _vEnemy.size(); i++) _vEnemy[i]->render();

	//오브젝트
	for (int i = 0; i < _vObject.size(); i++)
	{
		_vObject[i]->_img->frameRender(getMapDC(), _vObject[i]->_pos.x + -(_player->GetInfo().x- _vObject[i]->_pos.x) / 8,
			_vObject[i]->_pos.y, _vObject[i]->_indexX, 0);
	}

	//총알
	_cannon->render();

	//아이템
	_item->render();


}
