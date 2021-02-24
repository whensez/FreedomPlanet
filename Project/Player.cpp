#include "stdafx.h"
#include "Player.h"
#include "StageManager.h"
#include "Stage.h"
#include "Enums.h"

#include "PlayerAttack.h"
#include "PlayerBeam.h"
#include "PlayerClimb.h"
#include "PlayerDamage.h"
#include "PlayerDie.h"
#include "PlayerFallen.h"
#include "PlayerHang.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerRoll.h"
#include "PlayerRun.h"
#include "PlayerWait.h"
#include "PlayerWalk.h"
#include "PlayerSmile.h"

// ================== 디버그 용 ==================
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
// ==============================================

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::init()
{
	//이미지 추가
	IMGMANAGER->addFrameImage("milla_idle", "image/milla_idle0.bmp", 756, 200, 9, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_wait1", "image/milla_idle1.bmp", 1176, 200, 14, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_wait2", "image/milla_idle2.bmp", 558, 200, 7, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_wait3", "image/milla_idle3.bmp", 840, 200, 10, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_walk", "image/milla_walk.bmp", 840, 200, 10, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_run", "image/milla_run.bmp", 660, 200, 6, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_jump", "image/milla_jump.bmp", 756, 200, 9, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_fallen", "image/milla_fallen.bmp", 588, 200, 7, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_hang", "image/milla_hang.bmp", 186, 200, 2, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_attack", "image/milla_attack.bmp", 600, 200, 6, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_roll", "image/milla_dodge.bmp", 608, 200, 8, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_climb", "image/milla_climb.bmp", 1428, 216, 17, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_damage", "image/milla_damage.bmp", 504, 200, 6, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_die", "image/milla_die.bmp", 448, 200, 4, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_beam", "image/milla_beam.bmp", 84, 200, 1, 2, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("milla_smile", "image/milla_smile.bmp", 588, 200, 7, 2, true, MAGENTA, true);

	EFFECTMANAGER->addEffect("green", "effect_green.bmp", 1050, 150, 150, 150, 1.0f, 0.2f, 20);
	EFFECTMANAGER->addEffect("greenStar", "effect_greenStar.bmp", 768, 64, 64, 64, 1.0f, 0.8f, 100);

	_info.iconImg = IMGMANAGER->addImage("milla_icon", "image/milla_icon.bmp", 35, 35, true, MAGENTA);
	_info.beamImg = IMGMANAGER->addImage("beam", "image/effect_beam.bmp", 37, 50, true, MAGENTA, true);
	_info.countImg = IMGMANAGER->addFrameImage("ui_counter", "image/effect_count.bmp", 192, 40, 6, 1, true, MAGENTA);

	_attack = new PlayerAttack;
	_beam = new PlayerBeam;
	_climb = new PlayerClimb;
	_damage = new PlayerDamage;
	_die = new PlayerDie;
	_fallen = new PlayerFallen;
	_hang = new PlayerHang;
	_idle = new PlayerIdle;
	_jump = new PlayerJump;
	_roll = new PlayerRoll;
	_run = new PlayerRun;
	_wait = new PlayerWait;
	_walk = new PlayerWalk;
	_smile = new PlayerSmile;

	//초기 위치
	_info.x = WINSIZEX / 4;
	_info.y = WINSIZEY / 2;

	_info.redrawTimer = 0;
	_info.redrawInterval = 0.12f;

	_info.speed = SPEEDPOWER;
	_info.jumpPower = -1;

	_info.isDead = false;
	_info.isControl = true;
	_info.dest = D_RIGHT;
	_info.position = P_AIR;
	SetState(PS_JUMP);

	_info.rollTimer = 150;

	_info.countAni = new animation;
	_info.countAni->init(_info.countImg->getWidth(), _info.countImg->getHeight(), _info.countImg->getFrameWidth(), _info.countImg->getFrameHeight());
	_info.countAni->setDefPlayFrame(false, true);
	_info.countAni->setFPS(1);
	_info.countAni->start();

	_info.gaugeMax = 1000;
	_info.gauge = _info.gaugeMax;

	_info.maxLife = 10;
	_info.life = _info.maxLife;
	_info.crystal = 0;
	_info.isImmune = false;
	_info.alphaTimer = 0;
	_info.alpha = 255;

	//펫
	_pet = new Pet;
	_pet->init();

	return S_OK;
}

void Player::release()
{
	SAFE_DELETE(_Istate);
	SAFE_DELETE(_attack);
	SAFE_DELETE(_beam);
	SAFE_DELETE(_climb);
	SAFE_DELETE(_damage);
	SAFE_DELETE(_die);
	SAFE_DELETE(_fallen);
	SAFE_DELETE(_hang);
	SAFE_DELETE(_idle);
	SAFE_DELETE(_jump);
	SAFE_DELETE(_roll);
	SAFE_DELETE(_run);
	SAFE_DELETE(_wait);
	SAFE_DELETE(_walk);
	SAFE_DELETE(_smile);

	SAFE_DELETE(_pet);
}

void Player::update()
{
	if(_info.isControl)
	_Istate->UpdateState();				//상태

	KeyInput();							//키 입력
	Move();								//이동
	Adjust();							//조정

	FrameUpdate();						//프레임
	TerrainStand();						//지형

	_pet->update(_info.x, _info.y);		//펫
}

void Player::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))		//디버깅용 렉트
	{
		Rectangle(getMapDC(), _info.rcAttack);	//공격 범위 렉트
		Rectangle(getMapDC(), _info.rcDamage);	//피격 범위 렉트
	}

	//맵 플래이어
	_info.img->alphaFrameRender(getMapDC(), _info.x - _info.img->getFrameWidth() / 2, _info.y - _info.img->getFrameHeight() / 2, _info.alpha);

	//미니맵 플래이어
	_info.iconImg->stRatioRender(getMinimapDC(), _info.x, _info.y - 50, 4, 4);

	//펫
	if(!_info.isDead)_pet->render();

	//빔
	if (_info.state == PS_BEAM) _info.beamImg->stRender(getMapDC(), _info.rcAttack.left, _info.rcAttack.top, _info.rcAttack.right - _info.rcAttack.left, _info.rcAttack.bottom - _info.rcAttack.top);
	if (_info.rollTimer <= 150 && UIMANAGER->GetIsActive() && _info.state != PS_ROLL) _info.countImg->aniRender(getMapDC(), _info.x - _info.countImg->getFrameWidth() / 2, _info.y - 100, _info.countAni);
}

