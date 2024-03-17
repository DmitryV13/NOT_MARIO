#pragma once
#include "InterfaceItem.h"
#include "ImageButton.h"
#include "FormItem.h"
#include "InputField.h"

class Group : public InterfaceItem{
protected:
	//Objects for visualization
	RectangleShape g0;
	RectangleShape g1;
	RectangleShape g2;

	//
	RectangleShape background;
	Text* name;
	vector<vector<InterfaceItem*>> g_elements;

	float inner_width;
	float inner_height;
	float outer_width;
	float outer_height;
	Vector2f position;
public:
	Group(float x, float y, float width_, float height_);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;
	float getMaxELHeight(short index);
	short* getButtonState(int btn_id);

	void setAlignment(string horiz_a, string vertic_a);
	void setVAlignment(string vertic_a);
	void setHAlignment(string horiz_a);
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	void setBColor(Color color);

	void changePosition(float offset_x, float offset_y) override;
	void changePositionY(float offset);

	void createElementLine();


	void addIElement(InterfaceItem* new_group, short index);
	void addGroup(short fill_p_w, short fill_p_h, short index);// fill percentage width/height
	void addGroupName(string text_name, int name_size, Font* font);
	void addButton(short text_size, sf::Font* font, string btn_name, Color btn_color, int btn_id, short index_g);
	void addButton(float width, float height, short text_size, sf::Font* font
		, string btn_name, Color btn_hcolor, Color btn_icolor, Color shp_hcolor, Color shp_icolor
		, bool outline, int btn_id, short index_g);
	void addButton(float width, float height, short text_size, sf::Font* font_, string btn_name
		, Color btn_hcolor, Color btn_icolor, Color shp_hcolor, Color shp_icolor
		, TextureManager* t_manager, int index_t, string name, bool outline, int btn_id, short index_g);
	//void addDelimiter();
	//void addSlider();
	
	CRect<float>* calculatePFNII(short fill_p_w, short fill_p_h, short index);
	void resetActiveState() override;

	void formInput(Event event);
	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(RenderTarget* target);
};

