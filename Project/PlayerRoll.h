#pragma once
#include "IPlayerState.h"
class PlayerRoll :
	public IPlayerState
{


public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

