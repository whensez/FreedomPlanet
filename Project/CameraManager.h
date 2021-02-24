#pragma once
#include "singletonBase.h"

class gameNode;

class cameraManager : public singletonBase <cameraManager>
{
private:
	//Camera
	RECT mapRc, screenRc;				//�ʰ� ȭ�� ��Ʈ				(loopRender�� ���ڰ��� �ʿ� �� ���)
	float targetX, targetY;				//Ÿ�� ��ǥ
	float centerX, centerY;				//ī�޶� ���� ���� ��ǥ		(������ ĳ������ ���� ��ǥ)
	float drawLeft, drawTop;			//ī�޶� �׷��� ��			(������ 0, 0)
	float xOffset, yOffset;				//ī�޶� ������ ������		(����ŷ ���� ���� ī�޶� ������)

	float cameraXSize, cameraYSize;		//ī�޶��� ���� ���� ũ��		(Ŭ ���� �ε巯�� �������� ��.)
	float screenXSize, screenYSize;		//ȭ�� ���� ���� ũ��			(������ WINSIZEX, WINSIZEY ũ��)

	image* map;							//������ ��ü �� �̹���		(ī�޶� ���� �� �ִ� ����)
	float mapXSize, mapYSize;			//�� ���� ���� ũ��			(������ map�� width, height ũ��)
	float magnification;				//��ũ���� ���� ����			(������ 1)
	float magnificationOffset;			//��ũ���� ���� �߰� ����		(������ 0)
	bool isAdjustMagnificiation;		//������ �����ϰ� �ִ���
	float goalMag;						//��ǥ ����
	float plusMag;						//�߰� ����
	bool isZoomIn;						//Ȯ������ �������

	//MiniMap
	bool isMinimapActive;				//�̴ϸ��� Ȱ��ȭ ��������
	int minimapX, minimapY;				//�̴ϸ� X, Y ��ġ ������
	float minimapXsize, minimapYsize;	//�̴ϸ� ���� ���� ũ��
	float minimapRatio;					//�̴ϸ� ����
	float minimapAlpha;					//�̴ϸ� ������

	//Shake
	int shakeTime;						//���� ���� �ð�
	int shakeTimer;						//���� �ð� ��� Ÿ�̸�
	int shakeInterval;					//���� �ð� ����

	float perTime;						//�ð� �� ���� ������
	float shakeAngle;					//�׷����� ����

	int xShaking;						//��鸮�� x ����
	int yShaking;						//��鸮�� y ����
	int shakeStrength;					//���� �������� ���� �۰����� �״������
	bool isShaking;						//��鸲 ����

public:
	//======================== Camera Render ========================
	void mapRender(image* img, HDC hdc);
	void minimapRender(image* img, HDC hdc);

	//======================== Camera Getter ========================

	float GetX() { return centerX; }
	float GetY() { return centerY; }
	float GetLeft() { return drawLeft; }
	float GetTop() { return drawTop; }
	float GetCameraXSize() { return cameraXSize; }
	float GetCameraYSize() { return cameraYSize; }
	float GetScreenXSize() { return screenXSize; }
	float GetScreenYSize() { return screenYSize; }
	float GetMapXSize() { return mapXSize; }
	float GetMapYSize() { return mapYSize; }
	RECT GetMapRect() { return mapRc; }
	RECT GetScreenRect() { return screenRc; }
	float GetMagnificiation() { return magnification; }
	int GetMinimapWidth() { return minimapXsize * minimapRatio; }
	bool GetIsActiveMinimap() { return isMinimapActive; }

	//======================== Camera private Function ========================

private:
	//ī�޶� ������
	void Move();
	
	//Set Map ����
	void Setting();

public:
	cameraManager() {}
	~cameraManager() {}
	//ī�޶� �ʱ�ȭ
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc, image* map);
	virtual void render();

	//======================== Camera Setter ========================
