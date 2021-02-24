#include "stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init()
{
	//��� �̹���
	_background.img = IMGMANAGER->addFrameImage("background8", "image/backGround8.bmp", 2560, 1500, 2, 1, false, MAGENTA);
	_background.loopY = 0;

	//Ÿ��Ʋ �̹���
	_title.img = IMGMANAGER->addImage("ui_title", "image/ui_title.bmp", 598, 216, true, MAGENTA, true);
	_title.alpha = 0;
	_timer = 0;

	//�޴� �̹���
	_menu = new tagImg[3];

	_menu[0].img = IMGMANAGER->addImage("ui_menu_start", "image/ui_menu_start.bmp", 300, 40, true, MAGENTA, true);
	_menu[1].img = IMGMANAGER->addImage("ui_menu_howtoplay", "image/ui_menu_howtoplay.bmp", 300, 40, true, MAGENTA, true);
	_menu[2].img = IMGMANAGER->addImage("ui_menu_quit", "image/ui_menu_quit.bmp", 300, 40, true, MAGENTA, true);
	IMGMANAGER->addImage("ui_howtoplay", "image/ui_howtoplay.bmp", 300, 720, false, MAGENTA, true);

	for (int i = 0; i < 3; i++)
	{
		_menu[i].rc = RectMakeCenter(WINSIZEX / 2, 550 + i * 50, _menu[0].img->getWidth(), _menu[0].img->getHeight());
		_menu[i].alpha = 120;
		_menu[i].isSelect = false;
		_menu[i].loopX = 1;
		_menu[i].loopY = 1;
	}
	_isReverse = false;
	return S_OK;
}

void TitleScene::release()
{
	delete[] _menu;
}

void TitleScene::update()
{
	//��� �̹���
	if (_isReverse) _background.loopY -= 5;
	else if (TIMEMANAGER->getWorldTime() < 4.0f) _background.loopY += 2;
	
	//Ÿ��Ʋ �̹���
	if (_title.alpha >= 255) _title.alpha = 255;
	else _title.alpha += 3;

	if (TIMEMANAGER->getWorldTime() - _timer > 0.5f) ++_title.loopY;
	else --_title.loopY;
	if (TIMEMANAGER->getWorldTime() - _timer > 1.0f) _timer = TIMEMANAGER->getWorldTime();


	//�޴� ���� �� ���� ����
	for (int i = 0; i < 3; i++)
	{
		if (PtInRect(&_menu[i].rc, _ptMouse))
		{
			_menu[i].alpha = 255;
			if (i==1) _menu[i].isSelect = true;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _menu[i].isSelect = true;
		}
		else
		{
			_menu[i].alpha = 120;
			_menu[i].isSelect = false;
		}
	}
	
	//�����̽��� �Ǵ� ���ͷε� ���� ����
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isOnceKeyDown(VK_RETURN)) _menu[0].isSelect = true;
	if (_menu[0].isSelect)  _isReverse = true;
	else if (_menu[2].isSelect) PostQuitMessage(0);				//���� ���� �� ���α׷� ����

	if (_isReverse)
	{
		if (_title.alpha >= 10) _title.alpha -= 10;
		if(_background.loopY < 0) SCENEMANAGER->changeScene("game");	//���� ���� �� ���� ����
	}
}

void TitleScene::render()
{
	//��� �̹���
	_background.img->loopRender(getBackDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _background.loopY);
	
	//Ÿ��Ʋ �̹���
	_title.img->alphaRender(getBackDC(), WINSIZEX / 2 - _title.img->getWidth() / 2, WINSIZEY / 3 + _title.loopY, _title.alpha);

	//�޴� �̹���
	for (int i = 0; i < 3; i++) _menu[i].img->alphaRender(getBackDC(),_menu[i].rc.left, _menu[i].rc.top, _menu[i].alpha);

	if (_menu[1].isSelect) IMGMANAGER->findImage("ui_howtoplay")->alphaRender(getBackDC(), 0,0,200);

}
