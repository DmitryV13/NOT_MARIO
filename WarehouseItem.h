#pragma once

using namespace::sf;

class WarehouseItem{
private:
	int amount;//кол-во
	int max;// = 0
	bool access;//true

	int t_index;
	string name;
	string name_for_user;
	IntRect cords;
	int frame_numbers; //1
public:
	WarehouseItem(string name_, int amount_, int max_, bool access_);
	WarehouseItem(string name_, int amount_, int max_, bool access_, int index_, IntRect cords_, int frame_numbers_);
	WarehouseItem(string name_, string name_for_user_,  int amount_, int max_, bool access_, int index_, IntRect cords_, int frame_numbers_);
	~WarehouseItem();

	void setAccess(bool new_access);
	pair<int*, int> getInfo();
	int* getAmount();
	string getName();
	string getNameFU();
	bool isAccessible();
	pair<int, string> getTMInfo();
	pair<IntRect, int> getSpriteInfo();
};

