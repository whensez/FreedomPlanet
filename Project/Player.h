#pragma once
#include "gameNode.h"
#include "Pet.h"

#define JUMPPOWER 7.5f			//점프력
#define SPEEDPOWER 6.0f			//이동 속도

class StageManager;
struct tagCollision;
class IPlayerState;

enum DEST;
enum POSITION;
enum ITEMTYPE;

enum PLAYERSTATE		//플래이어 상태
{
	PS_IDLE,			//기본
	PS_WAIT,			//대기

	PS_WALK,			//걷기
	PS_RUN,				//뛰기
	PS_ROLL,			//구르기

	PS_JUMP,			//점프
	PS_FALLEN,			//하강
	
	PS_ATTACK,			//단거리
	PS_BEAM,			//장거리
	PS_DAMAGE,			//피격
	PS_DIE,				//죽음

	PS_HANG,			//매달리기
	PS_CLIMB,			//오르기

	PS_SMILE,			//웃음
};

class Player : public gameNode
{
	//정보를 담은 구조체
	typedef struct tagInfo
	{
	public:
		float x, y;					//중점 좌표
		RECT rcDamage, rcAttack;	//피격, 공격 범위 렉트
		int rcWidth, rcHeight;		//렉트 가로세로 크기
	
		float speed;				//횡 이동 속도
		float jumpPower;			//점프력
		bool isImmune;				//무적
		int immuneTimer;			//무적 시간
		float alphaTimer;			//알파 시간
		int alpha;					//투명도
	
		bool isDead;				//죽었는지
		bool isControl;				//컨트롤 여부
		DEST dest;					//방향
		POSITION position;			//위치
		PLAYERSTATE state;			//현재 상태

		image* img;					//이미지
		image* iconImg;				//아이콘 이미지
		int imageXIndex;			//이미지 가로 인덱스
		int imageYIndex;			//이미지 세로 인덱스
		float redrawTimer;			//이미지 다시 그리는 타이머
		float redrawInterval;		//이미지 다시 그리는 간격
		
		image* beamImg;				//빔 이미지
		int beam;					//빔 길이
		float effectStarTimer;		//이펙트 효과 타이머
		image* countImg;			//카운터이미지
		animation* countAni;		//카운터애니

		int gauge;					//대쉬 게이지
		int gaugeMax;				//최대 대쉬 게이지
		int rollTimer;				//닷지 시간
	
		int maxLife;				//최대 생명력
		int life;					//생명력
		int attack;					//공격력
		int crystal;				//크리스탈
	};

private:

	IPlayerState* _Istate;			//상태 패턴
	IPlayerState* _attack;
	IPlayerState* _beam;
	IPlayerState* _climb;
	IPlayerState* _damage;
	IPlayerState* _die;
	IPlayerState* _fallen;
	IPlayerState* _hang;
	IPlayerState* _idle;
	IPlayerState* _jump;
	IPlayerState* _roll;
	IPlayerState* _run;
	IPlayerState* _wait;
	IPlayerState* _walk;
	IPlayerState* _smile;

	tagInfo _info;
	StageManager* _stageM;		//스테이지매니저
	Pet* _pet;					//펫
	
public:
	// ==================== BASIC FUNC ====================

	Player();
	~Player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// ==================== LINK ====================

	//스테이지와 주소를 연결한다.
	void SetStageMAddressLink(StageManager* stageM) { _stageM = stageM; }

	// ==================== GETTER ====================
	
	RECT& GetRect() { return _info.rcDamage; }
	RECT& GetAttackRect() { return _info.rcAttack; }
	tagInfo& GetInfo() { return _info; }

	// ==================== SETTER ====================

	void SetControl(bool control) { _info.isControl = control; }
	void SetPosition(POSITION position) { _info.position = position; }
	void SetJumpPower(float jump) { _info.jumpPower = jump; }
	void SetState(PLAYERSTATE state);
	void SetAlpha(int alpha) { _info.alpha = alpha; }
	void SetImmune(bool immune) { _info.isImmune = immune; _info.immuneTimer = 200; }
	void SetRollTimer(int count) { _info.rollTimer = count; }

	// ==================== PUBLIC FUNC ====================

public:

	//스테이지를 위한 초기화를 한다.
	void StageInit();

	//피격 받는다.
	void Damage(int dmg, DEST dest, float jump);

	//아이템을 얻는다.
	void AddItem(ITEMTYPE type);

	//세이브 데이터를 저장한다.
	void SaveData();

	//세이브 데이터를 로드한다.
	void LoadData();

	//이미지와 렉트를 설정한다.
	void ImageRect(string strKey, int offsetX, int offsetY);

	//x, y만큼 이동시키고 렉트를 갱신한다.
	void xyMove(int x, int y);
	
	//게이지를 조절한다.
	void AdjustGauge(int plus);

	//빔을 조절한다.
	void AdjustBeam(int plus);

	//공격 렉트를 조절한다.
	void AdjustAttackRect(bool rect);

	void SetDie(bool die) { _info.isDead = die; }

	// ==================== PRIVATE FUNC ====================
private:
	//충돌 확인용 함수
	bool UDCollision(tagCollision& col);
	bool LRCollision(tagCollision& col);
	bool Collision(tagCollision& col);


	//움직임을 실행한다.
	void Move();

	//키 입력을 실행한다.
	void KeyInput();

	//이미지를 다시 그린다.
	void FrameUpdate();

	//프레임을 재생한다.
	void FramePlay(int count);

	//땅에 서 있는다.
	void TerrainStand();

	//수치를 조절한다.
	void Adjust();

};

