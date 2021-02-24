#pragma once
#include "IEnemyState.h"
class Enemy;


class EnemyIdle : public IEnemyState
{
	
public:
	EnemyIdle() {}
	~EnemyIdle() {}

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();

};

