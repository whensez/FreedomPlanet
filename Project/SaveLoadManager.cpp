#include "stdafx.h"
#include "SaveLoadManager.h"
#include "Player.h"
#pragma warning(disable:4996)


void SaveLoadManager::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		UIMANAGER->SetSaveTextAlpha(255);
		save();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		load();
	}
}

void SaveLoadManager::save()
{
	_player->SaveData();
}

void SaveLoadManager::load()
{
	_player->LoadData();
}

void SaveLoadManager::pushData(vector<string>* vector, int x)
{
	char temp[128];
	(*vector).push_back(itoa(x, temp, 10));
}
