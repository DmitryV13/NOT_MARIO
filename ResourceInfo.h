#pragma once
#include "ImageInfo.h"

using namespace::sf;

class ResourceInfo : public ImageInfo{
private:
	int* resource;
	bool image;
	string max;
	string prev;
public:
	ResourceInfo();
	ResourceInfo(float x, float y, int text_size, bool image_);
	ResourceInfo(float x, float y, int text_size, TextureManager* t_manager, Warehouse* w_object, string name, bool image_);
	ResourceInfo(float x, float y, int* resource_, int max_v, int text_size, TextureManager* t_manager, int index, string name, bool self_align_);
	~ResourceInfo();

	void addInfo(TextureManager* t_manager, Warehouse* w_object, string name, bool x);
	void addInfo(TextureManager* t_manager, WarehouseItem* w_item, bool x);

	void update() override;
};

