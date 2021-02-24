#include "stdafx.h"
#include "StageManager.h"
#include "Player.h"

#include "EasyStage.h"
#include "NormalStage.h"
#include "BossStage.h"
#include "HardStage.h"

HRESULT StageManager::init()
{
	// =============== 스테이지 이미지 초기화 ===============
	//뒷 배경
	IMGMANAGER->addImage("background1", "image/backGround1.bmp", 1600, 800, false, MAGENTA);
	IMGMANAGER->addImage("background2", "image/backGround2.bmp", 1280, 1000, false, MAGENTA);
	IMGMANAGER->addImage("background3", "image/backGround3.bmp", 960, 720, false, MAGENTA);
	IMGMANAGER->addFrameImage("background4", "image/backGround4.bmp", 2560, 720, 2, 1, false, MAGENTA);
	IMGMANAGER->addImage("background5", "image/backGround5.bmp", 2328, 888, false, MAGENTA);
	IMGMANAGER->addImage("background6", "image/backGround6.bmp", 1500, 285, false, MAGENTA);
	IMGMANAGER->addImage("background7", "image/backGround7.bmp", 1280, 1280, false, MAGENTA);
	IMGMANAGER->addFrameImage("background8", "image/backGround8.bmp", 2560, 1500, 2, 1, false, MAGENTA);

	//중간 배경
	IMGMANAGER->addImage("middleground1", "image/middleGround1.bmp", 640, 380, true, MAGENTA);
	IMGMANAGER->addImage("middleground2", "image/middleGround2.bmp", 640, 306, true, MAGENTA);
	IMGMANAGER->addImage("middleground3", "image/middleGround3.bmp", 768, 340, true, MAGENTA);
	IMGMANAGER->addImage("middleground4", "image/middleGround4.bmp", 800, 780, true, MAGENTA);
	IMGMANAGER->addImage("middleground5", "image/middleGround5.bmp", 640, 720, true, MAGENTA);
	IMGMANAGER->addImage("middleground6", "image/middleGround6.bmp", 640, 720, true, MAGENTA);
	IMGMANAGER->addImage("middleground7", "image/middleGround7.bmp", 640, 720, true, MAGENTA);
	IMGMANAGER->addImage("middleground8", "image/middleGround8.bmp", 150, 340, true, MAGENTA);

	//땅
	IMGMANAGER->addImage("ground0", "image/ground_left.bmp", 96, 120, true, MAGENTA);
	IMGMANAGER->addImage("ground1", "image/ground_middle.bmp", 384, 120, true, MAGENTA);
	IMGMANAGER->addImage("ground2", "image/ground_right.bmp", 96, 120, true, MAGENTA);

	//풀
	IMGMANAGER->addImage("grass0", "image/grass_left.bmp", 96, 120, true, MAGENTA);
	IMGMANAGER->addImage("grass1", "image/grass_middle.bmp", 384, 120, true, MAGENTA);
	IMGMANAGER->addImage("grass2", "image/grass_right.bmp", 96, 120, true, MAGENTA);

	//도로
	IMGMANAGER->addImage("road0", "image/road_left.bmp", 96, 120, true, MAGENTA);
	IMGMANAGER->addImage("road1", "image/road_middle.bmp", 384, 120, true, MAGENTA);
	IMGMANAGER->addImage("road2", "image/road_right.bmp", 96, 120, true, MAGENTA);

	//오브젝트
	IMGMANAGER->addFrameImage("rock", "image/object_rock.bmp", 912, 256, 3, 1, true, MAGENTA);
	IMGMANAGER->addFrameImage("tree1", "image/object_tree1.bmp", 604, 280, 2, 1, true, MAGENTA);
	IMGMANAGER->addFrameImage("tree2", "image/object_tree2.bmp", 900, 346, 2, 1, true, MAGENTA);
	IMGMANAGER->addFrameImage("tree3", "image/object_tree2.bmp", 768, 288, 2, 1, true, MAGENTA);
	IMGMANAGER->addFrameImage("tree4", "image/object_tree4.bmp", 512, 128, 2, 1, true, MAGENTA);
	IMGMANAGER->addFrameImage("cloud", "image/object_cloud.bmp", 1200, 150, 4, 1, true, MAGENTA);

	//총알
	IMGMANAGER->addImage("bullet1", "image/bullet1.bmp", 32, 32, true, MAGENTA, true);

	//아이템
	IMGMANAGER->addFrameImage("leaf", "image/item_leaf.bmp", 456, 40, 12, 1, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("crystal", "image/item_crystal.bmp", 132, 42, 6, 1, true, MAGENTA, true);
	IMGMANAGER->addFrameImage("bubble", "image/item_bubble.bmp", 160, 32, 5, 1, true, MAGENTA, true);

	//이펙트
	EFFECTMANAGER->addEffect("bomb", "effect_bomb.bmp", 640, 64, 64, 64, 1.0f, 0.5f, 20);
	EFFECTMANAGER->addEffect("explosion", "effect_explosion.bmp", 832, 62, 32, 62, 1.0f, 0.5f, 20);
	EFFECTMANAGER->addEffect("star", "effect_star.bmp", 300, 50, 50, 50, 1.0f, 0.2f, 20);

	_easy = new EasyStage;
	_normal = new NormalStage;
	_hard = new HardStage;
	_boss = new BossStage;

	SetStage(ST_EASY);

	return S_OK;
}

void StageManager::release()
{
	SAFE_DELETE(_easy);
	SAFE_DELETE(_normal);
	SAFE_DELETE(_hard);
	SAFE_DELETE(_boss);
}

void StageManager::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F3))	//디버깅용. F3 누를 시 다음 스테이지.
	{
		if (_currentStage != ST_BOSS) SetStage((STAGETYPE)(_currentStage + 1));
		else SetStage(ST_EASY);
	}

	_stage->update();

	//보스 제외 스테이지 클리어시 다음 스테이지
	if (_stage->getIsClear() && _currentStage != ST_BOSS) { SetStage((STAGETYPE)(_currentStage + 1)); }
}

void StageManager::render()
{
	_stage->render();
}

void StageManager::SetStage(STAGETYPE type)
{
	_currentStage = type;

	if (_stage != NULL) _stage->release();

	switch (_currentStage)
	{
		case ST_EASY:
		{
			_stage = _easy;
		}
		break;
		case ST_NORMAL:
		{
			_stage = _normal;
		}
		break;
		case ST_HARD:
		{
			_stage = _hard;
		}
		break;
		case ST_BOSS:
		{
			_stage = _boss;
		}
		break;
	}
	_stage->SetPlayerAddressLink(_player);
	_stage->init();
	UIMANAGER->SetStageAddressLink(_stage);
}
