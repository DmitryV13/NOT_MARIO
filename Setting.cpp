#include "stdafx.h"
#include "Setting.h"

Setting::Setting(RenderWindow* window_, double screen_w, double screen_h, Color menuColor_, TextureManager* t_manager_)
	: window(window_), screen_height(screen_h), screen_width(screen_w), menuColor(menuColor_), t_manager(t_manager_){
	initFont();

	int tmp_id;
	CRect<float>* tmp;

	settings = new PopUpAutocWindow(screen_width, screen_height, 1000, 800, t_manager);
	settings->createGroupLine();
	tmp = settings->calculatePFNG(100, 100, 0);
	Group* s_g0_top = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
	s_g0_top->setBColor(Color::Cyan);
	delete tmp;

	settings->addGroup(s_g0_top, 0);
	
	s_g0_top->createElementLine();
	
	tmp = s_g0_top->calculatePFNII(30, 30, 0);
	InputField* s_if = new TextareaField(tmp->first, tmp->second, tmp->third, tmp->fourth, "textarea", 25, true, 600);
	s_g0_top->addIElement((InterfaceItem*)s_if, 0);
	
	s_g0_top->createElementLine();
	tmp = s_g0_top->calculatePFNII(25, 10, 1);
	s_if = new InputField(tmp->first, tmp->second, tmp->third, tmp->fourth, "input", 25, true, 90);
	s_g0_top->addIElement((InterfaceItem*)s_if, 1);
	
	s_g0_top->createElementLine();
	tmp = s_g0_top->calculatePFNII(25, 10, 1);
	s_if = new InputField(tmp->first, tmp->second, tmp->third, tmp->fourth, "password", 25, true, 90);
	s_if->setVisibility(false);
	s_g0_top->addIElement((InterfaceItem*)s_if, 2);
	
	tmp_id = s_g0_top->addButton(tmp->fourth, tmp->fourth, 40, "", menuColor, Color::White, Color(239, 135, 6, 255)
		, Color(255, 185, 12), t_manager, 0, "EyeB", true, 2);
	settings->addCallback(s_g0_top->getButtonState(tmp_id), BUTTON_STATE::BTN_ACTIVE, 0, 0,
		&InputField::changeVisibility, s_if);
	
	s_g0_top->createElementLine();
	tmp = s_g0_top->calculatePFNII(20, 10, 0);
	NumberField* ls_g0_top2 = new NumberField(tmp->first, tmp->second, tmp->third, tmp->fourth, "number", 25, true, 90);
	ls_g0_top2->setMinMaxType(20, 100, false);
	s_g0_top->addIElement((InterfaceItem*)ls_g0_top2, 3);
	
	s_g0_top->createElementLine();
	tmp = s_g0_top->calculatePFNII(40, 10, 0);
	SliderControl* sl = new SliderControl(tmp->first, tmp->second, tmp->third, tmp->fourth, "slider");
	sl->setMinMaxType(0, 100);
	sl->setValueType(new float(), true);
	s_g0_top->addIElement((InterfaceItem*)sl, 4);
	
	s_g0_top->createElementLine();
	tmp = s_g0_top->calculatePFNII(40, 10, 0);
	tmp_id = s_g0_top->addButton(tmp->third, 60, 20, "MAP BUILDER", menuColor, Color::White,
		Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 5);
	
	
	s_g0_top->createElementLine();
	tmp = s_g0_top->calculatePFNII(40, 10, 0);
	tmp_id = s_g0_top->addButton(tmp->third, 60, 20, "BACK", menuColor, Color::White,
		Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 6);
	settings->addCallback(s_g0_top->getButtonState(tmp_id), BUTTON_STATE::BTN_ACTIVE, 0, 0,
		&Setting::close, (MainMenuOption*)this);

	s_g0_top->setAlignment("center auto", "center auto");

	settings->setPUWState(POP_UP_WINDOW_STATE::PUW_OPENED, 0);
}

void Setting::updateMenuState(){
	if (menu_timer.getElapsedTime().asSeconds() >= 0.2f) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			state = PAGE_STATE::PAGE_CLOSED;
		}
		menu_timer.restart();
	}
}

void Setting::updateEvents(){
	Event event;
	while (window->pollEvent(event)) {
		if (event.type == Event::Closed) {
			window->close();
		}
		if (settings->getState() == POP_UP_WINDOW_STATE::PUW_OPENED) {
			settings->updateEvent(&event);
		}
	}
}

void Setting::update(){
	updateEvents();
}

void Setting::initFont(){
	font = new Font();
	if (!font->loadFromFile("Fonts/Pixel.ttf")) {
		std::cout << "Error -> RoadMap -> couldn't load text font" << std::endl;
	}
}

void Setting::render(){
	window->clear();

	if (settings->getState() == POP_UP_WINDOW_STATE::PUW_OPENED) {
		settings->update();
		settings->render();
	}

	window->display();
}

void Setting::enter(RenderWindow* window){
	state = PAGE_STATE::PAGE_OPENED;
	while (state == PAGE_STATE::PAGE_OPENED) {
		updateMenuState();
		update();
		render();
	}
}
