#pragma once
#include "gameNode.h"
#include <vector>
class Player;
class Stage;

struct tagBullet
{
	image* _img;			//이미지
	RECT _rc;				//충돌용 렉트
	int _x, _y;				//중점 좌표
	float _fireX, _fireY;	//발사 위치
	float _angle;			//각도
	float _radius;			//반지름
	float _speed;			//속도
	float _gravity;			//중력
};

typedef vector<tagBullet*> vBullet;	//불렛 벡터

class Cannon : public gameNode	//대포
{
private:
	vBullet _vCannon;		//불렛 벡터
	const char* _imgName;	//이미지 이름
	float _range;			//범위
	int _bulletMax;			//최대 개수
	Player* _player;		//플래이어
	Stage* _stage;			//스테이지

public:

	Cannon() {}
	~Cannon() {}

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	//발사 (발사 위치, 목표 위치, 속도)
	void Fire(int x, int y, int goalX, int goalY, float speed);

	//SETTER
	void SetPlayerAddressLink(Player* player) { _player = player; }
	void SetStageAddressLink(Stage* stage) { _stage = stage; }

	//GETTER
	vBullet GetCannon() { return _vCannon; }



private:

	//이동
	void Move();

	//충돌
	void Collision();

	//삭제
	void Erase(int num);

};

