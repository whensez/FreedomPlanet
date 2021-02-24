#pragma once
#include "IPlayerState.h"
class PlayerDamage :
	public IPlayerState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

