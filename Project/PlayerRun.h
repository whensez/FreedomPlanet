#pragma once
#include "IPlayerState.h"
class PlayerRun :
	public IPlayerState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

