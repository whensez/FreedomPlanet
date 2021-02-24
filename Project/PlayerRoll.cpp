#include "stdafx.h"
#include "PlayerRoll.h"
#include "Player.h"
#include "Enums.h"

void PlayerRoll::EnterState()
{
	_thisObj->ImageRect("milla_roll", 20, 10);
	_thisObj->SetAlpha(150);
	_thisObj->SetImmune(true);
}


void PlayerRoll::UpdateState()
{
	if (_thisObj->GetInfo().jumpPower < -0.5) _thisObj->SetState(PS_JUMP);

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_thisObj->xyMove(-_thisObj->GetInfo().speed * 1.2, 0);
		if (_thisObj->GetInfo().dest != D_LEFT)_thisObj->GetInfo().imageXIndex = _thisObj->GetInfo().img->getMaxFrameX() - _thisObj->GetInfo().imageXIndex;
		_thisObj->GetInfo().dest = D_LEFT;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_thisObj->xyMove(+_thisObj->GetInfo().speed * 1.2, 0);
		if (_thisObj->GetInfo().dest != D_RIGHT)_thisObj->GetInfo().imageXIndex = _thisObj->GetInfo().img->getMaxFrameX() - _thisObj->GetInfo().imageXIndex;
		_thisObj->GetInfo().dest = D_RIGHT;
	}
}

void PlayerRoll::ExitState()
{
	_thisObj->SetAlpha(255);
	_thisObj->SetImmune(false);
	_thisObj->SetRollTimer(0);
}
