#include "stdafx.h"
#include "Group.h"

	Group::Group(int width_, int height_, Vector2f position_)
		: width(width_), height(height_), position(position_){
	}

	FloatRect Group::getLocalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	int Group::getMaxELHeight(short index){
		int height = 0;
		for (size_t i = 0; i < g_elements[index].size(); i++) {
			if (g_elements[index][i]->getLocalBounds().height > height) {
				height = g_elements[index][i]->getLocalBounds().height;
			}
		}
		return height;
	}

	void Group::setAlignment(string horiz_a, string vertic_a){
		if (vertic_a == "space around") {
			float elements_height = 0;
			for (size_t i = 0; i < g_elements.size(); i++){
				elements_height += getMaxELHeight(i);
			}
			float space_arnd = (width - elements_height) / (g_elements.size() + 1);


		}
	}

	void Group::setPosition(float x, float y){
	
	}

	void Group::changePosition(float offset_x, float offset_y){

	}
	
	void Group::createElementLine(){
		g_elements.push_back(vector<InterfaceItem*>());
	}

	void Group::addIElement(InterfaceItem* new_element, short index) {
		g_elements[index].push_back(new_element);
	}

	void Group::addGroupName(string text_name, int name_size, Font* font){
		name = new Text();
		name->setFont(*font);
		name->setString(text_name);
		name->setFillColor(sf::Color::White);
		name->setCharacterSize(name_size);
		name->setOutlineThickness(3.f);
		name->setOutlineColor(sf::Color(0, 0, 0, 0));
		name->setPosition(
			position.x + (width - name->getLocalBounds().width)/2 - name->getLocalBounds().left,
			position.y + (height - name->getLocalBounds().height) / 2 - name->getLocalBounds().top + name->getLocalBounds().height / 4
		);
	}

	void Group::addGroup(short fill_p_w, short fill_p_h, short index){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index; i++) {
			new_eposition_y += getMaxELHeight(i);
		}
		new_eposition_y += 2 * (name == nullptr ? 0 : name->getLocalBounds().width);
		
		int new_eposition_x = position.x;
		for (size_t i = 0; i < g_elements[index].size(); i++) {
			new_eposition_x += g_elements[index][i]->getLocalBounds().width;
		}

		g_elements[index].push_back(new Group(fill_p_w * width / 100, fill_p_h * height / 100, Vector2f(new_eposition_x, new_eposition_y)));
	}



	void Group::addButton(short text_size, sf::Font* font, string btn_name, Color btn_color, short index){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index; i++) {
			new_eposition_y += getMaxELHeight(i);
		}
		new_eposition_y += 2 * (name == nullptr ? 0 : name->getLocalBounds().width);

		int new_eposition_x = position.x;
		for (size_t i = 0; i < g_elements[index].size(); i++) {
			new_eposition_x += g_elements[index][i]->getLocalBounds().width;
		}

		g_elements[index].push_back(new Button(new_eposition_x, new_eposition_y, text_size, font, btn_name, btn_color));
	}


	CRect<float>* Group::calculatePFNII(short fill_p_w, short fill_p_h, short index){
		int new_gposition_y = position.y;
		for (size_t i = 0; i < index; i++) {
			new_gposition_y += getMaxELHeight(i);
		}
		new_gposition_y += 2 * (name == nullptr ? 0 : name->getLocalBounds().height);

		int new_gposition_x = position.x;
		for (size_t i = 0; i < g_elements[index].size(); i++) {
			new_gposition_x += g_elements[index][i]->getLocalBounds().width;
		}

		return new CRect<float>(new_gposition_x, new_gposition_y, fill_p_w * width / 100, fill_p_h * height / 100);
	}

	void Group::update(Vector2f mouse_pos, FloatRect view_cords){
		if (name != nullptr) {
			name->setPosition(
				view_cords.left - view_cords.width / 2 + position.x + (width - name->getLocalBounds().width) / 2 - name->getLocalBounds().left,
				view_cords.top - view_cords.height / 2 + position.y - name->getLocalBounds().top + name->getLocalBounds().height
			);
		}

		for (auto i : g_elements) {
			for (auto j : i) {
				j->update(mouse_pos, view_cords);
			}
		}
	}

	void Group::render(RenderTarget* target){
		if (name != nullptr) {
			target->draw(*name);
		}

		for (auto i : g_elements) {
			for (auto j : i) {
				j->render(target);
			}
		}
	}
