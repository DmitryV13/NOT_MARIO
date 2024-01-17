#include "stdafx.h"
#include "Group.h"

	Group::Group(int width_, int height_, Vector2f position_)
		: outer_width(width_), outer_height(height_), inner_width(width_), inner_height(height_), position(position_){
		g0.setSize(Vector2f(width_ - 2, height_ - 2));
		g0.setOutlineThickness(1.f);
		g0.setFillColor(Color(0, 0, 0, 0));

		
		g1.setOutlineThickness(1.f);
		g1.setFillColor(Color(0, 0, 0, 0));

		g2.setOutlineThickness(1.f);
		g2.setFillColor(Color(0, 0, 0, 0));
	}

	FloatRect Group::getLocalBounds(){//inv
		return FloatRect(position, Vector2f(outer_width, outer_height));
	}

	FloatRect Group::getGlobalBounds() {//inv
		return FloatRect(position, Vector2f(inner_width, inner_height));
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
		setVAlignment(vertic_a);
		setHAlignment(horiz_a);
	}

	void Group::setVAlignment(string vertic_a){
		int substring;

		substring = vertic_a.find("space around");
		if (substring != string::npos) {
			float elements_height = 0;
			for (size_t i = 0; i < g_elements.size(); i++) {
				elements_height += getMaxELHeight(i);
			}
			float space_arnd = (inner_height - elements_height) / (g_elements.size() + 1);

			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + space_arnd + position.y
						+ (i - g_elements.begin()) * getMaxELHeight((i - g_elements.begin()))
						+ (i - g_elements.begin()) * space_arnd);
				}
			}
			return;
		}

		substring = vertic_a.find("space between ");
		if (substring != string::npos) {
			string add_parameter = vertic_a.substr(substring + string("space between ").length());
			float elements_height = 0;
			for (size_t i = 0; i < g_elements.size(); i++) {
				elements_height += getMaxELHeight(i);
			}
			float add_offset = 0;
			if (add_parameter == "auto") {
				add_offset = getMaxELHeight(0) / 2;
			}
			else {
				add_offset = stof(add_parameter);
			}
			float space_btwn = (g_elements.size() - 1) != 0 ? (inner_height - elements_height
				- add_offset * 2) / (g_elements.size() - 1) : 0;
			add_offset = (g_elements.size() - 1) == 0 ? ((inner_height - elements_height) / 2) : add_offset;
			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + add_offset + position.y
						+ (i - g_elements.begin()) * getMaxELHeight((i - g_elements.begin()))
						+ (i - g_elements.begin()) * space_btwn);
				}
			}
			return;
		}

		substring = vertic_a.find("center ");
		if (substring != string::npos) {
			string add_parameter = vertic_a.substr(substring + string("center ").length());
			float elements_height = 0;
			for (size_t i = 0; i < g_elements.size(); i++) {
				elements_height += getMaxELHeight(i);
			}
			float add_offset = 0;
			if (add_parameter == "auto") {
				add_offset = getMaxELHeight(0) / 2;
			}
			else {
				add_offset = stof(add_parameter);
			}
			float space_edge = (inner_height - elements_height
				- add_offset * (g_elements.size() - 1)) / 2;

			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + space_edge + position.y
						+ (i - g_elements.begin()) * (getMaxELHeight(i - g_elements.begin()) + add_offset));
				}
			}
			return;
		}

		substring = vertic_a.find("top ");
		if (substring != string::npos) {
			short z = 1;
			string add_parameter;
			if (vertic_a.find("top z ") != string::npos) {
				z = 0;
				add_parameter = vertic_a.substr(substring + string("top z ").length());
			}
			else {
				add_parameter = vertic_a.substr(substring + string("top ").length());
			}
			float add_offset = 0;
			if (add_parameter == "auto") {
				add_offset = getMaxELHeight(0) / 2;
			}
			else {
				add_offset = stof(add_parameter);
			}

			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + z * add_offset + position.y
						+ (i - g_elements.begin()) * (getMaxELHeight(i - g_elements.begin()) + add_offset));
				}
			}
			return;
		}

		substring = vertic_a.find("bottom ");
		if (substring != string::npos) {
			short z = 0;
			string add_parameter;
			if (vertic_a.find("bottom z ") != string::npos) {
				z = 1;
				add_parameter = vertic_a.substr(substring + string("bottom z ").length());
			}
			else {
				add_parameter = vertic_a.substr(substring + string("bottom ").length());
			}
			float elements_height = 0;
			for (size_t i = 0; i < g_elements.size(); i++) {
				elements_height += getMaxELHeight(i);
			}
			float add_offset = 0;
			if (add_parameter == "auto") {
				add_offset = getMaxELHeight(0) / 2;
			}
			else {
				add_offset = stof(add_parameter);
			}
			float space_edge = inner_height - elements_height
				- add_offset * (g_elements.size() - z);

			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + space_edge + position.y
						+ (i - g_elements.begin()) * (getMaxELHeight(i - g_elements.begin()) + add_offset));
				}
			}
			return;
		}
	}

	void Group::setHAlignment(string horiz_a){
		int substring;

		substring = horiz_a.find("space around");
		if (substring != string::npos) {
			for (size_t i = 0; i < g_elements.size(); i++) {
				float elements_width = 0;
				for (size_t j = 0; j < g_elements[i].size(); j++) {
					elements_width += g_elements[i][j]->getLocalBounds().width;
				}
				float space_arnd = (inner_width - elements_width) / (g_elements[i].size() + 1);
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					(*j)->setPositionX(space_arnd + position.x + width_acc
						+ (j - g_elements[i].begin()) * space_arnd);
					width_acc += (*j)->getLocalBounds().width;
				}
			}
			return;
		}

		substring = horiz_a.find("space between ");
		if (substring != string::npos) {
			string add_parameter = horiz_a.substr(substring + string("space between ").length());
			float add_offset = 0;
			if (add_parameter != "auto") {
				add_offset = stof(add_parameter);
			}
			for (size_t i = 0; i < g_elements.size(); i++) {
				float elements_width = 0;
				for (size_t j = 0; j < g_elements[i].size(); j++) {
					elements_width += g_elements[i][j]->getLocalBounds().width;
				}
				if (add_parameter == "auto") {
					add_offset = g_elements[i][0]->getLocalBounds().width/2;
				}
				float space_btwn = (g_elements[i].size() - 1) != 0 ? (inner_width - elements_width
					- add_offset * 2) / (g_elements.size() - 1) : 0;
				add_offset = (g_elements[i].size() - 1) == 0 ? ((inner_width - elements_width) / 2) : add_offset;
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					(*j)->setPositionX(add_offset + position.x
						+ width_acc + (j - g_elements[i].begin()) * space_btwn);
					width_acc += (*j)->getLocalBounds().width;
				}
			}
			return;
		}

		substring = horiz_a.find("center ");
		if (substring != string::npos) {
			string add_parameter = horiz_a.substr(substring + string("center ").length());
			float add_offset = 0;
			if (add_parameter != "auto") {
				add_offset = stof(add_parameter);
			}
			for (size_t i = 0; i < g_elements.size(); i++) {
				float elements_width = 0;
				for (size_t j = 0; j < g_elements[i].size(); j++) {
					elements_width += g_elements[i][j]->getLocalBounds().width;
				}
				if (add_parameter == "auto") {
					add_offset = g_elements[i][0]->getLocalBounds().width / 2;
				}
				float space_edge = (inner_width - elements_width
					- add_offset * (g_elements[i].size() - 1)) / 2;
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					(*j)->setPositionX(space_edge + position.x
						+ width_acc + ((j - g_elements[i].begin()) * add_offset));
					width_acc += (*j)->getLocalBounds().width;
				}
			}
			return;
		}

		substring = horiz_a.find("left ");
		if (substring != string::npos) {
			short z = 1;
			string add_parameter;
			if (horiz_a.find("left z ") != string::npos) {
				z = 0;
				add_parameter = horiz_a.substr(substring + string("left z ").length());
			}
			else {
				add_parameter = horiz_a.substr(substring + string("left ").length());
			}
			float add_offset = 0;
			if (add_parameter != "auto") {
				add_offset = stof(add_parameter);
			}

			for (size_t i = 0; i < g_elements.size(); i++) {
				if (add_parameter == "auto") {
					add_offset = g_elements[i][0]->getLocalBounds().width / 2;
				}
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					(*j)->setPositionX(z * add_offset + position.x
						+ width_acc + ((j - g_elements[i].begin()) * add_offset));
					width_acc += (*j)->getLocalBounds().width;
				}
			}
			return;
		}

		substring = horiz_a.find("right ");
		if (substring != string::npos) {
			short z = 0;
			string add_parameter;
			if (horiz_a.find("right z ") != string::npos) {
				z = 1;
				add_parameter = horiz_a.substr(substring + string("right z ").length());
			}
			else {
				add_parameter = horiz_a.substr(substring + string("right ").length());
			}
			float add_offset = 0;
			if (add_parameter != "auto") {
				add_offset = stof(add_parameter);
			}

			for (size_t i = 0; i < g_elements.size(); i++) {
				float elements_width = 0;
				for (size_t j = 0; j < g_elements[i].size(); j++) {
					elements_width += g_elements[i][j]->getLocalBounds().width;
				}
				if (add_parameter == "auto") {
					add_offset = g_elements[i][0]->getLocalBounds().width / 2;
				}
				float space_edge = inner_width - elements_width
					- add_offset * (g_elements[i].size() - z);
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					(*j)->setPositionX(space_edge + position.x
						+ width_acc + ((j - g_elements[i].begin()) * add_offset));
					width_acc += (*j)->getLocalBounds().width;
				}
			}
			return;
		}
	}

	void Group::setPositionX(float x){
		float offset = x - position.x;

		for (auto i : g_elements) {
			for (auto j : i) {
				j->changePosition(offset, 0);
			}
		}
		changePosition(offset, 0);
	}

	void Group::setPositionY(float y) {
		float offset = y - position.y;

		for (auto i : g_elements) {
			for (auto j : i) {
				j->changePosition(0, offset);
			}
		}
		changePosition(0, offset);
	}

	void Group::changePosition(float offset_x, float offset_y){
		position.x += offset_x;
		position.y += offset_y;
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
			position.x + (outer_width - name->getLocalBounds().width) / 2 - name->getLocalBounds().left,
			position.y + name->getLocalBounds().height / 4 - name->getLocalBounds().top
		);
		inner_height = outer_height - name->getLocalBounds().height - name->getLocalBounds().height / 2;
		g1.setSize(Vector2f(inner_width - 2, inner_height - 2));
		g2.setSize(Vector2f(inner_width - 2, outer_height - inner_height - 2));
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

		g_elements[index].push_back(new Group(fill_p_w * inner_width / 100, fill_p_h * inner_height / 100, Vector2f(new_eposition_x, new_eposition_y)));
	}



	void Group::addButton(short text_size, sf::Font* font, string btn_name, Color btn_color, short index){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index; i++) {
			new_eposition_y += getMaxELHeight(i);
		}
		new_eposition_y += 2 * (name == nullptr ? 0 : name->getLocalBounds().height);

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
		new_gposition_y += outer_height - inner_height;

		int new_gposition_x = position.x;
		for (size_t i = 0; i < g_elements[index].size(); i++) {
			new_gposition_x += g_elements[index][i]->getLocalBounds().width;
		}

		return new CRect<float>(new_gposition_x, new_gposition_y, fill_p_w * inner_width / 100, fill_p_h * inner_height / 100);
	}

	void Group::update(Vector2f mouse_pos, FloatRect view_cords){
		if (name != nullptr) {
			name->setPosition(
				view_cords.left - view_cords.width / 2 + position.x + (outer_width - name->getLocalBounds().width) / 2 - name->getLocalBounds().left,
				view_cords.top - view_cords.height / 2 + position.y - name->getLocalBounds().top + name->getLocalBounds().height/4
			);
		}

		g0.setPosition(position.x + 1, position.y + 1);
		g1.setPosition(position.x + 1, position.y + 1 + outer_height - inner_height);
		g2.setPosition(position.x + 1, position.y + 1);

		if (FloatRect(mouse_pos, Vector2f(100, 100)).intersects(g0.getGlobalBounds())) {
			g0.setOutlineColor(Color::Green);
			g1.setOutlineColor(Color::Blue);
			g2.setOutlineColor(Color::Red);
		}
		else {
			g0.setOutlineColor(Color(0, 0, 0, 0));
			g1.setOutlineColor(Color(0, 0, 0, 0));
			g2.setOutlineColor(Color(0, 0, 0, 0));
		}
		g0.setPosition(view_cords.left - view_cords.width / 2 + g0.getPosition().x,
			view_cords.top - view_cords.height / 2 + g0.getPosition().y
		);
		g1.setPosition(view_cords.left - view_cords.width / 2 + g1.getPosition().x,
			view_cords.top - view_cords.height / 2 + g1.getPosition().y
		);
		g2.setPosition(view_cords.left - view_cords.width / 2 + g2.getPosition().x,
			view_cords.top - view_cords.height / 2 + g2.getPosition().y
		);


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

		//target->draw(g1);
		target->draw(g2);
		target->draw(g0);
	}
