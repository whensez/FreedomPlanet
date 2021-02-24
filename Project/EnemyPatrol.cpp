#include "stdafx.h"
#include "EnemyPatrol.h"
#include "Enemy.h"
#include "Player.h"

void EnemyPatrol::EnterState()
{
	_thisObj->SetImage();

	_thisObj->getSpeed() = _thisObj->getOriginSpeed() + _thisObj->getOriginSpeed()*1.3;
}

void EnemyPatrol::UpdateState()
{
	//플래이어가 공중이 아닌데 더 위에 있으면 점프한다.
	if (_thisObj->getPlayerAddress()->GetInfo().y < _thisObj->getY() - 30 &&
		_thisObj->getPlayerAddress()->GetInfo().position !=P_AIR
		&&abs(_thisObj->getPlayerAddress()->GetInfo().x - _thisObj->getX())
		< (_thisObj->getRcDamage().right - _thisObj->getRcDamage().left))
	{
		_thisObj->jump(7);
	}

	//플래이어와 충분히 가까우면 다가가지 않는다.
	if (abs(_thisObj->getPlayerAddress()->GetInfo().x - _thisObj->getX()) < (_thisObj->getRcDamage().right - _thisObj->getRcDamage().left)/2) return;

	//플래이어가 있는 방향으로 다가간다.
	if (_thisObj->getPlayerAddress()->GetInfo().x < _thisObj->getX()) _thisObj->setDest(D_LEFT);
	else if (_thisObj->getPlayerAddress()->GetInfo().x > _thisObj->getX()) _thisObj->setDest(D_RIGHT);
	_thisObj->xyMove(cosf(getAngle(_thisObj->getX(), 0, _thisObj->getPlayerAddress()->GetInfo().x, 0))*_thisObj->getSpeed(), 0);

}

void EnemyPatrol::ExitState()
{
	_thisObj->getSpeed() = _thisObj->getOriginSpeed();

}
