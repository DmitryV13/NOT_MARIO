#pragma once
#include "INTERFACE_ITEM_TYPE.h"
#include "InterfaceItem.h"
#include "Group.h"
#include "Button.h"

using namespace::sf;

class TabContainer: public InterfaceItem{
private:
	short current_tab;
	vector<Group*> tabs;

	float width;
	float height;
	Vector2f position;
public:
	TabContainer(float x, float y, float width_, float height_);
	~TabContainer();

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	void setPosition(float x, float y);
	void setPositionX(float x) override;
	void setPositionY(float y) override;

	void addTab(Group* tab);

	void changePosition(float offset_x, float offset_y) override;
	void changeCurrentTab(float tab_index, float param2);
	
	void update() override;
	void render() override;
};

