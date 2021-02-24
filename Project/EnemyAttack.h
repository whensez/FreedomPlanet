#pragma once
#include "IEnemyState.h"
class EnemyAttack : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();

};

