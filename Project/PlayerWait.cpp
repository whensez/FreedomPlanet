#include "stdafx.h"
#include "PlayerWait.h"
#include "Player.h"
#include "Enums.h"
void PlayerWait::EnterState()
{
	switch (RND->getInt(3))
	{
	case 0:
		_thisObj->ImageRect("milla_wait1", 20, 10);
		break;
	case 1:
		_thisObj->ImageRect("milla_wait2", 20, 10);
		break;
	case 2:
		_thisObj->ImageRect("milla_wait3", 20, 10);
		break;
	default:
		break;
	}
}

void PlayerWait::UpdateState()
{
	if (_thisObj->GetInfo().position == P_GROUND || _thisObj->GetInfo().position == P_PLATFORM)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))	//오른쪽으로 이동
		{
			_thisObj->GetInfo().dest = D_RIGHT;
			_thisObj->SetState(PS_WALK);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))		//왼쪽으로 이동
		{
			_thisObj->GetInfo().dest = D_LEFT;
			_thisObj->SetState(PS_WALK);
		}
	}
}

void PlayerWait::ExitState()
{
}
