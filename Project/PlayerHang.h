#pragma once
#include "IPlayerState.h"
class PlayerHang :
	public IPlayerState
{

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();


};

