#pragma once
#include "WarehouseItem.h"

using namespace::sf;

class Warehouse {
private:
	unordered_map<string, vector<pair<string, WarehouseItem>>> warehouse;
public:
	Warehouse();
	pair<int*, int> getItemInfo(string item_type, string item_name);
};