public:

	//*this, map �̹��� ����
	void SetMap(gameNode & _gameNode, image * _img);

	//*this, map xũ��, map yũ��
	void SetMap(gameNode & _gameNode, int _x, int _y);

	//ī�޶��� ���� x��ǥ, ī�޶��� ���� y��ǥ. (������ ĳ������ x, y ��ǥ�� ����.)
	void SetPos(float _x, float _y);

	//ī�޶��� ���� x��ǥ, ī�޶��� ���� y��ǥ, ī�޶� ������ xũ��, ī�޶� ������ yũ��, ī�޶� �ӵ�
	void SetPos(float _x, float _y, float _cameraXSize, float _cameraYSize, float _speed);

	//ȭ�� ũ�� ���� (�⺻�� WINSIZEX, WINSYZEY)
	void SetScreenSize(int _x, int _y) { screenXSize = _x; screenYSize = _y; }

	//ī�޶� �׸� ��ġ ���� (LEFT, TOP �����̸�, �⺻�� 0, 0)
	void SetDrawPos(int _x, int _y) { drawLeft = _x; drawTop = _y; }

	//======================== Camera Zoom ========================

	//���� ���� (������ 1)
	void SetMagnification(float mag) { magnification = mag; }

	//������ mag�� �� ������ plus�� ��ȭ��Ų��.
	void SetMagnification(float mag, float plus);

	//���� Offset ����
	void SetMagnificationOffset(float offset) { magnificationOffset = offset; }

	//���� Offset �߰�
	void PlusMagnification() { magnification += magnificationOffset; }
	
	//======================== Minimap ========================

	//�̴ϸ� ����
	void SetMinimap(int x, int y, int width, int height, float ratio, int alpha);

	//�̴ϸ� �ѱ� (������ true)
	void ActiveMinimap(bool mini) { isMinimapActive = mini; }

	//�̴ϸ� ���
	void SetMinimapToggle() { isMinimapActive = !isMinimapActive; }


	//======================== Camera Shake ========================
public:
	//���� �ð�, �ð� ����, ��鸱 x����, ��鸱 y����, ���� �۰�(-1) Ȥ�� �״�� (0) Ȥ�� ���� ����(+1), ���� �۰�+�ڵ� ����(-2)
	void Shake(int _time, int _interval, float _xShaking, float _yShaking, int _strength = -2);
};


