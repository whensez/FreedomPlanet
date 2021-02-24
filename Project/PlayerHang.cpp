#include "stdafx.h"
#include "PlayerHang.h"

#include "Player.h"

void PlayerHang::EnterState()
{
	_thisObj->ImageRect("milla_hang", 20, 10);
}

void PlayerHang::UpdateState()
{
}

void PlayerHang::ExitState()
{
}
