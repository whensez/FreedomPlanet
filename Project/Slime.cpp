#include "stdafx.h"
#include "Slime.h"
#include "Player.h"

#include "EnemyIdle.h"
#include "EnemyPatrol.h"
#include "EnemyAttack.h"
#include "EnemyDamage.h"
#include "EnemyDie.h"

HRESULT Slime::init(Player * player, Stage * stage, RECT rc)
{
	Enemy::init();

	//�̹��� �߰�
	_imgIdle = IMGMANAGER->addFrameImage("slime_idle", "image/enemy_slime_idle.bmp", 960, 160, 10, 2, true, MAGENTA, true);
	_imgPatrol = IMGMANAGER->addFrameImage("slime_patrol", "image/enemy_slime_patrol.bmp", 512, 160, 5, 2, true, MAGENTA, true);
	_imgAttack = IMGMANAGER->addFrameImage("slime_attack", "image/enemy_slime_attack.bmp", 288, 160, 3, 2, true, MAGENTA, true);
	_imgDamage = IMGMANAGER->addFrameImage("slime_damage", "image/enemy_slime_damage.bmp", 512, 160, 5, 2, true, MAGENTA, true);
	_imgDie = IMGMANAGER->addFrameImage("slime_die", "image/enemy_slime_die.bmp", 288, 160, 3, 2, true, MAGENTA, true);

	//����
	_player = player;
	_stage = stage;

	//����
	SetState(MS_IDLE);
	_isDead = false;
	_goRight = (bool)RND->getInt(2);
	_dest = D_LEFT;
	_position = P_AIR;
	_originSpeed = _speed = 1;
	_jumpPower = 0;
	_alpha = 255;

	//��ġ
	_rcTerrain = rc;
	_x = _xInit = (_rcTerrain.right + _rcTerrain.left) / 2;
	_y = _yInit = _rcTerrain.top - _img->getFrameHeight() / 2;
	rcMake();
	_x += RND->getFromIntTo(-(_rcRange.right - _rcRange.left) / 2, (_rcRange.right - _rcRange.left) / 2);

	

	//�̹���
	_imageXIndex = _imageYIndex = 0;
	_redrawTimer = 0;

	//����
	_maxLife = 20;
	_life = _maxLife;
	_attack = 2;
	_attckCool = 0;
	_attckInterval = 1.0f;

	return S_OK;
}

void Slime::release()
{
}

void Slime::update()
{
	Enemy::update();
}

void Slime::render()
{
	Enemy::render();
}

void Slime::attack()
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

void Slime::rcMake()
{
	_rcDamage = RectMakeUp(_x, _y + _img->getFrameHeight() / 2, _img->getFrameWidth(), _img->getFrameHeight());		//�ǰ� ���� ��Ʈ
	_rcAttack = RectMakeUp(_x, _y + _img->getFrameHeight() / 2, _img->getFrameWidth()*1.2, _img->getFrameHeight());		//���� ���� ��Ʈ
	_rcSense = RectMakeUp(_x, _y + _img->getFrameHeight() / 2, _img->getFrameWidth() * 4, _img->getFrameHeight() * 1.5);	//���� ���� ��Ʈ
	_rcRange = RectMakeUp((_rcTerrain.right + _rcTerrain.left) / 2, _rcTerrain.top,
		(_rcTerrain.right - _rcTerrain.left) - 50, _img->getFrameHeight() * 2);
}
