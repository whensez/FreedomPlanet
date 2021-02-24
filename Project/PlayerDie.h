#pragma once
#include "IPlayerState.h"
class PlayerDie :
	public IPlayerState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