/*
	�� ============================== �Ѹ� ī�޶� �ȳ��� ============================== ��

		����������������������������������������������������������������������������������������������������������������������������������������������������
		��	Created By : �Ѹ�						Version : 2.0				 ��
		��	Reporting Date : 2020.12.08				Last Update : 2020.12.14	 ��
		��																		 ��
		��	Function : SetMap, SetPos, Shake, MapRender, MiniMapRender			 ��
		��																		 ��
		��			��		Thanks for Using this Camera!		��				 ��
		����������������������������������������������������������������������������������������������������������������������������������������������������

	�� ī�޶� ����ϱ� ���ؼ��� init���� SetMap(), update���� SetPos() �� �Լ��� ȣ���ؾ� �մϴ�.
	����, ī�޶��� �߰����� ������δ� ī�޶� ��鸲 �Լ� Shake()�� �ֽ��ϴ�.


	�� ========================  ī�޶� ����ϴ� ����Դϴ�. ======================== ��

	1.	���� ����, gameNode.cpp�� gameNode.h�� �� ���� ���Ͽ��� �״�� ���� �ٿ��ֱ�! ���ּ���.


	2.  tagCamera : ī�޶� ��� ������ ����ϰ�, ��� ������ ī�޶� ��ü �����ϱ�!

			�� ī�޶�� ��� ���� �ȿ� Ŭ������ ������� �ֽ��ϴ�.
			�켱, playGround.h�� #include "Camera.h"�� �� ī�޶� ��� ������ ���Խ�Ű��,
			playGround.h�� ��� ������ tagCamera camera; �� ���� �� ī�޶� ��ü�� ����� �ݴϴ�.


	3.  SetMap() :  ī�޶� ������ ȭ���� ��ü ������ �����ϴ� �Լ� ȣ���ϱ�!

			ī�޶� ����ϱ� ���ؼ��� ī�޶� ���� �� �ִ� ���� ��ü ���� ũ�⸦ ������ �־�� �մϴ�.
			playGround.cpp �� init() ������ ���� �� �� gameNode::init(); �Ʒ��� camera.SetMap(); �Լ��� ȣ���մϴ�.
			�̴� gameNode::init() �Լ����ٴ� �Ʒ��� �־�� �մϴ�. SetMap �Լ����� gameNode�� backDC�� ũ�⸦ �������ϱ� �����Դϴ�.

			SetMap �Լ��� ī�޶� ���� �� �ִ� ������ ũ�⸦ �����ϱ� ������, �� ũ��� ���� ��ü ��.bmp �̹��� ������ ũ��� �����ϴ�.
			SetMap �Լ��� �����ε�� �� �����̸�, �� �� ���ڰ��� [gameNode]��, [���� �̹��� ����] �Ǵ� [�� ��� ���� ������]�Դϴ�.
			ī�޶󿡰� ���� ��ü ������ �˷��ֱ� ���� ���� �̹��� ������ ����� ���� �ְ�, �� width�� height ũ�⸦ ���� �Է��� ���� �ֽ��ϴ�.

		[1�� : ���� �̹��� ������ ����ϴ� ���]
			�Ű����� : SetMap(gameNode _gameNode, image* _img) == (���� ���, ���� �̹��� ����)

			ex.1) camera.SetMap(*this, IMAGEMANAGER->addImage("map", "image/map.bmp", 3200, 1800, false, RGB(255, 0, 255)));
			����� �Ǵ� �̹����� �� �Լ����� �ٷ� �߰��ϴ� �����Դϴ�. addImage�� �����ص� ������ �ʾ� �����մϴ�.

			ex.2) camera.SetMap(*this, IMAGEMANAGER->findImage("map");
			�� ��쿡��, SetMap �Լ� ȣ�⺸�� ���� ���� addImage�� �Ǿ� �־�� �մϴ�. addImage�� �����ϰ� findImage�ϸ� �����ϴ�.

			ex.3) camera.SetMap(*this, map);
			����������, SetMap �Լ� ȣ�⺸�� ���� ���� addImage�� �Ǿ� �־�� �ϸ�, image* map�� � �� �̹����� ����Ű�� �־�� �մϴ�.


		[2�� : ���� ����� ���� �������� �Է��ϴ� ���]
			�Ű����� : SetMap(gameNode _gameNode, int _x, int _y) == (���� ���, ���� ���� ũ��, ���� ���� ũ��)

			ex.1) camera.SetMap(*this, 3200, 1800);
			map�� ���� ���� ũ�⸦ ���� �Է��ϴ� ����Դϴ�. �̹��� ������ ��� �����ϹǷ� �̹��� ������ ���� ���, �� ����� �� ������ �� �ֽ��ϴ�.


	4.  SetPos() : ī�޶��� ���� ��ǥ�� �����ϴ� �Լ�! �ǽð����� ���ŵǾ�� �ϹǷ� update�� ����, ���� ĳ������ x, y ��ǥ�� ���ϴ�!

			���� playGround.cpp �� update �������� camera.SetPos(); �Լ��� ȣ���մϴ�.
			�Լ��� ��ġ�� player�� x, y�� ���ŵǴ� �� �ٷ� �Ʒ��� ���ִ� �� ��õ������, CPU�� ������ ������ ������ ũ�� ���� ������ �ʽ��ϴ�.

			���ڰ��� ī�޶��� ���� ��ǥ�� �� x, y�Դϴ�. ���� ������ ĳ������ x, y��ǥ�� �Է��մϴ�.
			���� ���, ī�޶� ĳ���͸� ���� �Ѿư� �� ���� �Ϲ����� �Է��� camera.SetPos(player.x, player.y);�� �� ���̸�,
			ĳ���ͺ��� �� �� ���� ���߱� ���� ���� camera.SetPos(player.x, player.y - 200); ��� ���� ���°� �� ���Դϴ�.

			�����ε�� �� �����̸�, �� ī�޶�� �۵� ����� �ٸ��ϴ�.

			1�� �����ε��, ���ڰ����� x, y ���� ��ǥ�� ������, ī�޶� �� ��ǥ�� �ٷ� �Ѿư��ϴ�.

			2�� �����ε�� ���ڰ����� x, y ������ǥ�� ī�޶� �Ѵ� ������ �Ѵ� ���ǵ带 ������,
			�Է¹��� ĳ���� ��ǥ�� �� ������ �����, �������� �ӵ���ŭ�� ������� �Ѿư��ϴ�.

			1���� ī�޶�� �ش� ��ǥ�� �ٷ� �ٷ� �Ѿư� ������, 2�� ī�޶�� �� �ڿ������� �ε巯�� �������� �� �� �ֽ��ϴ�.


		[1�� : ī�޶� �ٷ� �Ѿư��� ���]
		�Ű����� : SetPos(float _x, float _y) == (ī�޶��� ���� x��ǥ, ī�޶��� ���� y��ǥ)

			ex.1) camera.SetPos(player.x, player.y);
			�� ��� ī�޶� ĳ������ ������ �ٷ� �Ѿ� ���ϴ�.

			ex.2) camera.SetPos(player.x, player.y - 200);
			�� ��� ī�޶� ĳ���ͺ��� ���� ���� ���߱� ������, ĳ���Ͱ� ȭ���� �ణ �Ʒ� �ʿ� �ְ� �׷����ϴ�.


		[2�� : ī�޶� ������ ����� �Ѿư��� ���]
		�Ű����� : SetPos(float _x, float _y, float _cameraXSize, float _cameraYSize, int _speed)
					 == (ī�޶��� ���� x��ǥ, ī�޶��� ���� y��ǥ, ī�޶��� x ���� ũ��, ī�޶��� y ���� ũ��, ī�޶� ���� �ӵ�)

			ex.1) camera.SetPos(player.x, player.y, 200, 250, player.speed / 2);
			�� ī�޶�� ĳ���Ͱ� ������ �������� �Է��� ���ǵ常ŭ�� õõ�� �Ѿư� �� �� �ε巯�� ���Դϴ�.
			�� �� cameraXSize, cameraYSize ���� Ŭ ���� �� �� ��ٷȴٰ� �Ѿư���, ���� ���� �ٷ� �Ѿư��ϴ�.
			������ _cameraXSize, _cameraYSize�� 0, 0�� �Է��Ѵ� �ص�, 1�� ī�޶�� ���� ����� ���� �ٸ��ϴ�.
			x, y�� �ٷ� �����ϴ� ����� �ƴ�, ����ڰ� �Է��� _speed��ŭ �Ѿư��� ������ �� �� �ε巴���ϴ�.


	5. render() : ���� �������� �� ī�޶��� ���� �κ��� �׸���� �ٲ� �ݴϴ�!
		playGround.cpp�� render ������ ���ϴܺ��� �ǵ��� ����� �κ��� �ٲ��ݴϴ�.


	6.  ��� ������ �������ϴ�! ���� ī�޶� ����� �� �ֽ��ϴ�. >��<!
		ī�޶� ��뿡 ������� ������ �Ѹ𸮿��� ������ ��û�ϼ���...�١�

			�� TIP : ����� ī�޶� ����� ����, ĳ���Ͱ� �������̳� �Ʒ��� ������ �� ��,
			ȭ�� ��(WINSIZEX, WINSIZEY)�� �������� ���ϰ� �ϴ� ���� ó���� �ϸ� �� �ǰ�,
			�� ���� �������� ���ϰ� �ϴ� ���� ó���� �ؾ� �մϴ�.

			���� ���, ���������� �̵��� �� ȭ�� ���� �������� ���ϰ� ���� ���ǹ��� ������ ���Ҵٸ�,
			if (player.x + player.rcXsize < WINSIZEX && KEYMANAGER->isStayKeyDown(VK_RIGHT)) player.x += speed;

			������ ���� ������� �ٲ� �־�� �մϴ�.
			if (player.x + player.rcXsize < _camera.GetMapXSize() && KEYMANAGER->isStayKeyDown(VK_RIGHT)) player.x += speed;

			�̷� ó���� �ٲپ� ���� ������, ĳ���Ͱ� WINSIZEX ȭ���� �Ѿ�� ����, ī�޶� �۵��ǰ� �ִ��� Ȯ������ �� �� �����ϴ�.
			����, init���� SetMap�� �� �� �Է��ߴ� map ũ�� ��ŭ�� �̹����� ������ render �� �־�� �� ȭ�� ���� ��� ȭ���� ������ �� ���� ���Դϴ�.



	�� ======================== 2. TIP : ī�޶� �������� ��� ��ǥ�� ���� ���� ��! ======================== ��

	HPbar, Itemâ ��� ���� UI, �� map ���� ��ġ���� �ʰ�, ī�޶� �������� �� ��� ��ǥ�� ��� �ϴ� �͵��� render �κп� �ش� ��ġ�� �� ��,
	(0, 0) ���� ��ǥ�� �������� �� ��ġ�� �ƴ�, ī�޶��� ����(camera.x, camera.y)�� �� ���� ��� ��ǥ�� �������� ��ġ�� �Է��ؾ� �մϴ�.

	ī�޶� ���� CENTER :			(backDC, camera.GetX(), camera.GetY());
		ex) (backDC, camera.GetX() + 200, camera.GetY() - 100); �� ��� ī�޶� ������ �������� +200, -100 ��ġ�� �ش� ��ü�� �׸��ϴ�.

	ī�޶� ���� LEFT TOP :		(backDC, camera.GetX() - camera.GetScreenXSize() / 2 , camera.GetY() - camera.GetScreenYSize() / 2);
	ī�޶� ���� LEFT BOTTOM :	(backDC, camera.GetX() - camera.GetScreenXSize() / 2 , camera.GetY() + camera.GetScreenYSize() / 2);
	ī�޶� ���� RIGHT TOP :		(backDC, camera.GetX() + camera.GetScreenXSize() / 2 , camera.GetY() - camera.GetScreenYSize() / 2);
	ī�޶� ���� RIGHT BOTTOM :	(backDC, camera.GetX() + camera.GetScreenXSize() / 2 , camera.GetY() + camera.GetScreenYSize() / 2);



	�� ======================== 3. ī�޶��� Shake ����� ����ϴ� ����Դϴ�. ======================== ��

	1.  �켱 ���� 6���� ������ ���� ī�޶� ���� �� �ݴϴ�.

	2.  update ��������, ����ϰ� ���� ������ camera.Shaking(); �Լ��� ȣ���մϴ�.

		����ũ ������ 4�����̸�, ���� �۰�(-1), �״��(0), ���� ũ��(+1), ���� �۰� �ڵ� ����(-2)�� �ֽ��ϴ�.
		������ ���ڰ��� ����ũ ������ �Է��ϸ�, �Է����� ���� �� �ڵ� ����(-2)���� �����Ǿ� �ֽ��ϴ�.

		[����ũ �Լ�]
		�Ű����� : Shake(int _time, int _interval, float _xShaking, float _yShaking, int _strength = -2)
					== (���� ���� �ð�, ���� �ð� ����, ��鸱 xũ��, ��鸱 yũ��, �ð��� ���� ���� ����)

			ex.1) if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) camera.Shaking(100, 2, 15, 20, -2);
			���͸� ���� ���, ī�޶� 100�� ���� 2���� �������� x�� 15, y�� 20��ŭ ���� �۰� �ڵ� �����ϸ� ���ϴ�.

			ex.2) if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) camera.Shaking(30, 8, 0, 70, 1);
			���͸� ���� ���, ī�޶� 50�� ���� 8���� �������� x�� 0, y�θ� 70��ŭ ���� ���� ���ϴ�.

			�� ��� ex.1�� ex.2���� �� ���� ��鸮��, �� ������ ����, x, y�� ��鸳�ϴ�.
			ex.2�� ex.1���� �� ª�� ��鸮��, �� ������ ����, y�θ� ��鸳�ϴ�.


	�� ======================== �Ѹ� ī�޶� ������ּż� �����մϴ�...�١� ======================== ��

*/
