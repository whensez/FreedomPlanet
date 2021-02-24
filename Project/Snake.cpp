#include "stdafx.h"
#include "Snake.h"
#include "Player.h"
// ================== 디버그 용 ==================
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
// ================== 디버그 용 ==================

HRESULT Snake::init(Player * player, Stage * stage, int x, int y)
{
	Enemy::init();

	//이미지 추가
	IMGMANAGER->addFrameImage("snake_head2", "image/enemy_snake_head2.bmp", 1344, 336, 8, 2, true, MAGENTA, true);
	IMGMANAGER->addImage("snake_body2", "image/enemy_snake_body2.bmp", 168, 168, true, MAGENTA, true);
	_headImg = IMGMANAGER->addFrameImage("snake_head1", "image/enemy_snake_head1.bmp", 1344, 336, 8, 2, true, MAGENTA, true);
	_bodyImg = IMGMANAGER->addImage("snake_body1", "image/enemy_snake_body1.bmp", 168, 168, true, MAGENTA, true);

	//상태
	SetState(MS_IDLE);
	_isDead = false;
	_goRight = (bool)RND->getInt(2);
	_dest = D_LEFT;
	_position = P_AIR;
	_originSpeed = _speed = 7.0f;
	_patternInterval = 15.0f;
	_jumpPower = 0;
	_alpha = 255;

	//연결
	_player = player;
	_stage = stage;

	//위치
	_x = _xInit = x;
	_y = _yInit = y;
	rcMake();

	

	//뱀 몸 설정
	_radius = 50;
	for (int i = 0; i < SNAKEBODY; i++)
	{
		_body[0]._angle = (i == 0) ? PI / 4 : _body[i - 1]._angle;
		_body[i]._x = (i == 0) ? x : _body[i - 1]._x - cosf(_body[i]._angle) * (_radius * 2);
		_body[i]._y = (i == 0) ? y : _body[i - 1]._y - (-sinf(_body[i]._angle) * (_radius * 2));
	}

	//이미지
	_imageXIndex = _imageYIndex = 0;
	_redrawTimer = 0;

	//스텟
	_maxLife = 1000;
	_life = _maxLife;
	_attack = 1;
	_attckCool = 0;
	_attckInterval = 1.0f;

	//상태
	setPattern(BP_CENTER);
	return S_OK;
}

void Snake::release()
{
	
}

void Snake::update()
{
	damage();
	rcMake();

	if (_life <= 0) return;
	bodyMove();
	move();
	attack();
	phaseSetting();
}

void Snake::render()
{
	for (int i = 0; i < SNAKEBODY; i++)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB)) Ellipse(getMapDC(), _body[i]._rc);

		if (!_body[i]._isDamage)
		{
			if (i == 0) _headImg->alphaFrameRender(getMapDC(), _body[i]._x - _bodyImg->getWidth() / 2, _body[i]._y - _bodyImg->getHeight() / 2, _alpha);
			else  _bodyImg->alphaRender(getMapDC(), _body[i]._x - _bodyImg->getWidth() / 2, _body[i]._y - _bodyImg->getHeight() / 2, _alpha);
		}
		else
		{
			if (i == 0) IMGMANAGER->findImage("snake_head2")->alphaFrameRender(getMapDC(), _body[i]._x - _bodyImg->getWidth() / 2, _body[i]._y - _bodyImg->getHeight() / 2, _alpha);
			else IMGMANAGER->findImage("snake_body2")->alphaRender(getMapDC(), _body[i]._x - _bodyImg->getWidth() / 2, _body[i]._y - _bodyImg->getHeight() / 2, _alpha);
		}
	}
	switch (_phase)
	{
	case BP_EASY:
		UIMANAGER->ProgressBarRender(getMapDC(), IMGMANAGER->findImage("ui_HPBar0"), CAMERAMANAGER->GetX(), CAMERAMANAGER->GetY() + 300, _life, _maxLife, 7, 2);
		break;
	case BP_NORMAL:
		UIMANAGER->ProgressBarRender(getMapDC(), IMGMANAGER->findImage("ui_HPBar1"), CAMERAMANAGER->GetX(), CAMERAMANAGER->GetY() + 300, _life, _maxLife, 7, 2);
		break;
	case BP_HARD:
		UIMANAGER->ProgressBarRender(getMapDC(), IMGMANAGER->findImage("ui_HPBar2"), CAMERAMANAGER->GetX(), CAMERAMANAGER->GetY() + 300, _life, _maxLife, 7, 2);
		break;
	default:
		break;
	}

	//채색
	HPEN _hpen = CreatePen(PS_SOLID, 15, RGB(40, 10, 10));
	HPEN _hpenOld = (HPEN)SelectObject(getMinimapDC(), (HGDIOBJ)_hpen);
	HBRUSH _hbr = CreateSolidBrush(RGB(100, 50, 200));
	HBRUSH _hbrOld = (HBRUSH)SelectObject(getMinimapDC(), _hbr);

	//미니맵 렉트
	for (int i = 0; i < SNAKEBODY; i++)	Ellipse(getMinimapDC(), _body[i]._rc);

	//삭제
	_hpen = (HPEN)SelectObject(getMinimapDC(), _hpenOld);
	DeleteObject(_hpen);
	_hbr = (HBRUSH)SelectObject(getMinimapDC(), _hbrOld);
	DeleteObject(_hbr);

}

