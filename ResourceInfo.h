#pragma once
#include "ImageInfo.h"

using namespace::sf;

class ResourceInfo : public ImageInfo{
private:
	int* resource;
	string max;
public:
	ResourceInfo(float x, float y, int* resource_, int max_v, int text_size, Font* font, TextureManager* t_manager, int index, string name);

	void update(Vector2f mouse_pos, FloatRect view_cords) override;
};

