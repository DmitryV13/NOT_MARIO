#include "stdafx.h"
#include "ProductCard.h"

	ProductCard::ProductCard(int price_, int amount_, int* source_)
	: price(price_), amount(amount_), source(source_){
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
	
	void ProductCard::changePosition(float offset_x, float offset_y){
		group->changePosition(offset_x, offset_y);
	}
	
	void ProductCard::buy(float q){
		if (*currency >= price) {
			*source += amount;
			*currency -= price;
			price *= 2;
			purchase_state = PURCHASE::PURCHASE_DONE;
		}
	}
	
	void ProductCard::update(Vector2f mouse_pos, FloatRect view_cords){
		if (purchase_state == PURCHASE::PURCHASE_DONE) {
			purchase_state = PURCHASE::PURCHASE_UNDONE;
		}
		group->setAlignment(h_alignment, v_alignment);
		group->update(mouse_pos, view_cords);
	}
	
	void ProductCard::render(sf::RenderTarget* target){
		group->render(target);
	}
