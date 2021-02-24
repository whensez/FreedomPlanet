#include "stdafx.h"
#include "PlayerDamage.h"

#include "Player.h"

void PlayerDamage::EnterState()
{
	_thisObj->ImageRect("milla_damage", 20, 10);
}


void PlayerDamage::UpdateState()
{
}

void PlayerDamage::ExitState()
{
	_thisObj->SetAlpha(150);
	_thisObj->SetImmune(true);
	if (_thisObj->GetInfo().life <= 0)_thisObj->SetState(PS_DIE);
}
