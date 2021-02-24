#pragma once
#include "IPlayerState.h"
class PlayerClimb :
	public IPlayerState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();

};