void Player::Move()
{
	//하늘에 있을 때는 중력을 준다.
	if (_info.position == P_AIR) _info.jumpPower -= GRAVITY;

	//점프력만큼 올려준다. 
	xyMove(0, -_info.jumpPower);
}

void Player::KeyInput()
{
	//컨트롤 불가거나 죽거나 피격, 공격, 회피 시에는 키 입력을 받지 않는다.
	if (!_info.isControl || _info.isDead || _info.state == PS_DAMAGE || _info.state == PS_ATTACK || _info.state == PS_ROLL) return;

	// ========================= 방향 =========================
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT)) _info.dest = D_LEFT;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT)) _info.dest = D_RIGHT;

	// ========================= 점프와 낙하 =========================
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _info.position != P_AIR) { SetJumpPower(JUMPPOWER); SetState(PS_JUMP); }
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _info.position == P_PLATFORM) SetState(PS_FALLEN);
	
	// ========================= 공격 =========================
	if (KEYMANAGER->isOnceKeyDown('Z')) SetState(PS_ATTACK);
	if (KEYMANAGER->isOnceKeyDown('X')) SetState(PS_BEAM);
}

void Player::FrameUpdate()
{
	if (TIMEMANAGER->getWorldTime() - _info.redrawTimer > _info.redrawInterval)
	{
		_info.redrawTimer = TIMEMANAGER->getWorldTime();
		
		switch (_info.state)
		{
			case PS_IDLE:
			case PS_WALK:
			case PS_FALLEN:
			case PS_RUN:
			case PS_SMILE:
				FramePlay(0);
			break;
			case PS_JUMP:
			case PS_CLIMB:
				FramePlay(2);
			break;
			case PS_HANG:
			case PS_DIE:
			case PS_BEAM:
				FramePlay(1);
			break;
			case PS_ROLL:
			case PS_ATTACK:
			case PS_DAMAGE:
			case PS_WAIT:
				FramePlay(-1);
			break;
			default:
			break;
		}
	}
}

void Player::StageInit()
{
	_info.x = WINSIZEX / 6;
	_info.y = WINSIZEY / 2;
	_info.jumpPower = -1;

	_info.dest = D_RIGHT;
	SetState(PS_JUMP);
	_info.position = P_AIR;
	_info.isImmune = false;
	_info.alpha = 255;
	_info.gauge = _info.gaugeMax;
	_pet->StageInit();
}

