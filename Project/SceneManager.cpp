#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

gameNode* SceneManager::_currentScene = NULL;

HRESULT SceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

void SceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_mSceneList.clear();
}

void SceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void SceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

gameNode* SceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return nullptr;
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}


//���߿� �����ܺôٰ� �ڱ��Ը� �Ǵ� ��������Ʈ�� ������� �պ����ϸ� �պ���
HRESULT SceneManager::changeScene(string sceneName)
{
	//���ͷ����Ϳ� ã���� �ϴ� ���� Ű ���� �ִ´�
	mapSceneIter find = _mSceneList.find(sceneName);

	//ã���� �ϴ� ���� �������� ������ ���и� �˸���
	if (find == _mSceneList.end()) return E_FAIL;

	//ã���� �ϴ� ���� ���� ���� ������ �ٲ��ʿ䰡 ����
	if (find->second == _currentScene) return S_OK;

	//���� �ٲٴµ� ����������  init()�Լ��� �ٷ� �����Ų��
	if (SUCCEEDED(find->second->init()))
	{
		//���� ���� ������ �Լ��� ������� �޸� ������ �ϰ�
		if (_currentScene) _currentScene->release();

		//�ٲٷ��� ���� ��������� ü����
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
