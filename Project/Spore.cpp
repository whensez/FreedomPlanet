#include "stdafx.h"
#include "Spore.h"
#include "Player.h"

#include "EnemyIdle.h"
#include "EnemyPatrol.h"
#include "EnemyAttack.h"
#include "EnemyDamage.h"
#include "EnemyDie.h"

HRESULT Spore::init(Player * player, Stage * stage, RECT rc)
{

	Enemy::init();

	//이미지 추가
	_imgIdle = IMGMANAGER->addFrameImage("spore_idle", "image/enemy_spore_idle.bmp", 384, 224, 4, 2, true, MAGENTA, true);
	_imgPatrol = IMGMANAGER->addFrameImage("spore_idle", "image/enemy_spore_idle.bmp", 384, 224, 4, 2, true, MAGENTA, true);
	_imgAttack = IMGMANAGER->addFrameImage("spore_attack", "image/enemy_spore_attack.bmp", 480, 224, 5, 2, true, MAGENTA, true);
	_imgDamage = IMGMANAGER->addFrameImage("spore_damage", "image/enemy_spore_damage.bmp", 384, 204, 4, 2, true, MAGENTA, true);
	_imgDie = IMGMANAGER->addFrameImage("spore_die", "image/enemy_spore_die.bmp", 384, 204, 4, 2, true, MAGENTA, true);

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

	//초기 설정
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
	_attckInterval = 4.0f;

	_jumpTimer = 0;

	return S_OK;
}

void Spore::release()
{
}

void Spore::update()
{
	Enemy::update();

	if((TIMEMANAGER->getWorldTime() - _jumpTimer > 1.0f) && _jumpPower <= 0)
	{
		_jumpTimer = TIMEMANAGER->getWorldTime();
		_jumpPower = 3;
		_position = P_AIR;
	}
}

void Spore::render()
{
	Enemy::render();

}

void Spore::attack()
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

void Spore::rcMake()
{
	_rcDamage = RectMakeUp(_x, _y + _img->getFrameHeight() / 2, _img->getFrameWidth(), _img->getFrameHeight());		//피격 범위 렉트
	_rcAttack = RectMakeUp(_x, _y + _img->getFrameHeight(), _img->getFrameWidth()*1.2, _img->getFrameHeight()*2);		//공격 범위 렉트
	_rcSense = RectMakeUp(_x, _y + _img->getFrameHeight(), _img->getFrameWidth() * 4, _img->getFrameHeight() * 2);	//감지 범위 렉트
	_rcRange = RectMakeUp((_rcTerrain.right + _rcTerrain.left) / 2, _rcTerrain.top,
		(_rcTerrain.right - _rcTerrain.left) - 50, _img->getFrameHeight() * 2);			//이동 범위 렉트
}
