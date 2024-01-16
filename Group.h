#pragma once
#include "InterfaceItem.h"
#include "Button.h"

using namespace::sf;

class Group : InterfaceItem{
private:
	Text* name;
	vector<vector<InterfaceItem*>> g_elements;

	short vertical_alignment;
	short horizontal_alignment;

	int width;
	int height;
	Vector2f position;
public:
	Group(int width_, int height_, Vector2f position_);

	FloatRect getLocalBounds() override;
	int getMaxELHeight(short index);

	void setAlignment(string horiz_a, string vertic_a);
	void setPosition(float x, float y);

	void changePosition(float offset_x, float offset_y);

	void createElementLine();

	void addIElement(InterfaceItem* new_group, short index);
	void addGroup(short fill_p_w, short fill_p_h, short index);// fill percentage width/height
	void addGroupName(string text_name, int name_size, Font* font);
	void addButton(short text_size, sf::Font* font, string btn_name, Color btn_color, short index);
	//void addDelimiter();
	//void addSlider();
	//void addCard();
	
	CRect<float>* calculatePFNII(short fill_p_w, short fill_p_h, short index);

	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(RenderTarget* target);
};

