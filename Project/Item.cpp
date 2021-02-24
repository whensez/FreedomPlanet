#include "stdafx.h"
#include "Item.h"
#include "Player.h"

HRESULT Item::init()
{
	_speed = 5.0f;
	return S_OK;
}

void Item::release()
{
	for (int i = 0; i < _vItem.size();)
	{
		erase(i);
	}
}

void Item::update()
{
	move();
	collision();
	disappear();
}

void Item::render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB)) Ellipse(getMapDC(), _vItem[i]->_rc);
		_vItem[i]->_img->aniRender(getMapDC(), _vItem[i]->_x - _vItem[i]->_img->getFrameWidth() / 2, _vItem[i]->_y - _vItem[i]->_img->getFrameHeight() / 2, _vItem[i]->_ani, _vItem[i]->_alpha);
	}
}


void Item::make(int x, int y, ITEMTYPE type, bool isEternal)
{
	tagItem* item = new tagItem;

	item->_type = type;
	switch (item->_type)
	{
		case I_LEAF:
			item->_img = IMGMANAGER->findImage("leaf");
		break;
		case I_BUBBLE:
			item->_img = IMGMANAGER->findImage("bubble");
		break;
		case I_CRYSTAL:
			item->_img = IMGMANAGER->findImage("crystal");
		break;
		default:
		break;
	}

	item->_ani = new animation;
	item->_ani->init(item->_img->getWidth(), item->_img->getHeight(), item->_img->getFrameWidth(), item->_img->getFrameHeight());
	item->_ani->setDefPlayFrame(true, true);
	item->_ani->setFPS(1);

	item->_x = x;
	item->_y = y;
	item->_xIndex = 0;
	item->_rc = RectMakeCenter(item->_x, item->_y, item->_img->getFrameWidth(), item->_img->getFrameHeight());
	item->_timer = TIMEMANAGER->getWorldTime();
	item->_alpha = 255;
	item->_ani->start();
	item->_isDrag = false;
	item->_isEternal = isEternal;
	_vItem.push_back(item);
}

void Item::move()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		if (getDistance(_vItem[i]->_x, _vItem[i]->_y, _player->GetInfo().x, _player->GetInfo().y) < 200) _vItem[i]->_isDrag = true;
		if(_vItem[i]->_isDrag)
		{
			_vItem[i]->_x += cosf(getAngle(_vItem[i]->_x, _vItem[i]->_y, _player->GetInfo().x, _player->GetInfo().y))
				*(_speed + getDistance(_vItem[i]->_x, _vItem[i]->_y, _player->GetInfo().x, _player->GetInfo().y) / 50);
			_vItem[i]->_y -= sinf(getAngle(_vItem[i]->_x, _vItem[i]->_y, _player->GetInfo().x, _player->GetInfo().y))
				*(_speed + getDistance(_vItem[i]->_x, _vItem[i]->_y, _player->GetInfo().x, _player->GetInfo().y) / 50);
			_vItem[i]->_rc = RectMakeCenter(_vItem[i]->_x, _vItem[i]->_y, _vItem[i]->_img->getFrameWidth(), _vItem[i]->_img->getFrameHeight());
		}
	}
}

void Item::collision()
{
	for (int i = 0; i < _vItem.size();)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->GetRect(), &_vItem[i]->_rc))
		{
			_player->AddItem(_vItem[i]->_type);
			erase(i);
		}
		else i++;
	}
}

void Item::disappear()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (_vItem[i]->_isEternal) continue;
		if (TIMEMANAGER->getWorldTime() - _vItem[i]->_timer > 3.0f) _vItem[i]->_alpha -= 5;
		if (_vItem[i]->_alpha < 0)  _vItem[i]->_alpha = 0;
	}

	for (int i = 0; i < _vItem.size();)
	{
		if (_vItem[i]->_alpha <= 0) erase(i);
		else i++;
	}
}

void Item::erase(int i)
{
	SAFE_DELETE(_vItem[i]);
	_vItem.erase(_vItem.begin() + i);
}
