#include "stdafx.h"
#include "PlayerDie.h"

#include "Player.h"

#include "Enums.h"
void PlayerDie::EnterState()
{
	_thisObj->SetImmune(false);
	_thisObj->SetAlpha(255);
	_thisObj->ImageRect("milla_die", 20, 10);
}


void PlayerDie::UpdateState()
{
	if ((_thisObj->GetInfo().dest == D_RIGHT && _thisObj->GetInfo().imageXIndex == _thisObj->GetInfo().img->getMaxFrameX())
		|| (_thisObj->GetInfo().dest == D_LEFT && _thisObj->GetInfo().imageXIndex == 0))
	{
		_thisObj->SetDie(true);
	}


}

void PlayerDie::ExitState()
{
}
