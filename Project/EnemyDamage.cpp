#include "stdafx.h"
#include "EnemyDamage.h"
#include "Enemy.h"

void EnemyDamage::EnterState()
{
	_thisObj->SetImage();

}

void EnemyDamage::UpdateState()
{
	_thisObj->jump(3);
	_thisObj->damage();
}

void EnemyDamage::ExitState()
{
}
