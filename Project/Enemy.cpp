#include "stdafx.h"
#include "Enemy.h"
#include "Enums.h"
#include "Stage.h"
#include "Player.h"
#include "Item.h"

#include "EnemyIdle.h"
#include "EnemyPatrol.h"
#include "EnemyAttack.h"
#include "EnemyDamage.h"
#include "EnemyDie.h"


HRESULT Enemy::init()
{
	_ES_attack = new EnemyAttack;
	_ES_damage = new EnemyDamage;
	_ES_die = new EnemyDie;
	_ES_idle = new EnemyIdle;
	_ES_patrol = new EnemyPatrol;
	_EnemyState = NULL;

	return S_OK;
}

HRESULT Enemy::init(Player* player, Stage* stage, RECT rc)
{
	return S_OK;
}

HRESULT Enemy::init(Player * player, Stage * stage, int x, int y)
{
	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{
	xyMove(0, -_jumpPower);
	if (_position == P_AIR) _jumpPower -= GRAVITY;

	TerrainStand();
	imageRedraw();
	rcMake();

	RECT tempRc;

	if (_life <= 0) SetState(MS_DIE);
	else if (IntersectRect(&tempRc, &_rcDamage, &_player->GetAttackRect())) SetState(MS_DAMAGE);
	else if (IntersectRect(&tempRc, &_rcAttack, &_player->GetRect()) &&
		TIMEMANAGER->getWorldTime() - _attckCool > _attckInterval) SetState(MS_ATTACK);
	else if (IntersectRect(&tempRc, &_rcSense, &_player->GetRect())) SetState(MS_PATROL);
	else SetState(MS_IDLE);

	_EnemyState->UpdateState();

}

void Enemy::render()
{
	//디버깅용 맵 렉트
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMapDC(), _rcDamage);
	}

	//이미지
	_img->alphaFrameRender(getMapDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _imageXIndex, _imageYIndex, _alpha);

	UIMANAGER->ProgressBarRender(getMapDC(), IMGMANAGER->findImage("ui_HPBar0"), _x, _y + _img->getFrameHeight() / 2 + 10, _life, _maxLife);

	//채색
	HPEN _hpen = CreatePen(PS_SOLID, 15, RGB(40, 10, 10));
	HPEN _hpenOld = (HPEN)SelectObject(getMinimapDC(), (HGDIOBJ)_hpen);
	HBRUSH _hbr = CreateSolidBrush(RGB(200, 50, 100));
	HBRUSH _hbrOld = (HBRUSH)SelectObject(getMinimapDC(), _hbr);

	//미니맵 렉트
	Ellipse(getMinimapDC(), _rcDamage);

	//삭제
	_hpen = (HPEN)SelectObject(getMinimapDC(), _hpenOld);
	DeleteObject(_hpen);
	_hbr = (HBRUSH)SelectObject(getMinimapDC(), _hbrOld);
	DeleteObject(_hbr);
}

void Enemy::xyMove(int x, int y)
{
	_x += x;
	_y += y;
	rcMake();
}

void Enemy::jump(float jump)
{
	if (_position == P_AIR) return;
	_jumpPower = jump;
	_position = P_AIR;

}

void Enemy::attack()
{
	RECT tempRc;
	if (IntersectRect(&tempRc, &_rcAttack, &_player->GetRect()))
	{
		if (_x < _player->GetInfo().x)  _player->Damage(_attack, D_LEFT, 4);
		else _player->Damage(_attack, D_RIGHT, 4);
	}
}

void Enemy::die()
{

	if (_dest == D_RIGHT && _imageXIndex == _img->getMaxFrameX())
	{
		_alpha -= 10;
		if (_alpha <= 0)
		{
			_stage->getItem()->make(_x, _y, (ITEMTYPE)RND->getInt(3), false);
			_isDead = true;
		}
	}
	else if (_dest == D_LEFT && _imageXIndex == 0)
	{
		_alpha -= 10;
		if (_alpha <= 0)
		{
			_stage->getItem()->make(_x, _y, (ITEMTYPE)RND->getInt(3), false);
			_isDead = true;
		}
	}

}

bool Enemy::UDCollision(tagCollision & col)
{
	if (IntersectRect(&col.tempRc, &col.rc, &_rcDamage))
	{
		if (col.tempRc.right - col.tempRc.left > col.tempRc.bottom - col.tempRc.top
			&& (_rcDamage.bottom > col.rc.bottom || _rcDamage.top < col.rc.top)) return true;
	}
	return false;
}

bool Enemy::LRCollision(tagCollision & col)
{
	if (IntersectRect(&col.tempRc, &col.rc, &_rcDamage))
	{
		if (col.tempRc.right - col.tempRc.left < col.tempRc.bottom - col.tempRc.top
			&& (_rcDamage.right > col.rc.right || _rcDamage.left < col.rc.left)) return true;
	}
	return false;
}

bool Enemy::Collision(tagCollision & col)
{
	if (IntersectRect(&col.tempRc, &col.rc, &_rcDamage)) return false;
}

