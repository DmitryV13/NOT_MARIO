#include "stdafx.h"
#include "Inventory.h"

	Inventory::Inventory(){
		items["Coin"] = {new int(1000), 0 };
		items["BSplinter"] = { new int(100), 1000 };
		items["RSplinter"] = { new int(100), 1000 };
		items["Arrow"] = { new int(100), 0 };
	}
	
	pair<int*, int>& Inventory::getItemInfo(string name){
		return items[name];
	}
