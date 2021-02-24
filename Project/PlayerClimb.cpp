#include "stdafx.h"
#include "PlayerClimb.h"

#include "Player.h"

void PlayerClimb::EnterState()
{
	_thisObj->ImageRect("milla_climb", 20, 10);
}

void PlayerClimb::UpdateState()
{

}

void PlayerClimb::ExitState()
{
}
