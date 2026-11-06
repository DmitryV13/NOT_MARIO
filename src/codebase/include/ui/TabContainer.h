#pragma once
#include "ui/enums/INTERFACE_ITEM_TYPE.h"
#include "ui/InterfaceItem.h"
#include "ui/Group.h"
#include "ui/Button.h"

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

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	void setPosition(float x, float y);
	void setPositionX(float x) override;
	void setPositionY(float y) override;

	void addTab(Group* tab);

	void changePosition(float offset_x, float offset_y) override;
	void changeCurrentTab(float tab_index);
	
	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(sf::RenderTarget* target) override;
};

