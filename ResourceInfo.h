#pragma once
#include "ImageInfo.h"

using namespace::sf;

class ResourceInfo : public ImageInfo{
private:
	int* resource;
	bool self_align;
	string max;
public:
	ResourceInfo(float x, float y, int* resource_, int max_v, int text_size, Font* font, TextureManager* t_manager, int index, string name, bool self_align_);

	void update(Vector2f mouse_pos, FloatRect view_cords) override;
};

