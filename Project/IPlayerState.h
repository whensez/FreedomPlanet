#pragma once

class Player;

class IPlayerState abstract
{

protected:
	Player* _thisObj;

public:
	IPlayerState() {}
	~IPlayerState() {}

	void LinkPlayerAddress(Player* pl) { _thisObj = pl; }

	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;

};

