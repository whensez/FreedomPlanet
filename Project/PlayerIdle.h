#pragma once
#include "IPlayerState.h"
class PlayerIdle : public IPlayerState
{
private:
	float idleTimer;

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

