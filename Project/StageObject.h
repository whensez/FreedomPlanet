#pragma once
#include "gameNode.h"

enum POSITION;

struct tagCollision
{
	RECT rc;
	RECT tempRc;
};

struct Background
{
	image* _img;
	POINT _pos;
	int _loopX, _loopY;
};

struct Middleground
{
	RECT _rc;
	image* _img;
	POINT _pos;
	int _loopX, _loopY;
};

enum GROUNDTYPE
{
	GT_GROUND,
	GT_GRASS,
	GT_ROAD,
};

struct tagGround
{
	image* _img;
	POINT _pos;
};

struct Terrain : public gameNode
{
	tagGround* _ground;
	int _count;
	POINT _posLT;
	tagCollision _collision;
	POSITION _position;

public:
	Terrain() {}
	~Terrain() {}

	virtual void render();

	void SetGround(int count, int x, int y, POSITION position, GROUNDTYPE type);

	tagCollision &getCollision() { return _collision; }
	POSITION getPosition() { return _position; }
};

enum OBJECTTYPE
{
	OT_CLOUD,
	OT_ROCK,
	OT_TREE1,
	OT_TREE2,
	OT_TREE3,
	OT_TREE4,
};

struct Object : public gameNode
{
	image* _img;
	POINT _pos;
	int _indexX;

	void SetObject(int x, int y, OBJECTTYPE type);
};