void Snake::bodyMove()
{
	if (_body[0]._x < _body[1]._x) _dest = D_LEFT;
	else _dest = D_RIGHT;


	if (_dest == D_LEFT)
	{
		_headImg->setFrameY(1);
		_headImg->setFrameX(_headImg->getMaxFrameX());
	}
	else
	{
		_headImg->setFrameY(0);
		_headImg->setFrameX(0);
	}

	for (int i = 0; i < SNAKEBODY; i++)
	{
		if (i == 0)	//머리면
		{
			_body[i]._x += cosf(_body[i]._angle) * _speed;
			_body[i]._y += -sinf(_body[i]._angle) * _speed;

			if (_body[i]._x - _bodyImg->getFrameWidth() < 0)
			{
				CAMERAMANAGER->Shake(80, 2, 30, 10, -2);
				_body[i]._x = _bodyImg->getFrameWidth();
				_body[i]._angle = PI - _body[i]._angle;
			}
			if (_body[i]._x + _bodyImg->getFrameWidth() > CAMERAMANAGER->GetMapXSize())
			{
				CAMERAMANAGER->Shake(80, 2, 30, 10, -2);
				_body[i]._x = CAMERAMANAGER->GetMapXSize() - _bodyImg->getFrameWidth();
				_body[i]._angle = PI - _body[i]._angle;
			}
			if (_body[i]._y - _bodyImg->getFrameHeight() < 0)
			{
				CAMERAMANAGER->Shake(80, 2, 10, 30, -2);
				_body[i]._y = _bodyImg->getFrameHeight();
				_body[i]._angle = PI2 - _body[i]._angle;
			}
			if (_body[i]._y + _bodyImg->getFrameHeight() > CAMERAMANAGER->GetMapYSize())
			{
				CAMERAMANAGER->Shake(80, 2, 10, 30, -2);
				_body[i]._y = CAMERAMANAGER->GetMapYSize() - _bodyImg->getFrameHeight();
				_body[i]._angle = PI2 - _body[i]._angle;
			}
		}
		else //몸통이면
		{
			//지름보다 빗변값이 커졌다면,
			if (_radius * 2 < getDistance(_body[i]._x, _body[i]._y, _body[i - 1]._x, _body[i - 1]._y))
			{
				//바로 내 앞 인덱스의 각도를 가져온다.
				_body[i]._angle = getAngle(_body[i]._x, _body[i]._y, _body[i - 1]._x, _body[i - 1]._y);

				//각도에 따른 이동량이 달라진 것에 대해 값을 보정해준다.
				_body[i]._x = _body[i - 1]._x - (cosf(_body[i]._angle) * (_radius * 2));
				_body[i]._y = _body[i - 1]._y - (-sinf(_body[i]._angle) * (_radius * 2));
			}
			_body[i]._x += cosf(_body[i]._angle) * _speed;
			_body[i]._y += -sinf(_body[i]._angle) * _speed;
		}
	}

}

void Snake::rcMake()
{
	for (int i = 0; i < SNAKEBODY; i++)
	{
		_body[i]._rc = RectMakeCenter(_body[i]._x, _body[i]._y, _bodyImg->getWidth()-70, _bodyImg->getHeight()-70);
	}
}

