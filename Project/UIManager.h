#pragma once
#include "singletonBase.h"
class Player;
class Stage;

struct tagProgressBar
{
	image* img;
};

class UIManager : public singletonBase <UIManager>
{
private:
	bool _isActive;		//UI가 활성화 상태인지

	Player* _player;
	Stage* _stage;

	image* _number;
	image* _life;
	image* _crystal;
	image* _minimap;
	image* _state;
	image* _dashFrame;
	image* _dashBar;
	image* _time;
	image* _HPBar;

	image* _saveText;
	int _saveTextAlpha;

	int _minimapWidth;
	bool _isGaming;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	bool GetIsActive() { return _isActive; }
	void SetPlayerAddressLink(Player* player) { _player = player; }
	void SetStageAddressLink(Stage* stage) { _stage = stage; }

	void ProgressBarRender(HDC hdc, image* img, int x, int y, float current, float Max);
	void ProgressBarRender(HDC hdc, image* img, int x, int y, float current, float Max, float xRatio, float yRatio);
	
	void SetSaveTextAlpha(int alpha) { _saveTextAlpha = alpha; }

	void SetIsGaming(bool gaming) { _isGaming = gaming; }
	bool GetIsGaming() { return _isGaming;  }
	void SetIsActive(bool active) { _isActive = active; }
};

