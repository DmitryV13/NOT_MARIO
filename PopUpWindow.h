#pragma once
#include "Button.h"
#include "ComposedIMG.h"
#include "Label.h"
#include "Group.h"

using namespace sf;

class PopUpWindow{
private:
	TextureManager* manager;
	RenderWindow* window;
	ComposedIMG* w_background;
	RectangleShape* background;
	Label* label;

	//inner clean parameters
	int width;
	int height;

	Vector2f position;
	short vertical_alignment;
	short horizontal_alignment;
	short state;
	void *textInput;

	vector<vector<Group*>> groups;
public:
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_);
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, string positionX, string positionY);
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, string positionX, int y);
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, int x, string positionY);
	~PopUpWindow();

	void setBackground();
	void setSize();

	int getMaxGroupsHeight(short index);

	void createGroupLine();

	void addLabel(double screen_width, double screen_height, const string& label_text, Font* font_, int text_size, short offset);
	void addGroup(short fill_p_w, short fill_p_h, short index, string name, int name_size, Font* font);// fill percentage width/height
	void addGroup(short fill_p_w, short fill_p_h, short index);
	void addGroup(Group* new_group, short index);
	void addGroupName(int i, int j, string name, int name_size, Font* font);
	void addBackground(double map_width, double map_height, Color color);
	//void addButton();
	void addDelimiter();

	CRect<float>* calculatePFNG(short fill_p_w, short fill_p_h, short index);//parameters for new group
	void verifyBtnsPressed();

	void update(FloatRect view_cords);
	void render();
};

