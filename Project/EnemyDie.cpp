#include "stdafx.h"
#include "EnemyDie.h"
#include "Enemy.h"

void EnemyDie::EnterState()
{
	_thisObj->SetImage();

}

void EnemyDie::UpdateState()
{

	_thisObj->die();
}

void EnemyDie::ExitState()
{
}