void Player::SetState(PLAYERSTATE state)
{
	if (_info.state == state) return;	//이미 해당 상태면 변경하지 않는다.
	_info.state = state;				//현재 상태를 변경한다.

	//상태를 빠져 나온다.
	if (_Istate != NULL) _Istate->ExitState();

	//상태를 변경한다.
	switch (_info.state)
	{
		case PS_IDLE:	 _Istate = _idle;		break;
		case PS_WAIT:	 _Istate = _wait;		break;
		case PS_WALK:	 _Istate = _walk;		break;
		case PS_RUN:	 _Istate = _run;		break;
		case PS_ROLL:	 _Istate = _roll;		break;
		case PS_JUMP:	 _Istate = _jump;		break;
		case PS_FALLEN:	 _Istate = _fallen;		break;
		case PS_ATTACK:  _Istate = _attack;		break;
		case PS_BEAM:	 _Istate = _beam;		break;
		case PS_DAMAGE:  _Istate = _damage;		break;
		case PS_DIE:	 _Istate = _die;		break;
		case PS_HANG:	 _Istate = _hang;		break;
		case PS_CLIMB:	 _Istate = _climb;		break;
		case PS_SMILE:	 _Istate = _smile;		break;
		default: break;
	}

	_Istate->LinkPlayerAddress(this);
	_Istate->EnterState();
}

void Player::ImageRect(string strKey, int offsetX, int offsetY)
{
	_info.img = IMGMANAGER->findImage(strKey);											//이미지를 설정한다.
	if (_info.dest == D_RIGHT) _info.imageXIndex = 0;									//오른쪽 방향이면 0번 인덱스
	else if (_info.dest == D_LEFT) _info.imageXIndex = _info.img->getMaxFrameX();		//왼쪽 방향이면 마지막 인덱스
	_info.redrawTimer = _info.redrawInterval;											//바로 다시 그린다.

	_info.rcWidth = _info.img->getFrameWidth() - offsetX;								//렉트 크기를 이미지에 맞춘다.
	_info.rcHeight = _info.img->getFrameHeight() - offsetY;
	_info.rcDamage = RectMakeCenter(_info.x, _info.y, _info.rcWidth, _info.rcHeight);	//렉트를 다시 그린다.
}

void Player::FramePlay(int count)
{
	switch (count)
	{
	case -1:	//한 번 재생 후 기본
		if (_info.dest == D_RIGHT && _info.imageXIndex > _info.img->getMaxFrameX()) SetState(PS_IDLE);
		else if (_info.dest == D_LEFT && _info.imageXIndex < 0) SetState(PS_IDLE);
		break;
	case 1:		//한 번만 재생
		if (_info.dest == D_RIGHT && _info.imageXIndex > _info.img->getMaxFrameX()) _info.imageXIndex = _info.img->getMaxFrameX();
		else if (_info.dest == D_LEFT && _info.imageXIndex < 0) _info.imageXIndex = 0;
		break;
	case 0:		//무한 재생
		if (_info.dest == D_RIGHT && _info.imageXIndex > _info.img->getMaxFrameX()) _info.imageXIndex = 0;
		else if (_info.dest == D_LEFT && _info.imageXIndex < 0) _info.imageXIndex = _info.img->getMaxFrameX();
		break;
	case 2:		//특수 구간 재생
		if (_info.state == PS_JUMP)
		{
			if (_info.dest == D_RIGHT && _info.imageXIndex > _info.img->getMaxFrameX()) _info.imageXIndex = 3;
			else if (_info.dest == D_LEFT && _info.imageXIndex < 0) _info.imageXIndex = _info.img->getMaxFrameX() - 3;
		}
		break;
	}

	if (_info.imageXIndex < 0) _info.imageXIndex = 0;
	else if (_info.imageXIndex > _info.img->getMaxFrameX()) _info.imageXIndex = _info.img->getMaxFrameX();

	_info.img->setFrameY(_info.dest);
	_info.img->setFrameX(_info.imageXIndex);

	switch (_info.dest)
	{
	case D_RIGHT: ++_info.imageXIndex; break;
	case D_LEFT: --_info.imageXIndex; break;
	}
}

void Player::xyMove(int x, int y)
{
	_info.x += x;
	_info.y += y;

	if (_info.x - _info.rcWidth / 2 <= 0) { _info.x = _info.rcWidth / 2; return; }
	if (_info.x + _info.rcWidth / 2 >= getMemDCWidth()) { _info.x = getMemDCWidth() - _info.rcWidth / 2; }
	_info.rcDamage = RectMakeCenter(_info.x, _info.y, _info.rcWidth, _info.rcHeight);

}

