#pragma once
#include "IPlayerState.h"
class PlayerFallen :
	public IPlayerState
{


public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

