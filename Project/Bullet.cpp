#include "stdafx.h"
#include "Bullet.h"
#include "Enums.h"
#include "Player.h"
#include "Stage.h"

HRESULT Cannon::init(const char* imageName, int bulletMax, float range)
{
	_imgName = imageName;
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void Cannon::release()
{
	for (int i = 0; i < _vCannon.size(); i++) Erase(i);
}

void Cannon::update()
{
	Move();
	Collision();
}

void Cannon::render()
{
	for (int i = 0; i < _vCannon.size(); i++) _vCannon[i]->_img->render(getMapDC(), _vCannon[i]->_x, _vCannon[i]->_y);
}

void Cannon::Fire(int x, int y, int goalX, int goalY, float speed)
{
	tagBullet* bullet = new tagBullet;

	bullet->_img = IMGMANAGER->findImage(_imgName);
	bullet->_speed = speed;
	bullet->_radius = bullet->_img->getWidth() / 2;
	bullet->_x = bullet->_fireX = x;
	bullet->_y = bullet->_fireY = y;
	bullet->_angle = getAngle(x, y, goalX, goalY);
	bullet->_gravity = 0;
	bullet->_rc = RectMakeCenter(bullet->_x, bullet->_y, bullet->_img->getWidth(), bullet->_img->getHeight());

	_vCannon.push_back(bullet);
}

void Cannon::Move()
{
	for (int i = 0; i < _vCannon.size(); i++)
	{
		_vCannon[i]->_gravity += GRAVITY*3;
		_vCannon[i]->_x += cosf(_vCannon[i]->_angle) * _vCannon[i]->_speed;
		_vCannon[i]->_y += -sinf(_vCannon[i]->_angle) * _vCannon[i]->_speed + _vCannon[i]->_gravity;
		_vCannon[i]->_rc = RectMakeCenter(_vCannon[i]->_x, _vCannon[i]->_y, _vCannon[i]->_img->getWidth(), _vCannon[i]->_img->getHeight());
		
		if (_range < getDistance(_vCannon[i]->_x, _vCannon[i]->_y, _vCannon[i]->_fireX, _vCannon[i]->_fireY)) Erase(i);
		else i++;
	}
}

void Cannon::Collision()
{
	RECT temp;
	//플래이어와 충돌
	for (int i = 0; i < _vCannon.size();)
	{
		if (_player->GetInfo().isImmune || _player->GetInfo().state == PS_ROLL) break;
		if (IntersectRect(&temp, &_vCannon[i]->_rc, &_player->GetRect()))
		{
			if (_player->GetRect().right < _vCannon[i]->_rc.right) _player->Damage(1, D_RIGHT, 4);
			else _player->Damage(1, D_LEFT, 4);
			EFFECTMANAGER->play("bomb", _vCannon[i]->_x, _vCannon[i]->_y);
			Erase(i);
		}
		else i++;
	}

	//땅의 윗부분과 충돌
	for (int j = 0; j < _stage->getvTerrain().size(); j++)
	{
		for (int i = 0; i < _vCannon.size();)
		{
			if (IntersectRect(&temp, &_vCannon[i]->_rc, &_stage->getvTerrain()[j]->getCollision().rc)
				&& temp.top == _stage->getvTerrain()[j]->getCollision().rc.top)
			{
				EFFECTMANAGER->play("bomb", _vCannon[i]->_x, _vCannon[i]->_y);
				Erase(i);
			}
			else i++;
		}
	}
}

void Cannon::Erase(int num)
{
	SAFE_DELETE(_vCannon[num]);
	_vCannon.erase(_vCannon.begin() + num);
}
