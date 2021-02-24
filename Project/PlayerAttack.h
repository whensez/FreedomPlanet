#pragma once
#include "IPlayerState.h"
class PlayerAttack :
	public IPlayerState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

