#include "stdafx.h"
#include "PlayerAttack.h"

#include "Player.h"
#include "Enums.h"
void PlayerAttack::EnterState()
{
	_thisObj->SetPosition(P_AIR);
	_thisObj->SetJumpPower(JUMPPOWER / 3);
	_thisObj->ImageRect("milla_attack", 20, 10);
}

void PlayerAttack::UpdateState()
{
	if ((_thisObj->GetInfo().dest == D_RIGHT && _thisObj->GetInfo().imageXIndex == _thisObj->GetInfo().img->getMaxFrameX() - 3)
		|| (_thisObj->GetInfo().dest == D_LEFT && _thisObj->GetInfo().imageXIndex == 3))
	{
		_thisObj->AdjustAttackRect(true);
		EFFECTMANAGER->play("green", _thisObj->GetAttackRect().right, _thisObj->GetInfo().y);
		EFFECTMANAGER->play("green", _thisObj->GetAttackRect().left, _thisObj->GetInfo().y);
	}
	else _thisObj->AdjustAttackRect(false);
}

void PlayerAttack::ExitState()
{
	_thisObj->AdjustAttackRect(false);
}
