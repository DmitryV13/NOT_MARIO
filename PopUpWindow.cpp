#include "stdafx.h"
#include "PopUpWindow.h"


	PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_)
		:width(width_), height(height_), window(window_){

		manager = new TextureManager();

		w_background = new ComposedIMG(width, height, manager, 1);
		w_background->setPosition("center", "center", screen_width, screen_height);

		//label = new Label(label_text, font, text_size, manager, 0);
		//label->setPosition("center", (screen_height - 800) / 2 - label->getLocalBounds().height - 10, screen_width, screen_height);
	}
	
	PopUpWindow::~PopUpWindow(){
	}
	
	void PopUpWindow::setBackground(){
	}
	
	void PopUpWindow::setSize(){
	}

	void PopUpWindow::addLabel(double screen_width, double screen_height, const string& label_text, Font* font_, int text_size, short offset){
		label = new Label(label_text, font_, text_size, manager, 0);
		label->setPosition("center", (screen_height - height) / 2 - label->getLocalBounds().height - offset, screen_width, screen_height);
	}

	void PopUpWindow::addBackground(double map_width, double map_height, Color color){
		background = new RectangleShape();
		background->setSize(Vector2f(map_width, map_height));
		background->setFillColor(color);
	}
	
	void PopUpWindow::addWButton(){
	}
	
	void PopUpWindow::addNWButton(){
	}
	
	void PopUpWindow::addDelimiter(){
	}
	
	void PopUpWindow::verifyBtnsPressed(){
	}
	
	void PopUpWindow::update(FloatRect view_cords){
		w_background->update(view_cords);
		label->update(view_cords);
		//background_S.setPosition(view_cords.left + (view_cords.width - width) / 2 - view_cords.width / 2, view_cords.top + (view_cords.height - height) / 2 - view_cords.height / 2);
		//label_S.setPosition(view_cords.left + (view_cords.width - label_S.getLocalBounds().width) / 2 - view_cords.width / 2, view_cords.top + (view_cords.height - height) / 2 - label_S.getLocalBounds().height - view_cords.height / 2 - 10);
	}
	
	void PopUpWindow::render(){
		window->draw(*background);
		w_background->render(window);
		label->render(window);
		//window->draw(background_S);
		//window->draw(label_S);
	}
