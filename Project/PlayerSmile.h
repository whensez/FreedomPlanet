#pragma once
#include "IPlayerState.h"
class PlayerSmile :
	public IPlayerState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();

};

