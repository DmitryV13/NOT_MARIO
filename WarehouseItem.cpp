#include "stdafx.h"
#include "WarehouseItem.h"

	WarehouseItem::WarehouseItem(int amount_, int max_, bool access_)
		:amount(amount_), max(max_), access(access_){
	}
	
	WarehouseItem::~WarehouseItem(){
	}
	
	void WarehouseItem::setAccess(bool new_access){
		access = new_access;
	}

	pair<int*, int> WarehouseItem::getInfo(){
		return {&amount, max};
	}

	int* WarehouseItem::getAmount(){
		return &amount;
	}
