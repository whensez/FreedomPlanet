#include "stdafx.h"
#include "EnemyIdle.h"
#include "Enemy.h"

void EnemyIdle::EnterState()
{
	_thisObj->SetImage();

}

void EnemyIdle::UpdateState()
{
	if (_thisObj->getGoRight()) { _thisObj->xyMove(_thisObj->getSpeed(), 0); _thisObj->setDest(D_RIGHT); }
	else { _thisObj->xyMove(-_thisObj->getSpeed(), 0); _thisObj->setDest(D_LEFT); }

	if (_thisObj->getX() >= _thisObj->getRcRange().right ||
		_thisObj->getX() >= CAMERAMANAGER->GetMapXSize()) { _thisObj->setGoRight(false); }
	if (_thisObj->getX() <= _thisObj->getRcRange().left) { _thisObj->setGoRight(true); }
}

void EnemyIdle::ExitState()
{
}
