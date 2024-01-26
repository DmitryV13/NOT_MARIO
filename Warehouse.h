#pragma once
#include "WarehouseItem.h"

using namespace::sf;

class Warehouse {
private:
	unordered_map<string, vector<WarehouseItem*>> warehouse;
public:
	Warehouse();
	pair<int*, int> getItemInfo(string item_type, string item_name);
	WarehouseItem* getWarehouseItem(string type, string name);
	WarehouseItem* getWarehouseItem(string name);
	vector<WarehouseItem*> getWarehouseItems(string type);
};

