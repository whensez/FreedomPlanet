#include "stdafx.h"
#include "PlayerIdle.h"

#include "Player.h"
#include "Enums.h"
void PlayerIdle::EnterState()
{
	idleTimer = TIMEMANAGER->getWorldTime();
	_thisObj->ImageRect("milla_idle", 20, 10);
}


void PlayerIdle::UpdateState()
{
	if (TIMEMANAGER->getWorldTime() - idleTimer > 3.0f) _thisObj->SetState(PS_WAIT);
	
	if (_thisObj->GetInfo().jumpPower < -0.5) _thisObj->SetState(PS_JUMP);

	if (_thisObj->GetInfo().position == P_GROUND || _thisObj->GetInfo().position == P_PLATFORM)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))	//오른쪽으로 이동
		{
			{
				_thisObj->GetInfo().dest = D_RIGHT;
				_thisObj->SetState(PS_WALK);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))		//왼쪽으로 이동
		{
			{
				_thisObj->GetInfo().dest = D_LEFT;
				_thisObj->SetState(PS_WALK);
			}
		}
	}
}

void PlayerIdle::ExitState()
{
}
