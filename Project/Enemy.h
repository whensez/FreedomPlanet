#pragma once
#include "gameNode.h"
#include "Enums.h"

class IEnemyState;

class tagCollision;
class Player;
class Stage;

enum MS_STATE
{
	MS_IDLE,
	MS_PATROL,
	MS_ATTACK,
	MS_DAMAGE,
	MS_DIE
};

class Enemy : public gameNode
{
protected:
	int _x, _y;					//���� ���� ��ǥ
	int _xInit, _yInit;			//�ʱ� ���� ��ǥ

	RECT _rcTerrain;			//�ʱ� ���� ��Ʈ
	RECT _rcDamage;				//�ǰ� ���� ��Ʈ
	RECT _rcAttack;				//���� ���� ��Ʈ
	RECT _rcSense;				//���� ���� ��Ʈ
	RECT _rcRange;				//�̵� ���� ��Ʈ

	bool _isDead;				//�׾�����
	bool _goRight;				//���������� ������

	IEnemyState* _EnemyState;	//���� ���� ����
	IEnemyState* _ES_attack;	//���� ���� ����
	IEnemyState* _ES_damage;	//���� ���� ����
	IEnemyState* _ES_die;		//���� ���� ����
	IEnemyState* _ES_idle;		//���� ���� ����
	IEnemyState* _ES_patrol;	//���� ���� ����

	MS_STATE _state;			//���� ���� enum
	DEST _dest;					//����
	POSITION _position;			//��ġ

	float _speed;				//���� �̵� �ӵ�
	float _originSpeed;			//�⺻ �̵� �ӵ�
	float _jumpPower;			//������
	int _alpha;					//����
	float _angle;				//����

	image* _img;				//�̹���
	image* _imgIdle;			//�̹���
	image* _imgAttack;			//�̹���
	image* _imgPatrol;			//�̹���
	image* _imgDamage;			//�̹���
	image* _imgDie;				//�̹���

	int _imageXIndex;			//�̹��� ���� �ε���
	int _imageYIndex;			//�̹��� ���� �ε���
	float _redrawTimer;			//�̹��� �ٽ� �׸��� Ÿ�̸�

	int _maxLife;				//�ִ� �����
	int _life;					//�����
	int _attack;				//���ݷ�
	float _attckCool;			//���� ��Ÿ��
	float _attckInterval;		//���� ���͹�
	bool _isAttack;				//�����ߴ�


	Player* _player;			//�÷��̾�
	Stage* _stage;				//��������

public:
	Enemy() {}
	~Enemy() {}

	virtual HRESULT init();
	virtual HRESULT init(Player* player, Stage* stage, RECT rc);
	virtual HRESULT init(Player* player, Stage* stage, int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void xyMove(int x, int y);
	virtual void rcMake() {}

	virtual void jump(float jump);
	virtual void attack();
	void die();

	//�Ϲ� �Լ�
	void SetImage();
	void imageRedraw();
	

	void damage() { if (_life <= 0) return; _life -= 1; }

	//����
	bool getIsDead() { return _isDead; }
	bool& getGoRight() { return _goRight; }
	float& getSpeed() { return _speed; }
	float& getOriginSpeed() { return _originSpeed; }
	int getX() { return _x; }
	int getY() { return _y; }

	RECT getRcTerrain() { return _rcTerrain; }
	RECT getRcDamage() { return _rcDamage; }
	RECT getRcAttack() { return _rcAttack; }
	RECT getRcSense() { return _rcSense; }
	RECT getRcRange() { return _rcRange; }

	int getAttack() { return _attack; }

	Player* getPlayerAddress() { return _player; }

	//����
	void setDest(DEST dest) { _dest = dest;  }
	void setGoRight(bool go) { _goRight = go;  }
	void setPosition(POSITION position) { _position = position;  }
	void setIsAttack(bool attack) {_isAttack = attack;}
	

	//���������� �ּҸ� �����Ѵ�.
	void setStageAddressLink(Stage* stageM) { _stage = stageM; }

	//�浹 Ȯ�ο� �Լ�
	bool UDCollision(tagCollision& col);
	bool LRCollision(tagCollision& col);
	bool Collision(tagCollision& col);

	void TerrainStand();

	void SetState(MS_STATE state);
	void FramePlay(int count);
};