void Player::AdjustGauge(int plus)
{
	_info.gauge += plus;
	if (_info.gauge >= _info.gaugeMax) _info.gauge = _info.gaugeMax;
	if (_info.gauge <= 0) _info.gauge = 0;
}

void Player::AdjustBeam(int plus)
{
	if (_info.beam >= 100) _info.beam = 100;
	if (_info.beam <= 0) _info.beam = 0;
	_info.beam += plus;
}

void Player::AdjustAttackRect(bool rect)
{
	if (rect)
	{
		if (_info.state == PS_ATTACK) _info.rcAttack = RectMakeCenter(_info.x, _info.y, _info.rcWidth * 2, _info.rcHeight);
		else if (_info.state == PS_BEAM)
		{
			if (_info.dest == D_RIGHT) _info.rcAttack = { (int)(_info.x + _info.rcWidth / 2), (int)(_info.y - _info.rcHeight / 2 + 20), (int)(_info.x + _info.rcWidth / 2 + _info.rcWidth * 4 * _info.beam / 100), (int)(_info.y - _info.rcHeight / 2 + _info.rcHeight - 20) };
			else _info.rcAttack = { (int)(_info.x - _info.rcWidth / 2 - _info.rcWidth * 4 * _info.beam / 100), (int)(_info.y - _info.rcHeight / 2 + 20), (int)(_info.x - _info.rcWidth / 2) , (int)(_info.y - _info.rcHeight / 2 + _info.rcHeight - 20) };
		}
	}
	else _info.rcAttack = { -WINSIZEX,-WINSIZEX,-WINSIZEX,-WINSIZEX };
}

void Player::Damage(int dmg, DEST dest, float jump)
{
	if (_info.isImmune || _info.state == PS_ROLL || _info.state == PS_DAMAGE || _info.state == PS_DIE) return;
	SetState(PS_DAMAGE);

	CAMERAMANAGER->Shake(45, 1, 30, 5, -1);
	EFFECTMANAGER->play("star", _info.x, _info.y - 50);
	if (dest != D_NONE) _info.dest = dest;
	switch (_info.dest)
	{
		case D_RIGHT: _info.x -= 50; 	break;
		case D_LEFT: _info.x += 50;		break;
	}
	if (_info.position != P_AIR)
	{
		_info.jumpPower = jump;
		_info.position = P_AIR;
	}
	_info.life -= dmg;
	if (_info.life < 0)  _info.life = 0;
}

void Player::Adjust()
{
	AdjustGauge(1);
	_info.countAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	
	++_info.rollTimer;

	if (_info.isImmune)	_info.alpha = (unsigned int)(255 - _info.immuneTimer);
	if (--_info.immuneTimer < 0) { SetImmune(false); };
}



void Player::AddItem(ITEMTYPE type)
{
	switch (type)
	{
	case I_LEAF:
		++_info.life;
		if (_info.life > _info.maxLife) _info.life = _info.maxLife;
		break;
	case I_BUBBLE:
		_info.gauge += _info.gaugeMax / 4;
		if (_info.gauge > _info.gaugeMax) _info.gauge = _info.gaugeMax;
		break;
	case I_CRYSTAL:
		++_info.crystal;
		break;
	default:
		break;
	}
}

#pragma region SAVELOAD
void Player::SaveData()
{
	vector<string> vStr;
	SAVELOADMANAGER->pushData(&vStr, _info.x);
	SAVELOADMANAGER->pushData(&vStr, _info.y);
	SAVELOADMANAGER->pushData(&vStr, _info.position);
	SAVELOADMANAGER->pushData(&vStr, _info.speed);
	SAVELOADMANAGER->pushData(&vStr, _info.jumpPower);
	SAVELOADMANAGER->pushData(&vStr, _info.isImmune);
	SAVELOADMANAGER->pushData(&vStr, _info.alpha);
	SAVELOADMANAGER->pushData(&vStr, _info.isControl);
	SAVELOADMANAGER->pushData(&vStr, _info.dest);
	SAVELOADMANAGER->pushData(&vStr, _info.state);
	SAVELOADMANAGER->pushData(&vStr, _info.gauge);
	SAVELOADMANAGER->pushData(&vStr, _info.life);
	SAVELOADMANAGER->pushData(&vStr, _info.crystal);
	SAVELOADMANAGER->pushData(&vStr, _stageM->getCurrentStage());
	TXTDATA->txtSave("SAVEDATA.txt", vStr);
}

