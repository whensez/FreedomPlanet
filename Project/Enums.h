#pragma once

#define GRAVITY 0.18f			//�߷�

enum DEST			//�¿� ����
{
	D_RIGHT = 0,		//0 ������
	D_LEFT = 1,			//1 ����
	D_NONE = 2,			//2 ����
};

enum POSITION			//��ġ
{
	P_GROUND,			//��
	P_PLATFORM,			//�÷���
	P_AIR,				//����
	P_CLIFF,			//����
	P_LADDER,			//��ٸ�
};