#include "stdafx.h"
#include "PlayerJump.h"
#include "Player.h"
#include "Enums.h"
void PlayerJump::EnterState()
{
	_thisObj->SetPosition(P_AIR);					//�ϴÿ� �ִٰ� �Ѵ�.
	_thisObj->ImageRect("milla_jump", 20, 10);
}


void PlayerJump::UpdateState()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))		//���������� �̵�
	{
		_thisObj->xyMove(_thisObj->GetInfo().speed * 0.7, 0);
		if (_thisObj->GetInfo().dest != D_RIGHT)_thisObj->GetInfo().imageXIndex = _thisObj->GetInfo().img->getMaxFrameX() - _thisObj->GetInfo().imageXIndex;
		_thisObj->GetInfo().dest = D_RIGHT;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))		//�������� �̵�
	{
		_thisObj->xyMove(-_thisObj->GetInfo().speed * 0.7, 0);
		if (_thisObj->GetInfo().dest != D_LEFT)_thisObj->GetInfo().imageXIndex = _thisObj->GetInfo().img->getMaxFrameX() - _thisObj->GetInfo().imageXIndex;
		_thisObj->GetInfo().dest = D_LEFT;
	}
}

void PlayerJump::ExitState()
{
}
