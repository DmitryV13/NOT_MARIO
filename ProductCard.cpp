#include "stdafx.h"
#include "ProductCard.h"

	ProductCard::ProductCard(int price_, int amount_, float p_coefficient_, int* source_)
	: price(price_), amount(amount_), source(source_), p_coefficient(p_coefficient_){
		ii_type = INTERFACE_ITEM_TYPE::PRODUCT_CARD;
		id = GlobalProcessData::getUnicId();
	}
	
	FloatRect ProductCard::getLocalBounds(){
		return group->getLocalBounds();
	}
	
	FloatRect ProductCard::getGlobalBounds(){
		return group->getGlobalBounds();
	}

	short* ProductCard::getPurchaseState(){
		return &purchase_state;
	}
	
	Group* ProductCard::getGroup(){
		return group;
	}

	int* ProductCard::getPrice(){
		return &price;
	}
	
	void ProductCard::setGroup(Group* group_, Color color){
		group = group_;
		group->setBColor(color);
	}

	void ProductCard::setPositionX(float x){
		group->setPositionX(x);
	}
	
	void ProductCard::setPositionY(float y){
		group->setPositionY(y);
	}
	
	void ProductCard::setCurrency(int* curr){
		currency = curr;
	}

	void ProductCard::setAlignment(string h_align, string v_align){
		h_alignment = h_align;
		v_alignment = v_align;
		group->setAlignment(h_alignment, v_alignment);
	}

	void ProductCard::addNotification(short text_size, string text_, Color text_color){
		notification = new Notification(getGlobalBounds(), text_size, text_, text_color);
	}

	void ProductCard::addNotification(short text_size, Color text_color){
		notification = new Notification(getGlobalBounds(), text_size, "+"+std::to_string(amount), text_color);
	}
	
	void ProductCard::changePosition(float offset_x, float offset_y){
		group->changePosition(offset_x, offset_y);
	}
	
	void ProductCard::buy(float param1, float param2){
		if (*currency >= price) {
			*source += amount;
			*currency -= price;
			price *= p_coefficient;
			purchase_state = PURCHASE::PURCHASE_DONE;
			if (notification) {
				notification->activation(0);
			}
		}
	}
	
	void ProductCard::update(){
		if (purchase_state == PURCHASE::PURCHASE_DONE) {
			purchase_state = PURCHASE::PURCHASE_UNDONE;
		}
		group->setAlignment(h_alignment, v_alignment);
		group->update();
		if (notification) {
			notification->update();
		}
	}
	
	void ProductCard::render(){
		group->render();
		if (notification) {
			notification->render();
		}
	}
