#pragma once
#include "gameNode.h"
#include <vector>
class Player;
class Stage;

struct tagBullet
{
	image* _img;			//�̹���
	RECT _rc;				//�浹�� ��Ʈ
	int _x, _y;				//���� ��ǥ
	float _fireX, _fireY;	//�߻� ��ġ
	float _angle;			//����
	float _radius;			//������
	float _speed;			//�ӵ�
	float _gravity;			//�߷�
};

typedef vector<tagBullet*> vBullet;	//�ҷ� ����

class Cannon : public gameNode	//����
{
private:
	vBullet _vCannon;		//�ҷ� ����
	const char* _imgName;	//�̹��� �̸�
	float _range;			//����
	int _bulletMax;			//�ִ� ����
	Player* _player;		//�÷��̾�
	Stage* _stage;			//��������

public:

	Cannon() {}
	~Cannon() {}

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	//�߻� (�߻� ��ġ, ��ǥ ��ġ, �ӵ�)
	void Fire(int x, int y, int goalX, int goalY, float speed);

	//SETTER
	void SetPlayerAddressLink(Player* player) { _player = player; }
	void SetStageAddressLink(Stage* stage) { _stage = stage; }

	//GETTER
	vBullet GetCannon() { return _vCannon; }



private:

	//�̵�
	void Move();

	//�浹
	void Collision();

	//����
	void Erase(int num);

};

