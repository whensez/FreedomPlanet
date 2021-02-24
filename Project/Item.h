#pragma once
#include "gameNode.h"
#include <vector>

class Player;
enum ITEMTYPE
{
	I_LEAF,
	I_BUBBLE,
	I_CRYSTAL,
};
struct tagItem
{
	ITEMTYPE _type;
	animation* _ani;
	image* _img;
	int _x, _y;
	RECT _rc;
	int _xIndex;
	bool _isDrag;
	float _timer;
	int _alpha;
	bool _isEternal;
};

typedef vector<tagItem*> vItem;

class Item : public gameNode
{
private:

	float _speed;

	vItem _vItem;
	Player* _player;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void make(int x, int y, ITEMTYPE type, bool isEternal);
	void move();
	void collision();
	void disappear();

	void SetPlayerAddressLink(Player* player) { _player = player; }

	vItem getvItem() { return _vItem; }

	void erase(int i);
};

