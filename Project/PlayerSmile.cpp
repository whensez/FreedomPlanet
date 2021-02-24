#include "stdafx.h"
#include "PlayerSmile.h"
#include "Player.h"
#include "Enums.h"
void PlayerSmile::EnterState()
{
	_thisObj->ImageRect("milla_smile", 20, 10);
}


void PlayerSmile::UpdateState()
{
}

void PlayerSmile::ExitState()
{
}