void Enemy::TerrainStand()
{
	// ============================ 땅에 서 있는다. ============================
	for (int i = 0; i < _stage->getvTerrain().size(); i++)
	{
		if (_stage->getvTerrain()[i]->getPosition() == P_CLIFF) continue;

		//땅에서 좌우로 떨어지면 공중이다.
		if (_y == (_stage->getvTerrain())[i]->getCollision().rc.top - 1 - (_rcDamage.bottom - _rcDamage.top) / 2 &&
			(_x > (_stage->getvTerrain())[i]->getCollision().rc.right || _x < (_stage->getvTerrain())[i]->getCollision().rc.left)
			&& (_x < (_stage->getvTerrain())[i]->getCollision().rc.right + (_rcDamage.right - _rcDamage.left) && _x >(_stage->getvTerrain())[i]->getCollision().rc.left - (_rcDamage.right - _rcDamage.left)))
			_position = P_AIR;

		//땅과 충돌한다.
		if (UDCollision((_stage->getvTerrain())[i]->getCollision()) && _jumpPower <= 0
			(_rcDamage.bottom < (_stage->getvTerrain())[i]->getCollision().rc.top + 10 || _jumpPower < -7 * 1.5)
			&& (_x < (_stage->getvTerrain())[i]->getCollision().rc.right && _x >(_stage->getvTerrain())[i]->getCollision().rc.left)
			&& _rcDamage.top < (_stage->getvTerrain())[i]->getCollision().rc.top
			&& (_stage->getvTerrain())[i]->getCollision().rc.bottom > _rcDamage.bottom)
		{
			xyMove(0, -((_stage->getvTerrain())[i]->getCollision().tempRc.bottom - (_stage->getvTerrain())[i]->getCollision().tempRc.top));
			_y = (_stage->getvTerrain())[i]->getCollision().rc.top - (_rcDamage.bottom - _rcDamage.top) / 2;	//위치 보정

			if (_y == (_stage->getvTerrain())[i]->getCollision().rc.top - (_rcDamage.bottom - _rcDamage.top) / 2)
			{
				_jumpPower = 0;		//점프력 0
				_position = (_stage->getvTerrain())[i]->getPosition();	//위치 설정
				SetState(MS_IDLE);	//상태 설정
				_y = (_stage->getvTerrain())[i]->getCollision().rc.top - 1 - (_rcDamage.bottom - _rcDamage.top) / 2;	//위치 완전 보정
			}
		}
	}
}

void Enemy::SetState(MS_STATE state)
{
	if (_state != NULL && _state == state) return;
	_state = state;
	if (_EnemyState != NULL) _EnemyState->ExitState();

	switch (_state)
	{
	case MS_IDLE:
		_EnemyState = _ES_idle;
		break;
	case MS_PATROL:
		_EnemyState = _ES_patrol;
		break;

	case MS_ATTACK:
		_EnemyState = _ES_attack;
		break;
	case MS_DAMAGE:
		_EnemyState = _ES_damage;
		break;
	case MS_DIE:
		_EnemyState = _ES_die;
		break;
	default:
		break;
	}
	_EnemyState->LinkEnemyAddress(this);
	_EnemyState->EnterState();

}

void Enemy::imageRedraw()
{
	if (TIMEMANAGER->getWorldTime() - _redrawTimer > 0.1f)
	{
		_redrawTimer = TIMEMANAGER->getWorldTime();
		switch (_state)
		{
		case MS_IDLE:
		case MS_PATROL:
			FramePlay(0);
			break;
		case MS_ATTACK:
			FramePlay(-1);
			break;
		case MS_DAMAGE:
			FramePlay(0);
			break;
		case MS_DIE:
			FramePlay(1);
			break;
		}
	}
}

void Enemy::FramePlay(int count)
{
	_imageYIndex = _dest;

	switch (_dest)
	{
	case D_RIGHT:
		_imageXIndex++;
		break;
	case D_LEFT:
		_imageXIndex--;
		break;
	}

	switch (count)
	{
	case -1:	//한 번 재생 후 이전 재생
		if (_dest == D_RIGHT && _imageXIndex > _img->getMaxFrameX())
		{
			if (_state == MS_ATTACK) _attckCool = TIMEMANAGER->getWorldTime();
			SetState(MS_IDLE);
		}
		else if (_dest == D_LEFT && _imageXIndex < 0)
		{
			if (_state == MS_ATTACK) _attckCool = TIMEMANAGER->getWorldTime();
			SetState(MS_IDLE);
		}
		break;
	case 1:		//한 번만 재생
		if (_dest == D_RIGHT && _imageXIndex > _img->getMaxFrameX())
		{
			_imageXIndex = _img->getMaxFrameX();
		}
		else if (_dest == D_LEFT && _imageXIndex < 0)
		{
			_imageXIndex = 0;
		}
		break;
	case 0:		//무한 재생
		if (_dest == D_RIGHT && _imageXIndex >= _img->getMaxFrameX()) _imageXIndex = 0;
		else if (_dest == D_LEFT && _imageXIndex <= 0) _imageXIndex = _img->getMaxFrameX();
		break;
	}

}

void Enemy::SetImage()
{
	switch (_state)
	{
		case MS_IDLE:	
			if (_img == _imgIdle) return;
			_img = _imgIdle;
			break;
		case MS_PATROL: 
			if (_img == _imgPatrol) return;
			_img = _imgPatrol;
			break;
		case MS_ATTACK: 
			if (_img == _imgAttack) return;
			_img = _imgAttack;
			break;
		case MS_DAMAGE: 
			if (_img == _imgDamage) return;
			_img = _imgDamage;
			break;
		case MS_DIE:	
			if (_img == _imgDie) return;
			_img = _imgDie;
			break;
		default: break;
	}
														//이미지를 설정한다.
	if (_dest == D_RIGHT) _imageXIndex = 0;							//오른쪽 방향이면 0번 인덱스
	else if (_dest == D_LEFT) _imageXIndex = _img->getMaxFrameX();	//왼쪽 방향이면 마지막 인덱스
}