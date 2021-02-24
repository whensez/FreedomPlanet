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
	int _x, _y;					//현재 중점 좌표
	int _xInit, _yInit;			//초기 중점 좌표

	RECT _rcTerrain;			//초기 지형 렉트
	RECT _rcDamage;				//피격 범위 렉트
	RECT _rcAttack;				//공격 범위 렉트
	RECT _rcSense;				//감지 범위 렉트
	RECT _rcRange;				//이동 범위 렉트

	bool _isDead;				//죽었는지
	bool _goRight;				//오른쪽으로 가는지

	IEnemyState* _EnemyState;	//현재 상태 패턴
	IEnemyState* _ES_attack;	//현재 상태 패턴
	IEnemyState* _ES_damage;	//현재 상태 패턴
	IEnemyState* _ES_die;		//현재 상태 패턴
	IEnemyState* _ES_idle;		//현재 상태 패턴
	IEnemyState* _ES_patrol;	//현재 상태 패턴

	MS_STATE _state;			//현재 상태 enum
	DEST _dest;					//방향
	POSITION _position;			//위치

	float _speed;				//현재 이동 속도
	float _originSpeed;			//기본 이동 속도
	float _jumpPower;			//점프력
	int _alpha;					//투명도
	float _angle;				//각도

	image* _img;				//이미지
	image* _imgIdle;			//이미지
	image* _imgAttack;			//이미지
	image* _imgPatrol;			//이미지
	image* _imgDamage;			//이미지
	image* _imgDie;				//이미지

	int _imageXIndex;			//이미지 가로 인덱스
	int _imageYIndex;			//이미지 세로 인덱스
	float _redrawTimer;			//이미지 다시 그리는 타이머

	int _maxLife;				//최대 생명력
	int _life;					//생명력
	int _attack;				//공격력
	float _attckCool;			//공격 쿨타임
	float _attckInterval;		//공격 인터벌
	bool _isAttack;				//공격했니


	Player* _player;			//플래이어
	Stage* _stage;				//스테이지

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

	//일반 함수
	void SetImage();
	void imageRedraw();
	

	void damage() { if (_life <= 0) return; _life -= 1; }

	//게터
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

	//세터
	void setDest(DEST dest) { _dest = dest;  }
	void setGoRight(bool go) { _goRight = go;  }
	void setPosition(POSITION position) { _position = position;  }
	void setIsAttack(bool attack) {_isAttack = attack;}
	

	//스테이지와 주소를 연결한다.
	void setStageAddressLink(Stage* stageM) { _stage = stageM; }

	//충돌 확인용 함수
	bool UDCollision(tagCollision& col);
	bool LRCollision(tagCollision& col);
	bool Collision(tagCollision& col);

	void TerrainStand();

	void SetState(MS_STATE state);
	void FramePlay(int count);
};

