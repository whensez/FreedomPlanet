#include "stdafx.h"
#include "PlayerBeam.h"

#include "Player.h"
#include "Enums.h"
void PlayerBeam::EnterState()
{
	_thisObj->ImageRect("milla_beam", 20, 10);
	_starTimer = 0;
}

void PlayerBeam::UpdateState()
{
	_thisObj->AdjustGauge(-5);
	_thisObj->AdjustBeam(3);
	_thisObj->AdjustAttackRect(true);

	if (TIMEMANAGER->getWorldTime() - _starTimer > 0.05)
	{
		_starTimer = TIMEMANAGER->getWorldTime();
		if (_thisObj->GetInfo().dest == D_RIGHT) EFFECTMANAGER->play("greenStar", _thisObj->GetAttackRect().right - RND->getInt(30), _thisObj->GetInfo().y + RND->getFromIntTo(-30, 30));
		if (_thisObj->GetInfo().dest == D_LEFT) EFFECTMANAGER->play("greenStar", _thisObj->GetAttackRect().left + RND->getInt(30), _thisObj->GetInfo().y + RND->getFromIntTo(-30, 30));
	}
	if (KEYMANAGER->isOnceKeyUp('X') || _thisObj->GetInfo().gauge <= 0) _thisObj->SetState(PS_IDLE);
}

void PlayerBeam::ExitState()
{
	if (_thisObj->GetInfo().dest == D_RIGHT) EFFECTMANAGER->play("green", _thisObj->GetAttackRect().right, _thisObj->GetInfo().y);
	if (_thisObj->GetInfo().dest == D_LEFT) EFFECTMANAGER->play("green", _thisObj->GetAttackRect().left, _thisObj->GetInfo().y);

	_thisObj->AdjustBeam(-100);
	_thisObj->AdjustAttackRect(false);
}
