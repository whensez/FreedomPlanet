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
	//�÷��̾ ������ �ƴѵ� �� ���� ������ �����Ѵ�.
	if (_thisObj->getPlayerAddress()->GetInfo().y < _thisObj->getY() - 30 &&
		_thisObj->getPlayerAddress()->GetInfo().position !=P_AIR
		&&abs(_thisObj->getPlayerAddress()->GetInfo().x - _thisObj->getX())
		< (_thisObj->getRcDamage().right - _thisObj->getRcDamage().left))
	{
		_thisObj->jump(7);
	}

	//�÷��̾�� ����� ������ �ٰ����� �ʴ´�.
	if (abs(_thisObj->getPlayerAddress()->GetInfo().x - _thisObj->getX()) < (_thisObj->getRcDamage().right - _thisObj->getRcDamage().left)/2) return;

	//�÷��̾ �ִ� �������� �ٰ�����.
	if (_thisObj->getPlayerAddress()->GetInfo().x < _thisObj->getX()) _thisObj->setDest(D_LEFT);
	else if (_thisObj->getPlayerAddress()->GetInfo().x > _thisObj->getX()) _thisObj->setDest(D_RIGHT);
	_thisObj->xyMove(cosf(getAngle(_thisObj->getX(), 0, _thisObj->getPlayerAddress()->GetInfo().x, 0))*_thisObj->getSpeed(), 0);

}

void EnemyPatrol::ExitState()
{
	_thisObj->getSpeed() = _thisObj->getOriginSpeed();

}
