#pragma once

class Enemy;

class IEnemyState abstract
{
protected:
	Enemy* _thisObj;

public:
	IEnemyState() {}
	~IEnemyState() {}

	void LinkEnemyAddress(Enemy* en) { _thisObj = en; }

	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;

};

