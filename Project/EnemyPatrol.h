#pragma once
#include "IEnemyState.h"
class EnemyPatrol : public IEnemyState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

