#pragma once
class WarehouseItem{
private:
	int amount;
	int max;
	bool access;
	int t_index;
	FloatRect rect;
	int frame_numbers;
public:
	WarehouseItem(int amount_, int max_, bool access_);
	~WarehouseItem();

	void setAccess(bool new_access);
	pair<int*, int> getInfo();
	int* getAmount();
};

