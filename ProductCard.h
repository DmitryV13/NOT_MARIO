#pragma once
#include "Group.h"
#include "InterfaceItem.h"
#include "INTERFACE_ITEM_TYPE.h"
#include "PURCHASE.h"
#include "Notification.h"

using namespace::sf;

class ProductCard : public InterfaceItem{
private:
	Group* group;

	int price;
	int amount;
	float p_coefficient;
	int* source;
	int* currency;

	short purchase_state;
	string h_alignment;
	string v_alignment;
	Notification* notification;
public:
	ProductCard(int price, int amount, float p_coefficient, int* source);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;
	short* getPurchaseState();
	Group* getGroup();
	int* getPrice();

	void setGroup(Group* group_, Color color);
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	void setCurrency(int* curr);
	void setAlignment(string v_align, string h_align);
	void addNotification(short text_size, string text_, Color text_color);
	void addNotification(short text_size, Color text_color);

	void changePosition(float offset_x, float offset_y) override;

	void buy(float param1, float param2);

	void update() override;
	void render() override;
};

