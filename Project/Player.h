#pragma once
#include "gameNode.h"
#include "Pet.h"

#define JUMPPOWER 7.5f			//������
#define SPEEDPOWER 6.0f			//�̵� �ӵ�

class StageManager;
struct tagCollision;
class IPlayerState;

enum DEST;
enum POSITION;
enum ITEMTYPE;

enum PLAYERSTATE		//�÷��̾� ����
{
	PS_IDLE,			//�⺻
	PS_WAIT,			//���

	PS_WALK,			//�ȱ�
	PS_RUN,				//�ٱ�
	PS_ROLL,			//������

	PS_JUMP,			//����
	PS_FALLEN,			//�ϰ�
	
	PS_ATTACK,			//�ܰŸ�
	PS_BEAM,			//��Ÿ�
	PS_DAMAGE,			//�ǰ�
	PS_DIE,				//����

	PS_HANG,			//�Ŵ޸���
	PS_CLIMB,			//������

	PS_SMILE,			//����
};

class Player : public gameNode
{
	//������ ���� ����ü
	typedef struct tagInfo
	{
	public:
		float x, y;					//���� ��ǥ
		RECT rcDamage, rcAttack;	//�ǰ�, ���� ���� ��Ʈ
		int rcWidth, rcHeight;		//��Ʈ ���μ��� ũ��
	
		float speed;				//Ⱦ �̵� �ӵ�
		float jumpPower;			//������
		bool isImmune;				//����
		int immuneTimer;			//���� �ð�
		float alphaTimer;			//���� �ð�
		int alpha;					//����
	
		bool isDead;				//�׾�����
		bool isControl;				//��Ʈ�� ����
		DEST dest;					//����
		POSITION position;			//��ġ
		PLAYERSTATE state;			//���� ����

		image* img;					//�̹���
		image* iconImg;				//������ �̹���
		int imageXIndex;			//�̹��� ���� �ε���
		int imageYIndex;			//�̹��� ���� �ε���
		float redrawTimer;			//�̹��� �ٽ� �׸��� Ÿ�̸�
		float redrawInterval;		//�̹��� �ٽ� �׸��� ����
		
		image* beamImg;				//�� �̹���
		int beam;					//�� ����
		float effectStarTimer;		//����Ʈ ȿ�� Ÿ�̸�
		image* countImg;			//ī�����̹���
		animation* countAni;		//ī���;ִ�

		int gauge;					//�뽬 ������
		int gaugeMax;				//�ִ� �뽬 ������
		int rollTimer;				//���� �ð�
	
		int maxLife;				//�ִ� �����
		int life;					//�����
		int attack;					//���ݷ�
		int crystal;				//ũ����Ż
	};

private:

	IPlayerState* _Istate;			//���� ����
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
	StageManager* _stageM;		//���������Ŵ���
	Pet* _pet;					//��
	
public:
	// ==================== BASIC FUNC ====================

	Player();
	~Player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// ==================== LINK ====================

	//���������� �ּҸ� �����Ѵ�.
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

	//���������� ���� �ʱ�ȭ�� �Ѵ�.
	void StageInit();

	//�ǰ� �޴´�.
	void Damage(int dmg, DEST dest, float jump);

	//�������� ��´�.
	void AddItem(ITEMTYPE type);

	//���̺� �����͸� �����Ѵ�.
	void SaveData();

	//���̺� �����͸� �ε��Ѵ�.
	void LoadData();

	//�̹����� ��Ʈ�� �����Ѵ�.
	void ImageRect(string strKey, int offsetX, int offsetY);

	//x, y��ŭ �̵���Ű�� ��Ʈ�� �����Ѵ�.
	void xyMove(int x, int y);
	
	//�������� �����Ѵ�.
	void AdjustGauge(int plus);

	//���� �����Ѵ�.
	void AdjustBeam(int plus);

	//���� ��Ʈ�� �����Ѵ�.
	void AdjustAttackRect(bool rect);

	void SetDie(bool die) { _info.isDead = die; }

	// ==================== PRIVATE FUNC ====================
private:
	//�浹 Ȯ�ο� �Լ�
	bool UDCollision(tagCollision& col);
	bool LRCollision(tagCollision& col);
	bool Collision(tagCollision& col);


	//�������� �����Ѵ�.
	void Move();

	//Ű �Է��� �����Ѵ�.
	void KeyInput();

	//�̹����� �ٽ� �׸���.
	void FrameUpdate();

	//�������� ����Ѵ�.
	void FramePlay(int count);

	//���� �� �ִ´�.
	void TerrainStand();

	//��ġ�� �����Ѵ�.
	void Adjust();

};