void Snake::move()
{
	
	if (TIMEMANAGER->getWorldTime() - patternTimer > _patternInterval)
	{
		patternTimer = TIMEMANAGER->getWorldTime();
		if (_phase == BP_HARD) _currentPattern = BP_FOLLOW;
		else _currentPattern = BP_CENTER;
	}

	switch (_currentPattern)
	{
	case BP_IDLE:
	{
		_body[0]._angle += RND->getFromFloatTo(-0.08f, 0.08f);

	}
	break;

	break;
	case BP_RSPIN:
	{
		_body[0]._angle -= 0.04f;

	}
	break;
	case BP_LSPIN:
	{
		_body[0]._angle += 0.04f;
	}
	break;
	case BP_FOLLOW:
	{
		_body[0]._angle += RND->getFromFloatTo(-0.08f, 0.08f);

		if (getDistance(_body[0]._x, _body[0]._y, _player->GetInfo().x, _player->GetInfo().y) > 300)
			_body[0]._angle = getAngle(_body[0]._x, _body[0]._y, _player->GetInfo().x, _player->GetInfo().y);
	}
	case BP_CENTER:
	{
		_body[0]._angle = getAngle(_body[0]._x, _body[0]._y, CAMERAMANAGER->GetMapXSize() / 2, CAMERAMANAGER->GetMapYSize() / 2);
		if (getDistance(_body[0]._x, _body[0]._y, CAMERAMANAGER->GetMapXSize() / 2, CAMERAMANAGER->GetMapYSize() / 2) < 50)
		{
			_nextPattern = (BOSSPATTERN)RND->getInt(6);
			if (_nextPattern != _prevPattern) setPattern(_nextPattern);
		}
	}
	break;
	case BP_8Height:
	{
		if (isOverPI) _body[0]._angle -= 0.04f;
		else _body[0]._angle += 0.04f;

		if (_body[0]._angle >= PI * 2) isOverPI = true;
		else if (_body[0]._angle <= 0)  isOverPI = false;
	}
	break;
	case BP_8Width:
	{
		if (isOverPI) _body[0]._angle -= 0.04f;
		else _body[0]._angle += 0.04f;
		if (_body[0]._angle >= PI / 2 * 3) isOverPI = true;
		else if (_body[0]._angle <= -PI / 2)  isOverPI = false;
	}
	break;
	default:
		break;
	}
	
}

void Snake::attack()
{
	RECT tempRc;

	for (int i = 0; i < SNAKEBODY; i++)
	{
		if (IntersectRect(&tempRc, &_body[i]._rc, &_player->GetRect()))
		{
			if (_x < _player->GetInfo().x)  _player->Damage(_attack, D_LEFT, 4);
			else _player->Damage(_attack, D_RIGHT, 4);
		}
	}
}

void Snake::damage()
{
	if (_life <= 0)
	{
		_headImg->setFrameY(0);
		_headImg->setFrameX(_headImg->getMaxFrameX());

		if (_alpha >= 150) CAMERAMANAGER->Shake(80, 1, 10, 30, -1);
		if (_alpha == 255) for (int i = 0; i < SNAKEBODY; i++) _body[i]._angle = RND->getFloat(PI2);

		for (int i = 0; i < SNAKEBODY; i++)
		{
			_body[i]._x += cosf(_body[i]._angle) * _speed / 2;
			_body[i]._y += -sinf(_body[i]._angle) * _speed / 2;
		}

		_alpha -= 2;
		if (_alpha <= 0)
		{
			_isDead = true;
		}
	}


	RECT tempRc;
	for (int i = 0; i < SNAKEBODY; i++)
	{
		if (IntersectRect(&tempRc, &_body[i]._rc, &_player->GetAttackRect()))
		{
			_body[i]._isDamage = true;
			--_life;
		}
		else
		{
			_body[i]._isDamage = false;
		}
	}
}

void Snake::setPattern(BOSSPATTERN pattern)
{
	if (_currentPattern != BP_CENTER) _prevPattern = _currentPattern;

	_currentPattern = pattern;
}

void Snake::setPhase(BOSSPHASE phase)
{
	if (_phase == phase) return;
	_phase = phase;

	switch (_phase)
	{
	case BP_EASY:
		_phase = BP_EASY;
		break;
	case BP_NORMAL:
		_phase = BP_NORMAL;
		break;
	case BP_HARD:
		_phase = BP_HARD;
		break;
	default:
		break;
	}
}

void Snake::phaseSetting()
{
	if (_life <= _maxLife / 3) setPhase(BP_HARD);
	else if (_life <= _maxLife / 3*2) setPhase(BP_NORMAL);
	else if (_life <= _maxLife) setPhase(BP_EASY);

	switch (_phase)
	{
	case BP_EASY:
		_speed = _originSpeed +0;
		_patternInterval = 10.0f;
		break;
	case BP_NORMAL:
		_speed = _originSpeed +2.0f;
		_patternInterval = 8.0f;
		break;
	case BP_HARD:
		_speed = _originSpeed +4.0f;
		_patternInterval = 5.0f;
		break;
	default:
		break;
	}
}
