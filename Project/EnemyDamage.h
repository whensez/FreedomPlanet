#pragma once
#include "IEnemyState.h"
class EnemyDamage :
	public IEnemyState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();

};

