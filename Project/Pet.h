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

	float _x, _y;				//���� ��ǥ
	float _xOffset, _yOffset;	//������
	RECT _rc;					//�浹�� ��Ʈ
	int _rcWidth, _rcHeight;	//��Ʈ ���μ��� ũ��

	float _speed;				//Ⱦ �̵� �ӵ�
	float _jumpPower;			//������
	
	PETSTATE _currentState;
	PETSTATE _prevState;

	image* _img;
	int _imageXIndex;					//�̹��� ���� �ε���
	int _imageYIndex;					//�̹��� ���� �ε���
	int _redrawTimer, _redrawInterval;	//�̹��� �ٽ� �׸��� �ð�

	DEST _dest;
	bool _isVisible;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update(int x, int y);
	virtual void render();

	void StageInit();

	//�÷��̾ ���� �����δ�.
	void Move(int x, int y);

	//�̹����� �ٽ� �׸���.
	void ImageRedraw();

	//���¸� �����Ѵ�.
	void SetState(PETSTATE state);

	//�������� ����Ѵ�.
	void FramePlay();

};

