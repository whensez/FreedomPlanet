#pragma once
#include "singletonBase.h"
#include <vector>

struct tagPicture
{
	image* _img;
	int _count;
	int _number;
	RECT _rc;
};
class GalleryManager : public singletonBase <GalleryManager>
{
private:
	int _count;
	int _maxCount;
	int _lastCount;

	typedef vector<tagPicture*> vGallery;
	vGallery _vGallery;

	image* _back;
	image* _gallery;

	bool _isOpen;

public:
	virtual HRESULT init(image* img);
	virtual void release();
	virtual void update();
	virtual void render();

	void takePicture();
	void openGallery();

};
