#pragma once
#include "TileAnim.h"
class TileBox : public TileAnim
{
private:

	//���� � ���������� ���� ������, �� �������� � ��� �����.

public:

	TileBox();
	TileBox(std::string Name, short int inter, short int texture_size_w,short int texture_size_h, char ass, short int anim_f, short int anim_q, float time);
};

