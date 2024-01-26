#include "stdafx.h"
#include "Warehouse.h"

Warehouse::Warehouse(){
	warehouse["currency"] = vector<WarehouseItem*>();
	warehouse["currency"].push_back(new WarehouseItem("Coin", 1000, 0, true, 0 ,IntRect(0,0,8,8), 1));
	warehouse["currency"].push_back(new WarehouseItem("BSplinter", 100, 1000, true, 0, IntRect(0, 0, 7, 9), 1));
	warehouse["currency"].push_back(new WarehouseItem("RSplinter", 10, 1000, true, 0, IntRect(0, 0, 7, 11), 1));

	warehouse["ammunition"] = vector<WarehouseItem*>();
	warehouse["ammunition"].push_back(new WarehouseItem("Arrow1", "Arrow", 10, 0, true, 0, IntRect(0, 0, 40, 5), 1));

	warehouse["heroes"] = vector<WarehouseItem*>();
	warehouse["heroes"].push_back(new WarehouseItem("Hero1", 1, 1, true, 4, IntRect(0, 0, 54, 70), 6));
	warehouse["heroes"].push_back(new WarehouseItem("Hero2", 1, 1, true, 4, IntRect(0, 0, 63, 68), 1));

	warehouse["potions"] = vector<WarehouseItem*>();
	warehouse["potions"].push_back(new WarehouseItem("ManaPotion", "Mana", 1, 0, true, 5, IntRect(0, 0, 19, 39), 5));
	warehouse["potions"].push_back(new WarehouseItem("HealthPotion", "Health", 1, 0, true, 5, IntRect(0, 0, 19, 39), 5));
	warehouse["potions"].push_back(new WarehouseItem("PoisonPotion", "Poison", 1, 0, true, 5, IntRect(0, 0, 19, 39), 5));
	warehouse["potions"].push_back(new WarehouseItem("SpeedPotion", "Speed", 1, 0, true, 5, IntRect(0, 0, 19, 39), 5));

	warehouse["other"] = vector<WarehouseItem*>();
	warehouse["other"].push_back(new WarehouseItem("Transparent", 1, 0, true, 0, IntRect(0, 0, 0, 0), 1));
	warehouse["other"].push_back(new WarehouseItem("RedScaleBar", 1, 0, true, 0, IntRect(0, 0, 158, 20), 3));
	warehouse["other"].push_back(new WarehouseItem("BlueScaleBar", 1, 0, true, 0, IntRect(0, 0, 158, 20), 3));
	}
	
	pair<int*, int> Warehouse::getItemInfo(string item_type, string item_name){
		for (int i = 0; i < warehouse[item_type].size(); i++){
			if (warehouse[item_type][i]->getName() == item_name) {
				return warehouse[item_type][i]->getInfo();
			}
		}
	}

	WarehouseItem* Warehouse::getWarehouseItem(string type, string name){
		for (int i = 0; i < warehouse[type].size(); i++) {
			if (warehouse[type][i]->getName() == name) {
				return warehouse[type][i];
			}
		}
	}

	WarehouseItem* Warehouse::getWarehouseItem(string name){
		for (auto i : warehouse) {
			for (auto j : i.second) {
				if (j->getName() == name) {
					return j;
				}
			}
		}
	}

	vector<WarehouseItem*> Warehouse::getWarehouseItems(string type){
		return warehouse[type];
	}
