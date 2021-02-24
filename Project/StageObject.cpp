#include "stdafx.h"
#include "StageObject.h"
#include "Enums.h"

// ======================== 물건 ========================

void Object::SetObject(int x, int y, OBJECTTYPE type)
{
	_pos.x = x;
	_pos.y = y;
	_indexX = 0;

	switch (type)
	{
	case OT_CLOUD:
		_img = IMGMANAGER->findImage("cloud");
		break;
	case OT_ROCK:
		_img = IMGMANAGER->findImage("rock");
		break;
	case OT_TREE1:
		_img = IMGMANAGER->findImage("tree1");
		break;
	case OT_TREE2:
		_img = IMGMANAGER->findImage("tree2");
		break;
	case OT_TREE3:
		_img = IMGMANAGER->findImage("tree3");
		break;
	case OT_TREE4:
		_img = IMGMANAGER->findImage("tree4");
		break;
	default:
		break;
	}
	_indexX = RND->getInt(_img->getMaxFrameX());

}
// ======================== 지형 ========================

void Terrain::SetGround(int count, int x, int y, POSITION position, GROUNDTYPE type)
{
	_posLT.x = x;
	_posLT.y = y;
	_position = position;
	_count = count + 2;

	//개수만큼 땅 만들기
	_ground = new tagGround[_count];

	switch (type)		//이미지 설정
	{
	case GT_GROUND:
	{
		for (int i = 0; i < _count; i++) _ground[i]._img = IMGMANAGER->findImage("ground1");
		_ground[0]._img = IMGMANAGER->findImage("ground0");
		_ground[_count - 1]._img = IMGMANAGER->findImage("ground2");
	}
	break;
	case GT_GRASS:
	{
		for (int i = 0; i < _count; i++) _ground[i]._img = IMGMANAGER->findImage("grass1");
		_ground[0]._img = IMGMANAGER->findImage("grass0");
		_ground[_count - 1]._img = IMGMANAGER->findImage("grass2");
	}
	break;
	case GT_ROAD:
	{
		for (int i = 0; i < _count; i++) _ground[i]._img = IMGMANAGER->findImage("road1");
		_ground[0]._img = IMGMANAGER->findImage("road0");
		_ground[_count - 1]._img = IMGMANAGER->findImage("road2");
	}
	break;
	}

	//좌표 설정
	for (int i = 0; i < _count; i++)
	{
		_ground[i]._pos.y = _posLT.y;
		_ground[i]._pos.x = _posLT.x + _ground[0]._img->getWidth() + _ground[1]._img->getWidth() * (i - 1);
	}
	_ground[0]._pos.x = _posLT.x;

	//rc 설정
	_collision.rc = RectMake(_posLT.x, _posLT.y,
		_ground[0]._img->getWidth() * 2 + _ground[1]._img->getWidth()*(_count - 2), _ground[1]._img->getHeight() - 30);

}


void Terrain::render()
{
	for (int i = 0; i < _count; i++)
	{
		_ground[i]._img->render(getMapDC(), _ground[i]._pos.x, _ground[i]._pos.y);
		_ground[i]._img->render(getMinimapDC(), _ground[i]._pos.x, _ground[i]._pos.y);
	}

	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMapDC(), _collision.rc);
}