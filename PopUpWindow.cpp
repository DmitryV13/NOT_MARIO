#include "stdafx.h"
#include "PopUpWindow.h"


	PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_)
		:width(width_), height(height_), window(window_){

		manager = new TextureManager();

		w_background = new ComposedIMG(width, height, manager, 1);
		w_background->setPosition("center", "center", screen_width, screen_height);
		position = Vector2f(w_background->getLocalBounds().left, w_background->getLocalBounds().top);
	}

	PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, string positionX, string positionY) 
		:width(width_), height(height_), window(window_) {

		manager = new TextureManager();

		w_background = new ComposedIMG(width, height, manager, 1);
		w_background->setPosition(positionX, positionY, screen_width, screen_height);
		position = Vector2f(w_background->getLocalBounds().left, w_background->getLocalBounds().top);
	}

	PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, string positionX, int y) 
		:width(width_), height(height_), window(window_) {

		manager = new TextureManager();

		w_background = new ComposedIMG(width, height, manager, 1);
		w_background->setPosition(positionX, y, screen_width, screen_height);
		position = Vector2f(w_background->getLocalBounds().left, w_background->getLocalBounds().top);
	}

	PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_, int x, string positionY) 
		:width(width_), height(height_), window(window_) {

		manager = new TextureManager();

		w_background = new ComposedIMG(width, height, manager, 1);
		w_background->setPosition(x, positionY, screen_width, screen_height);
		position = Vector2f(w_background->getLocalBounds().left, w_background->getLocalBounds().top);
	}
	
	PopUpWindow::~PopUpWindow(){
	}
	
	void PopUpWindow::setBackground(){
	}
	
	void PopUpWindow::setSize(){
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

	void PopUpWindow::addLabel(double screen_width, double screen_height, const string& label_text, Font* font_, int text_size, short offset){
		label = new Label(label_text, font_, text_size, manager, 0);
		label->setPosition("center", (screen_height - height) / 2 - label->getLocalBounds().height - offset, screen_width, screen_height);
	}

	void PopUpWindow::addGroup(short fill_p_w, short fill_p_h, short index, string name, int name_size, Font* font){
		int new_gposition_y=position.y;
		for (size_t i = 0; i < index; i++){
			new_gposition_y += getMaxGroupsHeight(i);
		}
		Rect<int> f;
		int new_gposition_x = position.x;
		for (size_t i = 0; i < groups[index].size(); i++) {
			new_gposition_x += groups[index][i]->getLocalBounds().width;
		}

		groups[index].push_back(new Group(fill_p_w * width / 100, fill_p_h * height / 100, Vector2f(new_gposition_x, new_gposition_y)));
		groups[index][groups[index].size() - 1]->addGroupName(name, name_size, font);
	}

	void PopUpWindow::addGroup(short fill_p_w, short fill_p_h, short index) {
		int new_gposition_y = position.y;
		for (size_t i = 0; i < index; i++) {
			new_gposition_y += getMaxGroupsHeight(i);
		}
		Rect<int> f;
		int new_gposition_x = position.x;
		for (size_t i = 0; i < groups[index].size(); i++) {
			new_gposition_x += groups[index][i]->getLocalBounds().width;
		}

		groups[index].push_back(new Group(fill_p_w * width / 100, fill_p_h * height / 100, Vector2f(new_gposition_x, new_gposition_y)));
	}

	void PopUpWindow::addGroup(Group* new_group, short index){
		groups[index].push_back(new_group);
	}

	void PopUpWindow::addGroupName(int i, int j, string name, int name_size, Font* font){
		groups[i][j]->addGroupName(name, name_size, font);
	}

	void PopUpWindow::addBackground(double map_width, double map_height, Color color){
		background = new RectangleShape();
		background->setSize(Vector2f(map_width, map_height));
		background->setFillColor(color);
	}
	
	//void PopUpWindow::addButton(){
	//}
	
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

	void PopUpWindow::verifyBtnsPressed(){
	}
	
	void PopUpWindow::update(FloatRect view_cords){
		w_background->update(view_cords);
		label->update(view_cords);

		for (auto i = groups.begin(); i != groups.end(); ++i) {
			for (auto j = i->begin(); j != i->end(); ++j) {
				(*j)->update(Vector2f(Mouse::getPosition(*window)), view_cords);
			}
		}
	}
	
	void PopUpWindow::render(){
		window->draw(*background);
		w_background->render(window);
		label->render(window);

		for (auto i : groups) {
			for (auto j : i) {
				j->render(window);
			}
		}
	}