void Player::LoadData()
{
	vector<string> vStr = TXTDATA->txtLoad("SAVEDATA.txt");
	if (atoi(vStr[13].c_str()) != _stageM->getCurrentStage()) _stageM->SetStage((STAGETYPE)atoi(vStr[13].c_str()));
	_info.x = atoi(vStr[0].c_str());
	_info.y = atoi(vStr[1].c_str());
	_info.position = (POSITION)atoi(vStr[2].c_str());
	_info.speed = atoi(vStr[3].c_str());
	_info.jumpPower = atoi(vStr[4].c_str());
	_info.isImmune = atoi(vStr[5].c_str());
	_info.alpha = atoi(vStr[6].c_str());
	_info.isControl = atoi(vStr[7].c_str());
	_info.dest = (DEST)atoi(vStr[8].c_str());
	SetState(PS_IDLE);
	_info.gauge = atoi(vStr[10].c_str());
	_info.life = atoi(vStr[11].c_str());
	_info.crystal = atoi(vStr[12].c_str());
}
#pragma endregion

void Player::TerrainStand()
{
	// ============================ 땅에 서 있는다. ============================
	for (int i = 0; i < (_stageM->getStage()->getvTerrain()).size(); i++)
	{
		if ((_stageM->getStage()->getvTerrain())[i]->getPosition() == P_CLIFF) continue;

		//땅에서 좌우로 떨어지면 공중이다.
		if (_info.y == (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.top - 1 - (_info.rcDamage.bottom - _info.rcDamage.top) / 2 &&
			(_info.x > (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.right || _info.x < (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.left)
			&& (_info.x < (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.right + _info.rcWidth && _info.x >(_stageM->getStage()->getvTerrain())[i]->getCollision().rc.left - _info.rcWidth))
			_info.position = P_AIR;

		//땅 위에서 아래키를 누르면 떨어진다.
		if (_info.state == PS_FALLEN && _info.jumpPower > -JUMPPOWER / 2) return;

		//땅과 충돌한다.
		if (UDCollision((_stageM->getStage()->getvTerrain())[i]->getCollision()) && _info.jumpPower <= 0 &&
			(_info.rcDamage.bottom < (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.top + 10 || _info.jumpPower < -JUMPPOWER * 1.5)
			&& (_info.x < (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.right && _info.x >(_stageM->getStage()->getvTerrain())[i]->getCollision().rc.left)
			&& _info.rcDamage.top < (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.top)
		{
			xyMove(0, -((_stageM->getStage()->getvTerrain())[i]->getCollision().tempRc.bottom - (_stageM->getStage()->getvTerrain())[i]->getCollision().tempRc.top));
			_info.y = (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.top - (_info.rcDamage.bottom - _info.rcDamage.top) / 2;	//위치 보정

			if (_info.y == (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.top - (_info.rcDamage.bottom - _info.rcDamage.top) / 2)
			{
				_info.jumpPower = 0;		//점프력 0
				_info.position = (_stageM->getStage()->getvTerrain())[i]->getPosition();	//위치 설정
				if (_info.state == PS_JUMP || _info.state == PS_FALLEN) SetState(PS_IDLE);	//상태 설정
				_info.y = (_stageM->getStage()->getvTerrain())[i]->getCollision().rc.top - 1 - (_info.rcDamage.bottom - _info.rcDamage.top) / 2;	//위치 완전 보정
			}
		}
	}
}

#pragma region COLLISION
bool Player::UDCollision(tagCollision & col)
{
	if (IntersectRect(&col.tempRc, &col.rc, &_info.rcDamage))
	{
		if (col.tempRc.right - col.tempRc.left > col.tempRc.bottom - col.tempRc.top
			&& (_info.rcDamage.bottom > col.rc.bottom || _info.rcDamage.top < col.rc.top)) return true;
	}
	return false;
}

bool Player::LRCollision(tagCollision & col)
{
	if (IntersectRect(&col.tempRc, &col.rc, &_info.rcDamage))
	{
		if (col.tempRc.right - col.tempRc.left < col.tempRc.bottom - col.tempRc.top
			&& (_info.rcDamage.right > col.rc.right || _info.rcDamage.left < col.rc.left)) return true;
	}
	return false;
}

bool Player::Collision(tagCollision & col)
{
	if (IntersectRect(&col.tempRc, &col.rc, &_info.rcDamage)) return false;
}
#pragma endregion
