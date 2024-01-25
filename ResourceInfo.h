#pragma once
#include "ImageInfo.h"

using namespace::sf;

class ResourceInfo : public ImageInfo{
private:
	int* resource;
	bool self_align;
	string max;
	string prev;
public:
	ResourceInfo();
	ResourceInfo(float x, float y, Font* font, int text_size, bool self_align_);
	ResourceInfo(float x, float y, int text_size, Font* font, TextureManager* t_manager, Warehouse* w_object, string name, bool self_align_);
	ResourceInfo(float x, float y, int* resource_, int max_v, int text_size, Font* font, TextureManager* t_manager, int index, string name, bool self_align_);

	void addInfo(TextureManager* t_manager, Warehouse* w_object, string name, bool x);

	void update(Vector2f mouse_pos, FloatRect view_cords) override;
};

