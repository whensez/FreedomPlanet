#pragma once
#include "IPlayerState.h"
class PlayerBeam :
	public IPlayerState
{

	float _starTimer;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();

};

