#pragma once
#include "IEnemyState.h"
class EnemyDie : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();

};

