#include "stdafx.h"
#include "GalleryManager.h"


HRESULT GalleryManager::init(image* img)
{
	_gallery = IMGMANAGER->addImage("ui_gallery", "image/ui_gallery.bmp", 1080, 656, false, MAGENTA, true);
	_count = 0;
	_maxCount = 9;
	_lastCount = 0;
	_back = img;
	_isOpen = false;
	return S_OK;
}

void GalleryManager::release()
{
}

void GalleryManager::update()
{
	takePicture();
	openGallery();
}

void GalleryManager::render()
{
	if (_isOpen)
	{
		_gallery->alphaRender(_back->getMemDC(), 95, 38, 150);

		for (int i = 0; i < _vGallery.size(); i++)
		{
			_vGallery[i]->_img->stRender(_back->getMemDC(), 105+(i % 3) * (WINSIZEX / 4+50),
				45+(i / 3) * (WINSIZEY / 4 + 50), WINSIZEX / 4, WINSIZEY / 4);

			IMGMANAGER->findImage("ui_number")->frameRender(_back->getMemDC(), 155 + (i % 3) * (WINSIZEX / 4 + 50),
				60 + (i / 3) * (WINSIZEY / 4 + 50), _vGallery[i]->_number %10, 0);

			IMGMANAGER->findImage("ui_number")->frameRender(_back->getMemDC(), 110 + (i % 3) * (WINSIZEX / 4 + 50),
				60 + (i / 3) * (WINSIZEY / 4 + 50), _vGallery[i]->_number / 10, 0);

			_vGallery[i]->_rc = RectMake(105 + (i % 3) * (WINSIZEX / 4 + 50), 45 + (i / 3) * (WINSIZEY / 4 + 50), WINSIZEX / 4, WINSIZEY / 4);

			if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(_back->getMemDC(), _vGallery[i]->_rc);
		}

		for (int i = 0; i < _vGallery.size(); i++)
		{
			if (PtInRect(&_vGallery[i]->_rc, _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_vGallery[i]->_img->render(_back->getMemDC());
			}
		}
	}
}

void GalleryManager::takePicture()
{
	if (!_isOpen && KEYMANAGER->isOnceKeyDown('S') && UIMANAGER->GetIsActive())
	{
		if (_count >= _maxCount)
		{
			_back->render(_vGallery[_lastCount]->_img->getMemDC());
			_lastCount = _vGallery[_lastCount]->_count;
			_vGallery[_lastCount]->_number = _count;
			++_lastCount;
			_count++;
			if (_lastCount >= _maxCount) _lastCount = 0;
		}
		else
		{
			tagPicture* _picture = new tagPicture;
			_picture->_img = new image;
			_picture->_img->init(1280, 720, false);
			_back->render(_picture->_img->getMemDC());
			_picture->_count = _count;
			_picture->_number = _count;
			_vGallery.push_back(_picture);
			_count++;
		}
	}
}

void GalleryManager::openGallery()
{
	if (KEYMANAGER->isOnceKeyDown('G') && !_vGallery.empty())
	{
		if (UIMANAGER->GetIsGaming() && !_isOpen)
		{
			_isOpen = true;
			UIMANAGER->SetIsGaming(false);
		}

		else if (_isOpen)
		{
			_isOpen = false;
			UIMANAGER->SetIsGaming(true);
		}
	}


	
}
