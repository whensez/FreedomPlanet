#pragma once
#include "gameNode.h"

enum DEST;

enum PETSTATE
{
	IDLE,
	JUMP,
	SMILE,
};
class Pet : public gameNode
{
private:

	float _x, _y;				//중점 좌표
	float _xOffset, _yOffset;	//오프셋
	RECT _rc;					//충돌용 렉트
	int _rcWidth, _rcHeight;	//렉트 가로세로 크기

	float _speed;				//횡 이동 속도
	float _jumpPower;			//점프력
	
	PETSTATE _currentState;
	PETSTATE _prevState;

	image* _img;
	int _imageXIndex;					//이미지 가로 인덱스
	int _imageYIndex;					//이미지 세로 인덱스
	int _redrawTimer, _redrawInterval;	//이미지 다시 그리는 시간

	DEST _dest;
	bool _isVisible;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update(int x, int y);
	virtual void render();

	void StageInit();

	//플래이어를 따라서 움직인다.
	void Move(int x, int y);

	//이미지를 다시 그린다.
	void ImageRedraw();

	//상태를 설정한다.
	void SetState(PETSTATE state);

	//프레임을 재생한다.
	void FramePlay();

};

