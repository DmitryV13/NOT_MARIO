#pragma once

using namespace::sf;

class WarehouseItem{
private:
	int amount;
	int max;
	bool access;

	int t_index;
	string name;
	IntRect cords;
	int frame_numbers;
public:
	WarehouseItem(string name_, int amount_, int max_, bool access_);
	WarehouseItem(string name_, int amount_, int max_, bool access_, int index_, IntRect cords_, int frame_numbers_);
	~WarehouseItem();

	void setAccess(bool new_access);
	pair<int*, int> getInfo();
	int* getAmount();
	string getName();
	bool isAccessible();
	pair<int, string> getTMInfo();
	pair<IntRect, int> getSpriteInfo();
};

