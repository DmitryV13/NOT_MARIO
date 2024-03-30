#pragma once
#include "Button.h"
#include "Reviewer.h"
#include "ComposedIMG.h"
#include "Label.h"
#include "Group.h"
#include "BUTTON_STATE.h"
#include "POP_UP_WINDOW_STATE.h"
#include "CallbacksHandler.h"
#include "DCallbacksHandler.h"

class PopUpWindow{
private:
	TextureManager* manager;
	RenderWindow* window;
	ComposedIMG* w_background;
	RectangleShape* background;
	Label* label;
	short puw_state;

	CallbacksHandler* callbacks_handler;
	DCallbacksHandler* dcallbacks_handler;
	//inner clean parameters
	int width;
	int height;

	Vector2f position;
	//void *textInput;

	vector<vector<Group*>> groups;
public:
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, 
		TextureManager* t_manager_);
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, 
		string positionX, string positionY, TextureManager* t_manager_);
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, 
		string positionX, int y, TextureManager* t_manager_);
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, 
		int x, string positionY, TextureManager* t_manager_);
	~PopUpWindow();

	void setBackground();
	void setSize();
	void setPUWState(float param1, float param2);

	short getState();
	int getMaxGroupsHeight(short index);

	void createGroupLine();

	void addLabel(double screen_width, double screen_height, const string& label_text, Font* font_, int text_size, short offset);
	void addGroup(short fill_p_w, short fill_p_h, short index, string name, int name_size, Font* font);// fill percentage width/height
	void addGroup(short fill_p_w, short fill_p_h, short index);
	void addGroup(Group* new_group, short index);
	void addGroupName(int i, int j, string name, int name_size, Font* font);
	void addBackground(double map_width, double map_height, Color color);
	void addDelimiter();

	template<class T>
	bool addCallback(short* b_state, short a_state, float param1, float param2, void(T::* l_func)(float, float), T* l_instance);

	template<class T>
	bool addDCallback(short* b_state, short a_state, string* param1, string* param2, void(T::* l_func)(string*, string*), T* l_instance);

	CRect<float>* calculatePFNG(short fill_p_w, short fill_p_h, short index);//parameters for new group

	void formInput(Event event);
	void itemScroll(float delta);
	void update(FloatRect view_cords);
	void updateEvent(Event* event);
	void render();
};

template<class T>
inline bool PopUpWindow::addCallback(short* b_state, short a_state, float param1, float param2, void(T::* l_func)(float, float), T* l_instance){
	return callbacks_handler->addCallback(b_state, a_state, param1, param2, l_func, l_instance);
}

template<class T>
inline bool PopUpWindow::addDCallback(short* b_state, short a_state, string* param1, string* param2, void(T::* l_func)(string*, string*), T* l_instance) {
	return dcallbacks_handler->addCallback(b_state, a_state, param1, param2, l_func, l_instance);
}
