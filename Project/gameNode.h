#pragma once
#include "image.h"


//����۶�� �� ��Ʈ�� �̹����� �ϳ� �����صд�
static image* _backBuffer = IMGMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _mapBuffer = IMGMANAGER->addImage("mapBuffer", WINSIZEX, WINSIZEY);
static image* _miniMapBuffer = IMGMANAGER->addImage("midBuffer", WINSIZEX, WINSIZEY, true);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//�Ŵ��� �ʱ�ȭ �Ҳ��� ����

public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();					//�ʱ�ȭ ���� �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();					//�޸� ���� �Լ�
	virtual void update();					//���� ����
	virtual void render();					//�׸��� ����

	//����� ������
	void setBackBuffer(int _mapXSize, int _mapYSize) { _backBuffer->init(_mapXSize, _mapYSize); }
	void setMapBuffer(int _mapXSize, int _mapYSize) { _mapBuffer->init(_mapXSize, _mapYSize); }
	void setMinimapBuffer(int _mapXSize, int _mapYSize) { _miniMapBuffer->init(_mapXSize, _mapYSize); }
	
	HDC getHDC() { return _hdc; }

	HDC getBackDC() { return _backBuffer->getMemDC(); }

	//�ʹ��� ������
	HDC getMapDC() { return _mapBuffer->getMemDC(); }
	
	//�̴ϸ� ���� ������
	HDC getMinimapDC() { return _miniMapBuffer->getMemDC(); }

	int getMemDCWidth() { return _mapBuffer->getWidth(); }
	int getMemDCHeight() { return _mapBuffer->getHeight(); }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

