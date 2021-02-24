#include "stdafx.h"
#include "EnemyAttack.h"
#include "Enemy.h"
#include "Player.h"

void EnemyAttack::EnterState()
{
	_thisObj->SetImage();
	_thisObj->setIsAttack(false);
}

void EnemyAttack::UpdateState()
{
	if (_thisObj->getPlayerAddress()->GetInfo().x < _thisObj->getX()) _thisObj->setDest(D_LEFT);
	else if (_thisObj->getPlayerAddress()->GetInfo().x > _thisObj->getX()) _thisObj->setDest(D_RIGHT);
	_thisObj->attack();
}

void EnemyAttack::ExitState()
{
}
