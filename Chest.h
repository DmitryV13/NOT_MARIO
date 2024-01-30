#pragma once
#include "AnimObject.h"
#include "WarehouseItem.h"
#include "random"

class Chest : public AnimObject
{
private:
	bool opened;
	short int fileNumber;
	std::vector<WarehouseItem*> items;
	void filled_in();
	
public:
	~Chest();
	Chest();
	Chest(std::string name, float position_x, float position_y, short int size_W, short int size_H
		, short int anim_factor, short int anim_quantity, float anim_time, short int fileNumber);
	vector<WarehouseItem*>& getItems();
	void useObject() override;
	void animation_object() override;
};

