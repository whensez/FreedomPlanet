#pragma once

#define GRAVITY 0.18f			//중력

enum DEST			//좌우 방향
{
	D_RIGHT = 0,		//0 오른쪽
	D_LEFT = 1,			//1 왼쪽
	D_NONE = 2,			//2 없음
};

enum POSITION			//위치
{
	P_GROUND,			//땅
	P_PLATFORM,			//플랫폼
	P_AIR,				//공중
	P_CLIFF,			//절벽
	P_LADDER,			//사다리
};