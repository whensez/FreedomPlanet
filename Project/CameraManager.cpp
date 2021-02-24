#include "stdafx.h"
#include "cameraManager.h"
#include "gameNode.h"

HRESULT cameraManager::init()
{
	targetX = targetY = 0;		//ī�޶� Ÿ�� ��ǥ
	centerX = centerY = 0;		//ī�޶� ���� ��ǥ
	xOffset = yOffset = 0;		//ī�޶� ���� ������
	drawLeft = drawTop = 0;		//ī�޶� �׸� ��ġ
	mapXSize = mapYSize = 0;	//���� ũ��

	screenXSize = WINSIZEX;		//ȭ���� X ũ��
	screenYSize = WINSIZEY;		//ȭ���� Y ũ��

	shakeTime = shakeInterval = 0;	//Ÿ�̸�
	perTime = shakeAngle = 0;		//�������� ����
	isShaking = false;				//��鸲 ����

	magnification = 1;				//����
	magnificationOffset = 0;		//�߰� ����
	isAdjustMagnificiation = false; //������ �����ϰ� �ִ���

	SetMinimap(20, 20, 1200, 700, 0.2f, 200);	//�̴ϸ� ����
	ActiveMinimap(true);						//�̴ϸ� �ѱ�

	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{

}

void cameraManager::render(HDC hdc, image * map)
{
	mapRender(map, hdc);
}

void cameraManager::render()
{
}

void cameraManager::mapRender(image* img, HDC hdc)
{
	img->stRender(hdc, drawLeft, drawTop, screenXSize, screenYSize,
		centerX - screenXSize / 2 / magnification, centerY - screenYSize / 2 / magnification,
		screenXSize/magnification, screenYSize/magnification);
}

void cameraManager::minimapRender(image* img, HDC hdc)
{
	if (isMinimapActive && UIMANAGER->GetIsActive()) img->alphaRender(hdc, screenXSize - minimapXsize * minimapRatio - minimapX, minimapY,
		minimapXsize * minimapRatio, minimapYsize * minimapRatio, targetX - minimapXsize / 2, targetY - minimapYsize / 2, minimapXsize, minimapYsize, minimapAlpha);
}


void cameraManager::SetMinimap(int x, int y, int width, int height, float ratio, int alpha)
{
	minimapX = x;
	minimapY = y;
	minimapXsize = width;
	minimapYsize = height;
	minimapRatio = ratio;
	minimapAlpha = alpha;
}

void cameraManager::Move()
{

	if (magnification < 1)
	{
		magnification = 1;
		magnificationOffset = 0;
	}

	PlusMagnification();

	//���� ������ ������� ��� ������ �����Ѵ�.
	if (isAdjustMagnificiation)
	{
		if (isZoomIn)	//���� Ȯ��
		{
			if (magnification < goalMag) magnificationOffset = plusMag;
			else
			{
				magnification = goalMag;
				magnificationOffset = 0;
				isAdjustMagnificiation = false;
			}
		}
		else
		{				//�ܾƿ� ���
			if (magnification > goalMag) magnificationOffset = -plusMag;
			else
			{
				magnification = goalMag;
				magnificationOffset = 0;
				isAdjustMagnificiation = false;
			}
		}
	}

	//����ŷ�� ������� ��� ī�޶� ����.
	if (isShaking)
	{
		if (--shakeTimer < 0)	//Timer�� 0�� �Ǹ� ����ũ�� �����Ѵ�.
		{
			xOffset = 0;			//Offset�� 0���� �ʱ�ȭ
			yOffset = 0;			//Offset�� 0���� �ʱ�ȭ
			shakeAngle = 0;			//�׷����� ������ 0���� �ʱ�ȭ
			isShaking = false;		//����� �ʴ´�.
			return;
		}

		//�ð� ���ݸ��� shakeAngle�� �ٲ۴�.
		if (shakeTimer % shakeInterval == 0)
		{
			shakeAngle = RND->getFloat(PI * 2);

			//������ ���� ����� ���� �ð��� ���� ������ �޸� �Ѵ�.
			if (shakeStrength == -1 || shakeStrength == -2) perTime = shakeTimer;	//���� �۰�
			else if (shakeStrength == 0) perTime = shakeTime;						//�״��
			else if (shakeStrength == 1) perTime = (shakeTime - shakeTimer);		//���� ����
		}

		//���� �۰� + �ڵ� ������ ���� ���, �ε巯�� ó���� ����, �ʹݿ��� Strength ���� �۰� ����.
		if (shakeStrength == -2 && shakeTimer > shakeTime * 0.7f)
		{
			xOffset = cosf(shakeAngle) * xShaking * (shakeTime - shakeTimer) / shakeTime;
			yOffset = sinf(shakeAngle) * yShaking * (shakeTime - shakeTimer) / shakeTime;
		}
		else	//�� ���� ��� ������ �ð��� ���� ���� ������ �Ѵ�.
		{
			xOffset = cosf(shakeAngle) * xShaking * perTime / shakeTime;
			yOffset = sinf(shakeAngle) * yShaking * perTime / shakeTime;
		}

		centerX += xOffset;
		centerY += yOffset;
	}
}

void cameraManager::Setting()
{
	centerX = centerY = 0;		//ī�޶� ���� ��ǥ
	xOffset = yOffset = 0;		//ī�޶� ���� ������
	drawLeft = drawTop = 0;		//ī�޶� �׸� ��ġ
	mapXSize = mapYSize = 0;	//���� ũ��

	screenXSize = WINSIZEX;		//ȭ���� X ũ��
	screenYSize = WINSIZEY;		//ȭ���� Y ũ��
}

void cameraManager::SetMap(gameNode & _gameNode, image * _img)
{
	Setting();						//�ʱ�ȭ
	map = _img;						//��� �̹���
	mapXSize = map->getWidth();		//��� xũ��
	mapYSize = map->getHeight();	//��� yũ��
	_gameNode.gameNode::setBackBuffer(screenXSize, screenYSize);
	_gameNode.gameNode::setMapBuffer(mapXSize, mapYSize);
	_gameNode.gameNode::setMinimapBuffer(mapXSize, mapYSize);
	mapRc = RectMake(0, 0, mapXSize, mapYSize);
}

void cameraManager::SetMap(gameNode & _gameNode, int _x, int _y)
{
	Setting();			//�ʱ�ȭ
	mapXSize = _x;		//��� xũ��
	mapYSize = _y;		//��� yũ��
	_gameNode.gameNode::setBackBuffer(screenXSize, screenYSize);
	_gameNode.gameNode::setMapBuffer(mapXSize, mapYSize);
	_gameNode.gameNode::setMinimapBuffer(mapXSize, mapYSize);
	mapRc = RectMake(0, 0, mapXSize, mapYSize);
}

void cameraManager::SetPos(float _x, float _y)
{
	//ī�޶� �Է��� ��ǥ�� ���� ���󰣴�.
	targetX = _x + xOffset;
	targetY = _y + yOffset;

	//ī�޶� �� ���� ����� �ʰ� ���� ó���� �Ѵ�.
	if (targetX <= 0 + screenXSize / 2) targetX = screenXSize / 2;
	if (targetY <= 0 + screenYSize / 2) targetY = screenYSize / 2;
	if (targetX >= mapXSize - screenXSize / 2) targetX = mapXSize - screenXSize / 2;
	if (targetY >= mapYSize - screenYSize / 2) targetY = mapYSize - screenYSize / 2;

	//ī�޶� �Է��� ��ǥ�� ���� ���󰣴�.
	centerX = _x + xOffset;
	centerY = _y + yOffset;

	Move();		//ī�޶� ����ŷ �� ī�޶��� �������� ȣ���Ѵ�.

	//ī�޶� �� ���� ����� �ʰ� ���� ó���� �Ѵ�.
	if (centerX <= 0 + screenXSize / 2) centerX = screenXSize / 2;
	if (centerY <= 0 + screenYSize / 2) centerY = screenYSize / 2;
	if (centerX >= mapXSize - screenXSize / 2) centerX = mapXSize - screenXSize / 2;
	if (centerY >= mapYSize - screenYSize / 2) centerY = mapYSize - screenYSize / 2;
	screenRc = RectMakeCenter(centerX, centerY, screenXSize, screenYSize);
}

void cameraManager::SetPos(float _x, float _y, float _cameraXSize, float _cameraYSize, float _speed)
{
	if (_speed < 1) _speed = 1;		//�ӵ��� 1�̻����� �Ѵ�.

	int revisionXSpeed = 0;			//ī�޶� �� ���󰡸� ���� �ӵ��� �߰��Ѵ�.
	int revisionYSpeed = 0;			//ī�޶� �� ���󰡸� ���� �ӵ��� �߰��Ѵ�.
	if (abs(centerX - _x) > screenXSize / 16) revisionXSpeed = abs(centerX - _x) / 64;
	if (abs(centerY - _y) > screenYSize / 16) revisionYSpeed = abs(centerY - _y) / 64;

	Move();		//ī�޶� ����ŷ �� ī�޶��� �������� ȣ���Ѵ�.


	//ī�޶� �Է��� ��ǥ�� ���� ���󰣴�.
	targetX = _x + xOffset;
	targetY = _y + yOffset;

	//ī�޶� �� ���� ����� �ʰ� ���� ó���� �Ѵ�.
	if (targetX <= 0 + screenXSize / 2) targetX = screenXSize / 2;
	if (targetY <= 0 + screenYSize / 2) targetY = screenYSize / 2;
	if (targetX >= mapXSize - screenXSize / 2) targetX = mapXSize - screenXSize / 2;
	if (targetY >= mapYSize - screenYSize / 2) targetY = mapYSize - screenYSize / 2;

	//ī�޶� �Է��� ��ǥ�� _speed�� �ӵ��� ���󰣴�.
	if (centerX <= _x - xOffset - _cameraXSize / 2) centerX += _speed + revisionXSpeed;
	if (centerX >= _x + xOffset + _cameraXSize / 2) centerX -= _speed + revisionXSpeed;
	if (centerY <= _y - yOffset - _cameraYSize / 2) centerY += _speed + revisionYSpeed;
	if (centerY >= _y + yOffset + _cameraYSize / 2) centerY -= _speed + revisionYSpeed;

	//ī�޶� �� ���� ����� �ʰ� ���� ó���� �Ѵ�.
	if (centerX <= 0 + screenXSize / 2) centerX = screenXSize / 2;
	if (centerY <= 0 + screenYSize / 2) centerY = screenYSize / 2;
	if (centerX >= mapXSize - screenXSize / 2) centerX = mapXSize - screenXSize / 2;
	if (centerY >= mapYSize - screenYSize / 2) centerY = mapYSize - screenYSize / 2;
}

void cameraManager::SetMagnification(float mag, float plus)
{
	if (mag < 1) mag = 1;
	goalMag = mag;
	if (goalMag > magnification) isZoomIn = true;
	else isZoomIn = false;
	plusMag = abs(plus);
	isAdjustMagnificiation = true;
}


void cameraManager::Shake(int _time, int _interval, float _xShaking, float _yShaking, int _strength)
{
	if (_interval < 1) _interval = 1;	//������ �ּ� 1 �̻�
	xShaking = _xShaking;				//���η� ���� ����
	yShaking = _yShaking;				//���η� ���� ����
	shakeInterval = _interval;			//���� �ð� ����
	shakeTime = _time;					//���� ���� �ð�
	shakeTimer = _time;					//���� �ð� Ÿ�̸�
	shakeStrength = _strength;			//���� �۰� ��鸮���� �״������ ��������
	isShaking = true;					//��鸮�� �Ѵ�
}