#pragma once
#include "InterfaceItem.h"
#include "Button.h"

using namespace::sf;

class Group : InterfaceItem{
private:
	RectangleShape g0;
	RectangleShape g1;
	RectangleShape g2;

	Text* name;
	vector<vector<InterfaceItem*>> g_elements;
	short vertical_alignment;
	short horizontal_alignment;

	float inner_width;
	float inner_height;
	float outer_width;
	float outer_height;
	Vector2f position;
public:
	Group(int width_, int height_, Vector2f position_);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds();
	int getMaxELHeight(short index);

	void setAlignment(string horiz_a, string vertic_a);
	void setVAlignment(string vertic_a);
	void setHAlignment(string horiz_a);

	void setPositionX(float x) override;
	void setPositionY(float y) override;

	void changePosition(float offset_x, float offset_y) override;

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

