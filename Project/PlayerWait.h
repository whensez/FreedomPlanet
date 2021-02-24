#pragma once
#include "IPlayerState.h"
class PlayerWait :
	public IPlayerState
{

private:


public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

