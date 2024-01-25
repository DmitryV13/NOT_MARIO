#include "stdafx.h"
#include "WarehouseItem.h"

	WarehouseItem::WarehouseItem(string name_, int amount_, int max_, bool access_)
		:amount(amount_), max(max_), access(access_), name(name_){
	}

	WarehouseItem::WarehouseItem(string name_, int amount_, int max_, bool access_, int index_, IntRect cords_, int frame_numbers_)
		:amount(amount_), max(max_), access(access_), name(name_), t_index(index_), cords(cords_), frame_numbers(frame_numbers_) {
	}

	WarehouseItem::WarehouseItem(string name_, string name_for_user_, int amount_, int max_, bool access_, int index_, IntRect cords_, int frame_numbers_)
		:amount(amount_), max(max_), access(access_), name(name_), name_for_user(name_for_user_), t_index(index_), cords(cords_), frame_numbers(frame_numbers_) {
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

	string WarehouseItem::getName(){
		return name;
	}

	string WarehouseItem::getNameFU(){
		return name_for_user;
	}

	bool WarehouseItem::isAccessible(){
		return access;
	}

	pair<int, string> WarehouseItem::getTMInfo(){
		return { t_index, name };
	}

	pair<IntRect, int> WarehouseItem::getSpriteInfo(){
		return {cords, frame_numbers};
	}
