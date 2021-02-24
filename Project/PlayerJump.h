#pragma once
#include "IPlayerState.h"
class PlayerJump :
	public IPlayerState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

