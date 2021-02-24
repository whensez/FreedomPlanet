#include "stdafx.h"
#include "Pet.h"
#include "Player.h"
#include "Enums.h"

HRESULT Pet::init()
{
	IMGMANAGER->addFrameImage("pet", "image/pet.bmp", 896, 160, 14, 2, true, MAGENTA);

	_x = WINSIZEX/3;
	_y = WINSIZEY/3;
	_xOffset = 120;
	_yOffset = 80;

	_speed = 3;
	_jumpPower = 0;

	_img = IMGMANAGER->findImage("pet");
	_imageXIndex = 0;
	_imageYIndex = 0;
	_redrawTimer = 0;
	_redrawInterval = 12;

	_rcWidth = _img->getFrameWidth();
	_rcHeight = _img->getFrameHeight();
	_rc = RectMakeCenter(_x, _y, _rcWidth, _rcHeight);

	_dest = D_RIGHT;
	_currentState = IDLE;
	_isVisible = true;

	return S_OK;
}

void Pet::release()
{
}

void Pet::update(int x, int y)
{
	Move(x, y);
	ImageRedraw();
}

void Pet::render()
{
	if(_isVisible) _img->frameRender(getMapDC(), _rc.left, _rc.top);
}

void Pet::StageInit()
{

	_x = WINSIZEX / 3;
	_y = WINSIZEY / 3;

}

void Pet::Move(int x, int y)
{
	//펫이 일정 거리 이상 멀어지면 보정 속도를 추가한다.
	int revisionXSpeed = 0;			
	int revisionYSpeed = 0;
	if (abs(x - _x) > WINSIZEX / 4) revisionXSpeed = abs(x - _x) / 64;
	if (abs(y - _y) > WINSIZEY / 4) revisionYSpeed = abs(y - _y) / 64;

	if (_x > x + _xOffset/2)
	{
		_dest = D_LEFT;
		--_x;
	}

	if (_x < x - _xOffset/2)
	{
		_dest = D_RIGHT;
		++_x;
	}

	if (_x < x - _xOffset) _x += _speed + revisionXSpeed;
	if (_x > x + _xOffset) _x -= _speed + revisionXSpeed;
	if (_y <= y - _yOffset) _y += _speed + revisionYSpeed;
	if (_y >= y + _yOffset) _y -= _speed + revisionYSpeed;
	_rc = RectMakeCenter(_x, _y, _rcWidth, _rcHeight);

}

void Pet::ImageRedraw()
{
	if (++_redrawTimer >= _redrawInterval)
	{
		_redrawTimer = 0;
		FramePlay();
	}
}

void Pet::SetState(PETSTATE state)
{
	if (_currentState == state) return;
	_prevState = _currentState;	//이전 상태를 저장한다
	_currentState = state;

	switch (_currentState)
	{
	case IDLE:
		_imageXIndex = 3;
	break;
	case JUMP:
		_imageXIndex = 0;
	break;
	case SMILE:
		_imageXIndex = 10;
	break;
	}

	switch (_dest)
	{
	case D_RIGHT: break;
	case D_LEFT:_imageXIndex = _img->getMaxFrameX() - _imageXIndex;
	break;
	}
	_redrawTimer = _redrawInterval;							//바로 다시 그린다.
}


void Pet::FramePlay()
{	

	switch (_currentState)
	{
		case IDLE:
			if (_dest == D_RIGHT && _imageXIndex > 8) _imageXIndex = 3;
			else if (_dest == D_LEFT && _imageXIndex < 5) _imageXIndex = 9;
		break;
		case JUMP:
			if (_dest == D_RIGHT && _imageXIndex > 8) _imageXIndex = 0;
			else if (_dest == D_LEFT && _imageXIndex < 5) _img->getMaxFrameX();
		break;
		case SMILE:
			if (_dest == D_RIGHT && _imageXIndex > _img->getMaxFrameX()) SetState(IDLE);
			else if (_dest == D_LEFT && _imageXIndex < 0) SetState(IDLE);
		break;
	}


	_imageYIndex = _dest;

	switch (_dest)
	{
	case D_RIGHT:
		_img->setFrameX(_imageXIndex);
		_img->setFrameY(_imageYIndex);
		_imageXIndex++;
		break;
	case D_LEFT:
		_img->setFrameX(_imageXIndex);
		_img->setFrameY(_imageYIndex);
		_imageXIndex--;
		break;
	}

}
