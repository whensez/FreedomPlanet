#include "stdafx.h"
#include "PlayerWalk.h"
#include "Player.h"
#include "Enums.h"
void PlayerWalk::EnterState()
{
	_thisObj->ImageRect("milla_walk", 20, 10);
}

void PlayerWalk::UpdateState()
{
	if (_thisObj->GetInfo().jumpPower < -1.5) _thisObj->SetState(PS_JUMP);

	//Ű�� ������ ���� ������ �⺻ ����
	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT)) _thisObj->SetState(PS_IDLE);

	//SHIFT�� ������ �޸���
	if (KEYMANAGER->isStayKeyDown(VK_SHIFT)) _thisObj->SetState(PS_RUN);

	//C�� ������ ������
	if (KEYMANAGER->isOnceKeyDown('C') && _thisObj->GetInfo().rollTimer > 150) _thisObj->SetState(PS_ROLL);

	//���⿡ ���� �̵�
	if (_thisObj->GetInfo().dest == D_LEFT) _thisObj->xyMove(-_thisObj->GetInfo().speed, 0);
	else if (_thisObj->GetInfo().dest == D_RIGHT) _thisObj->xyMove(_thisObj->GetInfo().speed, 0);
}

void PlayerWalk::ExitState()
{
}
