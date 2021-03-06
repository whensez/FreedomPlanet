#include "stdafx.h"
#include "Turret.h"
#include "Player.h"
#include "Stage.h"

#include "EnemyIdle.h"
#include "EnemyPatrol.h"
#include "EnemyAttack.h"
#include "EnemyDamage.h"
#include "EnemyDie.h"

#include "Bullet.h"


HRESULT Turret::init(Player* player, Stage* stage, RECT rc)
{
	Enemy::init();

	//이미지
	_imgIdle =	 IMGMANAGER->addFrameImage("turret_idle", "image/enemy_turret_idle.bmp", 768, 200, 8, 2, true, MAGENTA, true);
	_imgPatrol = IMGMANAGER->addFrameImage("turret_idle", "image/enemy_turret_idle.bmp", 768, 200, 8, 2, true, MAGENTA, true);
	_imgAttack = IMGMANAGER->addFrameImage("turret_attack", "image/enemy_turret_attack.bmp", 1008, 200, 9, 2, true, MAGENTA, true);
	_imgDamage = IMGMANAGER->addFrameImage("turret_damage", "image/enemy_turret_damage.bmp", 530, 200, 5, 2, true, MAGENTA, true);
	_imgDie =	 IMGMANAGER->addFrameImage("turret_die", "image/enemy_turret_die.bmp", 530, 200, 5, 2, true, MAGENTA, true);

	//연결
	_player = player;
	_stage = stage;

	//상태
	SetState(MS_IDLE);
	_isDead = false;
	_goRight = (bool)RND->getInt(2);
	_dest = D_LEFT;
	_position = P_AIR;
	_originSpeed = _speed = 1;
	_jumpPower = 0;
	_alpha = 255;

	//위치
	_rcTerrain = rc;
	_x = _xInit = (_rcTerrain.right + _rcTerrain.left) / 2;
	_y = _yInit = _rcTerrain.top - _img->getFrameHeight() / 2;
	rcMake();
	_x += RND->getFromIntTo(-(_rcRange.right - _rcRange.left) / 2, (_rcRange.right - _rcRange.left) / 2);

	

	//이미지
	_imageXIndex = _imageYIndex = 0;
	_redrawTimer = 0;

	//스텟
	_maxLife = 50;
	_life = _maxLife;
	_attack = 1;
	_attckCool = 0;
	_attckInterval = 3.f;

	return S_OK;
}

void Turret::release()
{
}

void Turret::update()
{
	Enemy::update();
}

void Turret::render()
{
	Enemy::render();
}



void Turret::rcMake()
{
	_rcDamage = RectMakeUp(_x, _y + _img->getFrameHeight() / 2, _img->getFrameWidth(), _img->getFrameHeight());			//피격 범위 렉트
	_rcAttack = RectMakeUp(_x, _y + _img->getFrameHeight() / 2, _img->getFrameWidth() * 4, _img->getFrameHeight() * 1.5);		//공격 범위 렉트
	_rcSense = RectMakeUp(_x, _y + _img->getFrameHeight() / 2, _img->getFrameWidth()*6, _img->getFrameHeight() * 1.5);		//감지 범위 렉트
	_rcRange = RectMakeUp((_rcTerrain.right + _rcTerrain.left) / 2 , _rcTerrain.top,
		(_rcTerrain.right - _rcTerrain.left)-50 , _img->getFrameHeight() * 2);			//이동 범위 렉트

}

void Turret::attack()
{
	if (_dest == D_RIGHT)
	{
		if (_imageXIndex == 6)
		{
			if (_isAttack) return;
			_stage->getBullet()->Fire(_x + 30, _y - 40, _player->GetInfo().x, _player->GetInfo().y - 100, 10);
			_isAttack = true;
		}
		else if (_imageXIndex == _img->getMaxFrameX()) _attckCool = TIMEMANAGER->getWorldTime();
	}

	else if (_dest == D_LEFT)
	{
		if (_imageXIndex == 2)
		{
			if (_isAttack) return;
			_stage->getBullet()->Fire(_x - 30, _y - 40, _player->GetInfo().x, _player->GetInfo().y - 100, 10);
			_isAttack = true;
		}
		else if (_imageXIndex == 0)_attckCool = TIMEMANAGER->getWorldTime();
	}
}
