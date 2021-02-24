#include "stdafx.h"
#include "PlayerJump.h"
#include "Player.h"
#include "Enums.h"
void PlayerJump::EnterState()
{
	_thisObj->SetPosition(P_AIR);					//하늘에 있다고 한다.
	_thisObj->ImageRect("milla_jump", 20, 10);
}


void PlayerJump::UpdateState()
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

void PlayerJump::ExitState()
{
}
