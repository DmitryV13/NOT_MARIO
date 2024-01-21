#pragma once
#include "Button.h"
#include "Reviewer.h"
#include "ComposedIMG.h"
#include "Label.h"
#include "Group.h"
#include "BUTTON_STATE.h"
#include "POP_UP_WINDOW_STATE.h"
#include "CallbacksHandler.h"

class PopUpWindow{
private:
	TextureManager* manager;
	RenderWindow* window;
	ComposedIMG* w_background;
	RectangleShape* background;
	Label* label;
	short puw_state;

	CallbacksHandler* callbacks_handler;
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
	void setPUWStateO(float q);
	void setPUWStateC(float q);

	short getState();
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

	template<class T>
	bool addCallback(short* b_state, short a_state, float param, void(T::* l_func)(float), T* l_instance);

	CRect<float>* calculatePFNG(short fill_p_w, short fill_p_h, short index);//parameters for new group
	void verifyBtnsPressed();

	void update(FloatRect view_cords);
	void render();
};

template<class T>
inline bool PopUpWindow::addCallback(short* b_state, short a_state, float param, void(T::* l_func)(float), T* l_instance){
	return callbacks_handler->addCallback(b_state, a_state, param, l_func, l_instance);
}
