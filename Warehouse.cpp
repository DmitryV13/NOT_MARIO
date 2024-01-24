#include "stdafx.h"
#include "Warehouse.h"

Warehouse::Warehouse(){
	warehouse["currency"] = vector<pair<string, WarehouseItem>>();
	warehouse["currency"].push_back({ "coin", WarehouseItem(1000, 0, true) });
	warehouse["currency"].push_back({ "b_splinter", WarehouseItem(100, 1000, true) });
	warehouse["currency"].push_back({ "r_splinter", WarehouseItem(10, 1000, true) });

	warehouse["ammunition"] = vector<pair<string, WarehouseItem>>();
	warehouse["ammunition"].push_back({ "simple_arrow", WarehouseItem(10, 0, true) });
	}
	
	pair<int*, int> Warehouse::getItemInfo(string item_type, string item_name){
		for (int i = 0; i < warehouse[item_type].size(); i++){
			if (warehouse[item_type][i].first == item_name) {
				return warehouse[item_type][i].second.getInfo();
			}
		}
	}
