#include "stdafx.h"
#include "Setting.h"

Setting::Setting(RenderWindow* window_, double screen_w, double screen_h, Color menuColor_, TextureManager* t_manager_)
	: window(window_), screen_height(screen_h), screen_width(screen_w), menuColor(menuColor_), t_manager(t_manager_){
	initFont();
	CRect<float>* tmp;

	example = new PopUpAutocWindow(screen_width, screen_height, 1000, 800, window, t_manager);
	example->setWindowName("Window");
	example->createGroupLine();
	tmp = example->calculatePFNG(100, 100, 0);
	Group* ls = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
	delete tmp;

	example->addGroup(ls, 0);

	ls->createElementLine();
	tmp = ls->calculatePFNII(25, 10, 0);
	ls_g0_top = new InputField(tmp->first, tmp->second, tmp->third, tmp->fourth, "input", font, 25, true, 90);
	ls_g0_top->setVisibility(0, 0);
	ls->addIElement((InterfaceItem*)ls_g0_top, 0);

	tmp = ls->calculatePFNII(30, 30, 0);
	ls_g0_top = new TextareaField(tmp->first, tmp->second, tmp->third, tmp->fourth, "textarea", font, 25, true, 600);
	ls->addIElement((InterfaceItem*)ls_g0_top, 0);

	ls->createElementLine();
	tmp = ls->calculatePFNII(25, 10, 1);
	ls_g0_top = new InputField(tmp->first, tmp->second, tmp->third, tmp->fourth, "input", font, 25, true, 90);
	ls->addIElement((InterfaceItem*)ls_g0_top, 1);
	
	tmp = ls->calculatePFNII(30, 30, 1);
	ls_g0_top = new TextareaField(tmp->first, tmp->second, tmp->third, tmp->fourth, "textarea", font, 25, true, 600);
	ls->addIElement((InterfaceItem*)ls_g0_top, 1);
	
	ls->createElementLine();
	tmp = ls->calculatePFNII(20, 10, 0);
	NumberField* ls_g0_top2 = new NumberField(tmp->first, tmp->second, tmp->third, tmp->fourth, "number", font, 25, true, 90);
	ls_g0_top2->setMinMaxType(20, 100, false);
	ls->addIElement((InterfaceItem*)ls_g0_top2, 2);
	
	ls->createElementLine();
	tmp = ls->calculatePFNII(40, 10, 0);
	SliderControl* sl = new SliderControl(tmp->first, tmp->second, tmp->third, tmp->fourth, "slider", font);
	sl->setMinMaxType(0, 100);
	sl->setValueType(new float(), true);
	ls->addIElement((InterfaceItem*)sl, 3);
	
	tmp = ls->calculatePFNII(30, 30, 3);
	ls_g0_top = new TextareaField(tmp->first, tmp->second, tmp->third, tmp->fourth, "textarea", font, 25, true, 600);
	ls->addIElement((InterfaceItem*)ls_g0_top, 3);

	ls->setAlignment("center auto", "center auto");

	example->setPUWState(POP_UP_WINDOW_STATE::PUW_OPENED, 0);
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
		if (example->getState() == POP_UP_WINDOW_STATE::PUW_OPENED) {
			example->updateEvent(&event);
		}
	}
}

void Setting::update(){
	GlobalProcessData::setViewCords(FloatRect(window->getView().getCenter(), Vector2f(screen_width, screen_height)));
	window->setView(View(FloatRect(0, 0, screen_width, screen_height)));
	
	updateEvents();
}

void Setting::initFont(){
	font = new Font();
	if (!font->loadFromFile("Fonts/Pixel.ttf")) {
		std::cout << "Error -> RoadMap -> couldn't load text font" << std::endl;
	}
}

void Setting::render(){
	window->clear(Color::Yellow);

	if (example->getState() == POP_UP_WINDOW_STATE::PUW_OPENED) {
		example->update(FloatRect(window->getView().getCenter(), Vector2f(screen_width, screen_height)));
		example->render();
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
