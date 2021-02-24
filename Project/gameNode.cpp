#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		KEYMANAGER->init();
		IMGMANAGER->init();
		TIMEMANAGER->init();
		CAMERAMANAGER->init();
		UIMANAGER->init();
		SCENEMANAGER->init();
		TXTDATA->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		GALLERYMANGER->release();
		GALLERYMANGER->releaseSingleton();

		IMGMANAGER->release();
		IMGMANAGER->releaseSingleton();

		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		SAVELOADMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();
	}
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render()
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
		case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.y = static_cast<float>(HIWORD(lParam));

		break;


		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;
			}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
