#pragma once
#include "IPlayerState.h"
class PlayerWalk :
	public IPlayerState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

