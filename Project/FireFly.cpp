#include "stdafx.h"
#include "FireFly.h"

#include "Player.h"

#include "EnemyIdle.h"
#include "EnemyPatrol.h"
#include "EnemyAttack.h"
#include "EnemyDamage.h"
#include "EnemyDie.h"

HRESULT FireFly::init(Player * player, Stage * stage, RECT rc)
{
	Enemy::init();

	//이미지 추가
	_imgIdle =	 IMGMANAGER->addFrameImage("firefly_idle", "image/enemy_firefly_idle.bmp", 288, 160, 3, 2, true, MAGENTA, true);
	_imgPatrol = IMGMANAGER->addFrameImage("firefly_patrol", "image/enemy_firefly_patrol.bmp", 288, 160, 3, 2, true, MAGENTA, true);
	_imgAttack = IMGMANAGER->addFrameImage("firefly_attack", "image/enemy_firefly_attack.bmp", 336, 160, 3, 2, true, MAGENTA, true);
	_imgDamage = IMGMANAGER->addFrameImage("firefly_damage", "image/enemy_firefly_damage.bmp", 192, 160, 2, 2, true, MAGENTA, true);
	_imgDie =	 IMGMANAGER->addFrameImage("firefly_die", "image/enemy_firefly_die.bmp", 192, 160, 2, 2, true, MAGENTA, true);

	//연결
	_player = player;
	_stage = stage;

	//상태
	SetState(MS_IDLE);
	_isDead = false;
	_goRight = (bool)RND->getInt(2);
	_dest = D_LEFT;
	_position = P_AIR;
	_originSpeed = _speed = 2;
	_jumpPower = 0;
	_alpha = 255;

	//위치
	_rcTerrain = rc;
	_x = _xInit = (_rcTerrain.right + _rcTerrain.left) / 2;
	_y = _yInit = _rcTerrain.top - _img->getFrameHeight() / 2-100;
	rcMake();
	_x += RND->getFromIntTo(-(_rcRange.right - _rcRange.left) / 2, (_rcRange.right - _rcRange.left) / 2);

	

	//이미지
	_imageXIndex = _imageYIndex = 0;
	_redrawTimer = 0;

	//스텟
	_maxLife = 40;
	_life = _maxLife;
	_attack = 1;
	_attckCool = 0;
	_attckInterval = 1.0f;

	//각도
	_angle = 0;

	return S_OK;
}

void FireFly::release()
{
}

void FireFly::update()
{
	_EnemyState->UpdateState();
	imageRedraw();
	rcMake();

	RECT tempRc;

	if (_life <= 0) SetState(MS_DIE);
	else if (IntersectRect(&tempRc, &_rcDamage, &_player->GetAttackRect())) SetState(MS_DAMAGE);
	else if (IntersectRect(&tempRc, &_rcAttack, &_player->GetRect()) &&
		TIMEMANAGER->getWorldTime() - _attckCool > _attckInterval)
	{
		SetState(MS_ATTACK);
	}
	else if (IntersectRect(&tempRc, &_rcSense, &_player->GetRect())) SetState(MS_PATROL);
	else SetState(MS_IDLE);

	_angle += 0.04f;
	xyMove(0, sinf(_angle)*_originSpeed);


	//플래이어가 있는 방향으로 다가간다.
	if(_state!=MS_IDLE&&abs(_player->GetInfo().y - _y)>50)
		xyMove(0, -sinf(getAngle(0, _y, 0, _player->GetInfo().y))*_speed);


}

void FireFly::render()
{
	Enemy::render();
}

void FireFly::attack()
{
	if (_dest == D_RIGHT && _imageXIndex == _img->getMaxFrameX())
	{
		Enemy::attack();
		_attckCool = TIMEMANAGER->getWorldTime();
	}
	else if (_dest == D_LEFT && _imageXIndex == 0)
	{
		Enemy::attack();
		_attckCool = TIMEMANAGER->getWorldTime();
	}
}


void FireFly::rcMake()
{
	_rcDamage = RectMakeUp(_x, _y + _img->getFrameHeight() / 2, _img->getFrameWidth(), _img->getFrameHeight());		//피격 범위 렉트
	_rcAttack = RectMakeUp(_x, _y + _img->getFrameHeight() / 2, _img->getFrameWidth()*1.2, _img->getFrameHeight()*2);		//공격 범위 렉트
	_rcSense = RectMakeCenter(_x, _y , _img->getFrameWidth() * 5, _img->getFrameHeight() * 5);					//감지 범위 렉트
	_rcRange = RectMakeUp((_rcTerrain.right + _rcTerrain.left) / 2, _rcTerrain.top, (_rcTerrain.right - _rcTerrain.left) - 50, _img->getFrameHeight() * 2);
}
