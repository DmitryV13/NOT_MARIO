#include "stdafx.h"
#include "PopUpWindow.h"


	PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, 
		TextureManager* t_manager_)
		:width(width_), height(height_), puw_state(POP_UP_WINDOW_STATE::PUW_CLOSED){
		callbacks_handler = new CallbacksHandler();
		dcallbacks_handler = new DCallbacksHandler();
		manager = t_manager_;

		w_background = new ComposedIMG(width, height, 6, manager, 2);
		w_background->setPosition("center", "center", screen_width, screen_height);
		position = Vector2f(w_background->getLocalBounds().left, w_background->getLocalBounds().top);
	}

	PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, 
		string positionX, string positionY, TextureManager* t_manager_)
		:width(width_), height(height_), puw_state(POP_UP_WINDOW_STATE::PUW_CLOSED){
		callbacks_handler = new CallbacksHandler();
		dcallbacks_handler = new DCallbacksHandler();
		manager = t_manager_;

		w_background = new ComposedIMG(width, height, 6, manager, 1);
		w_background->setPosition(positionX, positionY, screen_width, screen_height);
		position = Vector2f(w_background->getLocalBounds().left, w_background->getLocalBounds().top);
	}

	PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, 
		string positionX, int y, TextureManager* t_manager_)
		:width(width_), height(height_), puw_state(POP_UP_WINDOW_STATE::PUW_CLOSED){
		callbacks_handler = new CallbacksHandler();
		dcallbacks_handler = new DCallbacksHandler();
		manager = t_manager_;

		w_background = new ComposedIMG(width, height, 6, manager, 1);
		w_background->setPosition(positionX, y, screen_width, screen_height);
		position = Vector2f(w_background->getLocalBounds().left, w_background->getLocalBounds().top);
	}

	PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, 
		int x, string positionY, TextureManager* t_manager_)
		:width(width_), height(height_), puw_state(POP_UP_WINDOW_STATE::PUW_CLOSED){
		callbacks_handler = new CallbacksHandler();
		dcallbacks_handler = new DCallbacksHandler();
		manager = t_manager_;

		w_background = new ComposedIMG(width, height, 6, manager, 1);
		w_background->setPosition(x, positionY, screen_width, screen_height);
		position = Vector2f(w_background->getLocalBounds().left, w_background->getLocalBounds().top);
	}
	
	PopUpWindow::~PopUpWindow(){
		for (auto i : groups) {
			for (auto j : i) {
				delete j;
			}
		}
		delete manager;
		delete w_background;
		delete background;
		delete label;
		delete callbacks_handler;
		delete dcallbacks_handler;
	}
	
	void PopUpWindow::setBackground(){
	}
	
	void PopUpWindow::setSize(){
	}

	void PopUpWindow::setPUWState(float param1, float param2){
		puw_state = static_cast<short>(param1);
		if (puw_state == POP_UP_WINDOW_STATE::PUW_CLOSED) {
			for (auto i : groups) {
				for (auto j : i) {
					j->resetActiveState();
				}
			}
		}
	}

	short PopUpWindow::getState(){
		return puw_state;
	}

	int PopUpWindow::getMaxGroupsHeight(short index){
		int height = 0;
		for (size_t i = 0; i < groups[index].size(); i++){
			if (groups[index][i]->getLocalBounds().height > height) {
				height = groups[index][i]->getLocalBounds().height;
			}
		}
		return height;
	}

	void PopUpWindow::createGroupLine(){
		groups.push_back(vector<Group*>());
	}

	void PopUpWindow::addLabel(double screen_width, double screen_height, const string& label_text, int text_size, short offset){
		label = new Label(label_text, text_size, manager, 0);
		label->setPosition("center", (screen_height - height) / 2 - label->getLocalBounds().height - offset, screen_width, screen_height);
	}

	void PopUpWindow::addGroup(short fill_p_w, short fill_p_h, short index, string name, int name_size){
		int new_gposition_y=position.y;
		for (size_t i = 0; i < index; i++){
			new_gposition_y += getMaxGroupsHeight(i);
		}
		int new_gposition_x = position.x;
		for (size_t i = 0; i < groups[index].size(); i++) {
			new_gposition_x += groups[index][i]->getLocalBounds().width;
		}

		groups[index].push_back(new Group(new_gposition_x, new_gposition_y, fill_p_w * width / 100, fill_p_h * height / 100));
		groups[index][groups[index].size() - 1]->addGroupName(name, name_size);
	}

	void PopUpWindow::addGroup(short fill_p_w, short fill_p_h, short index) {
		int new_gposition_y = position.y;
		for (size_t i = 0; i < index; i++) {
			new_gposition_y += getMaxGroupsHeight(i);
		}
		int new_gposition_x = position.x;
		for (size_t i = 0; i < groups[index].size(); i++) {
			new_gposition_x += groups[index][i]->getLocalBounds().width;
		}

		groups[index].push_back(new Group(new_gposition_x, new_gposition_y, fill_p_w * width / 100, fill_p_h * height / 100));
	}

	void PopUpWindow::addGroup(Group* new_group, short index){
		groups[index].push_back(new_group);
	}

	void PopUpWindow::addGroupName(int i, int j, string name, int name_size){
		groups[i][j]->addGroupName(name, name_size);
	}

	void PopUpWindow::addBackground(double map_width, double map_height, Color color){
		background = new RectangleShape();
		background->setSize(Vector2f(map_width, map_height));
		background->setFillColor(color);
	}
	
	void PopUpWindow::addDelimiter(){
	}
	
	CRect<float>* PopUpWindow::calculatePFNG(short fill_p_w, short fill_p_h, short index){
		int new_gposition_y=position.y;
		for (size_t i = 0; i < index; i++){
			new_gposition_y += getMaxGroupsHeight(i);
		}
		
		int new_gposition_x = position.x;
		for (size_t i = 0; i < groups[index].size(); i++) {
			new_gposition_x += groups[index][i]->getLocalBounds().width;
		}
		
		return new CRect<float>(new_gposition_x, new_gposition_y, fill_p_w * width / 100, fill_p_h * height / 100);
	}
	
	void PopUpWindow::formInput(Event event){
		for (auto i : groups) {
			for (auto j : i) {
				((Group*)j)->formInput(event);
			}
		}
	}

	void PopUpWindow::itemScroll(float delta){
		for (auto i : groups) {
			for (auto j : i) {
				((Group*)j)->itemScroll(delta);
			}
		}
	}

	void PopUpWindow::updateEvent(Event* event){
		if (event->type == Event::TextEntered) {
			formInput(*event);
		}
		if (event->type == Event::MouseWheelScrolled) {
			itemScroll(event->mouseWheelScroll.delta);
		}
	}

	void PopUpWindow::update(){
		w_background->update();
		if(label!=nullptr)
			label->update();

		for (auto i = groups.begin(); i != groups.end(); ++i) {
			for (auto j = i->begin(); j != i->end(); ++j) {
				(*j)->update();
			}
		}

		callbacks_handler->update();
		dcallbacks_handler->update();
	}
	
	void PopUpWindow::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		if(background)
			target->draw(*background);
		w_background->render();
		if (label != nullptr)
			label->render();


		for (auto i : groups) {
			for (auto j : i) {
				j->render();
			}
		}
	}
