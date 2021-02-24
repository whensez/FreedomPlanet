#include "stdafx.h"
#include "PlayerRun.h"
#include "Player.h"
#include "Enums.h"
void PlayerRun::EnterState()
{
	_thisObj->ImageRect("milla_run", 20, 10);
}

void PlayerRun::UpdateState()
{
	if (_thisObj->GetInfo().jumpPower < 0) _thisObj->SetState(PS_JUMP);

	//키를 누르고 있지 않으면 기본 상태
	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT)) _thisObj->SetState(PS_IDLE);

	//SHIFT를 떼면 걷기
	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT)) _thisObj->SetState(PS_WALK);

	if (_thisObj->GetInfo().gauge <= 5)
	{
		//방향에 따른 이동
		if (_thisObj->GetInfo().dest == D_LEFT) _thisObj->xyMove(-_thisObj->GetInfo().speed * 1.0, 0);
		else if (_thisObj->GetInfo().dest == D_RIGHT) _thisObj->xyMove(_thisObj->GetInfo().speed * 1.0, 0);
	}
	else
	{
		_thisObj->AdjustGauge(-5);
		//방향에 따른 이동
		if (_thisObj->GetInfo().dest == D_LEFT) _thisObj->xyMove(-_thisObj->GetInfo().speed * 1.7, 0);
		else if (_thisObj->GetInfo().dest == D_RIGHT) _thisObj->xyMove(_thisObj->GetInfo().speed * 1.7, 0);
	}
}

void PlayerRun::ExitState()
{
}
