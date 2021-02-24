#include "stdafx.h"
#include "PlayerFallen.h"

#include "Player.h"
#include "Enums.h"

void PlayerFallen::EnterState()
{
	_thisObj->SetPosition(P_AIR);
	_thisObj->SetJumpPower(-JUMPPOWER / 3);
	_thisObj->ImageRect("milla_fallen", 20, 10);
}

void PlayerFallen::UpdateState()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))		//오른쪽으로 이동
	{
		_thisObj->xyMove(_thisObj->GetInfo().speed * 0.7, 0);
		if (_thisObj->GetInfo().dest != D_RIGHT)_thisObj->GetInfo().imageXIndex = _thisObj->GetInfo().img->getMaxFrameX() - _thisObj->GetInfo().imageXIndex;
		_thisObj->GetInfo().dest = D_RIGHT;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))		//왼쪽으로 이동
	{
		_thisObj->xyMove(-_thisObj->GetInfo().speed * 0.7, 0);
		if (_thisObj->GetInfo().dest != D_LEFT)_thisObj->GetInfo().imageXIndex = _thisObj->GetInfo().img->getMaxFrameX() - _thisObj->GetInfo().imageXIndex;
		_thisObj->GetInfo().dest = D_LEFT;

	}
}

void PlayerFallen::ExitState()
{
}
