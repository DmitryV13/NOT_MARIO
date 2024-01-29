#include "stdafx.h"
#include "Group.h"

	Group::Group(float x, float y, float width_, float height_)
		: outer_width(width_), outer_height(height_), inner_width(width_), inner_height(height_)
		, position(Vector2f(x, y)){
		ii_type = INTERFACE_ITEM_TYPE::GROUP;
		background.setFillColor(Color(0, 0, 0, 0));

		g0.setSize(Vector2f(width_ - 2, height_ - 2));
		g0.setOutlineThickness(1.f);
		g0.setFillColor(Color(0, 0, 0, 0));
		
		g1.setOutlineThickness(1.f);
		g1.setFillColor(Color(0, 0, 0, 0));

		g2.setOutlineThickness(1.f);
		g2.setFillColor(Color(0, 0, 0, 0));
	}

	FloatRect Group::getGlobalBounds(){
		return FloatRect(position, Vector2f(outer_width, outer_height));
	}

	FloatRect Group::getLocalBounds() {
		return FloatRect(position, Vector2f(inner_width, inner_height));
	}

	float Group::getMaxELHeight(short index){
		float height = 0;
		for (size_t i = 0; i < g_elements[index].size(); i++) {
			if (g_elements[index][i]->getGlobalBounds().height > height) {
				height = g_elements[index][i]->getGlobalBounds().height;
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
			float height_acc = 0;
			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + space_arnd + position.y
						+ height_acc + (i - g_elements.begin()) * space_arnd);
				}
				height_acc += getMaxELHeight(i - g_elements.begin());
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
			float height_acc = 0;
			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + add_offset + position.y
						+ height_acc + (i - g_elements.begin()) * space_btwn);
				}
				height_acc += getMaxELHeight(i - g_elements.begin());
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
			float height_acc = 0;
			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					float el_offset = (getMaxELHeight(i - g_elements.begin()) - (*j)->getGlobalBounds().height) / 2;
					(*j)->setPositionY(outer_height - inner_height + space_edge + position.y
						+ height_acc + el_offset + (i - g_elements.begin()) * add_offset);
				}
				height_acc += getMaxELHeight(i - g_elements.begin());
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
			float height_acc = 0;
			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + z * add_offset + position.y
						+ height_acc + ((i - g_elements.begin()) * add_offset));
				}
				height_acc += getMaxELHeight(i - g_elements.begin());
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
			float height_acc = 0;
			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + space_edge + position.y
						+ height_acc + ((i - g_elements.begin()) * add_offset));
				}
				height_acc += getMaxELHeight(i - g_elements.begin());
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
					elements_width += g_elements[i][j]->getGlobalBounds().width;
				}
				float space_arnd = (inner_width - elements_width) / (g_elements[i].size() + 1);
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					(*j)->setPositionX(space_arnd + position.x + width_acc
						+ (j - g_elements[i].begin()) * space_arnd);
					width_acc += (*j)->getGlobalBounds().width;
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
					elements_width += g_elements[i][j]->getGlobalBounds().width;
				}
				if (add_parameter == "auto") {
					add_offset = g_elements[i][0]->getGlobalBounds().width/2;
				}
				float space_btwn = (g_elements[i].size() - 1) != 0 ? (inner_width - elements_width
					- add_offset * 2) / (g_elements[i].size() - 1) : 0;
				add_offset = (g_elements[i].size() - 1) == 0 ? ((inner_width - elements_width) / 2) : add_offset;
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					float r = add_offset + position.x
						+ width_acc + (j - g_elements[i].begin()) * space_btwn;
					(*j)->setPositionX(add_offset + position.x
						+ width_acc + (j - g_elements[i].begin()) * space_btwn);
					width_acc += (*j)->getGlobalBounds().width;
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
					elements_width += g_elements[i][j]->getGlobalBounds().width;
				}
				if (add_parameter == "auto") {
					add_offset = g_elements[i][0]->getGlobalBounds().width / 2;
				}
				float space_edge = (inner_width - elements_width
					- add_offset * (g_elements[i].size() - 1)) / 2;
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					(*j)->setPositionX(space_edge + position.x
						+ width_acc + ((j - g_elements[i].begin()) * add_offset));
					width_acc += (*j)->getGlobalBounds().width;
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
					add_offset = g_elements[i][0]->getGlobalBounds().width / 2;
				}
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					(*j)->setPositionX(z * add_offset + position.x
						+ width_acc + ((j - g_elements[i].begin()) * add_offset));
					width_acc += (*j)->getGlobalBounds().width;
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
					elements_width += g_elements[i][j]->getGlobalBounds().width;
				}
				if (add_parameter == "auto") {
					add_offset = g_elements[i][0]->getGlobalBounds().width / 2;
				}
				float space_edge = inner_width - elements_width
					- add_offset * (g_elements[i].size() - z);
				float width_acc = 0;
				for (auto j = g_elements[i].begin(); j != g_elements[i].end(); ++j) {
					(*j)->setPositionX(space_edge + position.x
						+ width_acc + ((j - g_elements[i].begin()) * add_offset));
					width_acc += (*j)->getGlobalBounds().width;
				}
			}
			return;
		}
	}

	void Group::setPositionX(float x){
		float offset = x - position.x;
		changePosition(offset, 0);
	}

	void Group::setPositionY(float y) {
		float offset = y - position.y;
		changePosition(0, offset);
	}

	void Group::setBColor(Color color){
		background.setFillColor(color);
		background.setPosition(position);
		background.setSize(Vector2f(outer_width, outer_height));
	}

	void Group::changePosition(float offset_x, float offset_y){
		position.x += offset_x;
		position.y += offset_y;
		for (auto i : g_elements) {
			for (auto j : i) {
				j->changePosition(offset_x, offset_y);
			}
		}
		background.setPosition(position);
	}

	void Group::changePositionY(float offset){
		changePosition(0, offset);
	}
	
	void Group::createElementLine(){
		g_elements.push_back(vector<InterfaceItem*>());
	}

	short* Group::getButtonState(int btn_id){
		for (int i = 0; i < g_elements.size(); i++){
			for (int j = 0; j < g_elements[i].size(); j++) {
				if (g_elements[i][j]->getIIType() == INTERFACE_ITEM_TYPE::BUTTON) {
					//string u = static_cast<Button*>(g_elements[i][j])->getName();
					if (static_cast<Button*>(g_elements[i][j])->getIdentificator() == btn_id) {
						return static_cast<Button*>(g_elements[i][j])->getButtonState();
					}
				}
			}
		}
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
			new_eposition_x += g_elements[index][i]->getGlobalBounds().width;
		}

		g_elements[index].push_back(new Group(new_eposition_x, new_eposition_y, fill_p_w * inner_width / 100, fill_p_h * inner_height / 100));
	}



	void Group::addButton(short text_size, sf::Font* font, string btn_name, Color btn_color, int btn_id, short index_g){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index_g; i++) {
			new_eposition_y += getMaxELHeight(i);
		}
		new_eposition_y += outer_height-inner_height;

		int new_eposition_x = position.x;
		for (size_t i = 0; i < g_elements[index_g].size(); i++) {
			new_eposition_x += g_elements[index_g][i]->getGlobalBounds().width;
		}
		g_elements[index_g].push_back(new Button(new_eposition_x, new_eposition_y, text_size, font, btn_name, btn_color, btn_id));
	}

	void Group::addButton(float width, float height, short text_size, sf::Font* font
		, string btn_name, Color btn_hcolor, Color btn_icolor, Color shp_hcolor, Color shp_icolor
		, bool outline, int btn_id, short index_g){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index_g; i++) {
			new_eposition_y += getMaxELHeight(i);
		}
		new_eposition_y += outer_height - inner_height;

		int new_eposition_x = position.x;
		for (size_t i = 0; i < g_elements[index_g].size(); i++) {
			new_eposition_x += g_elements[index_g][i]->getGlobalBounds().width;
		}
		Button* btn = new Button(new_eposition_x, new_eposition_y, width, height, text_size, font, btn_name, outline, btn_id);
		btn->setColors(btn_hcolor, btn_icolor, shp_hcolor, shp_icolor);
		g_elements[index_g].push_back(btn);
	}

	void Group::addButton(float width, float height, short text_size, sf::Font* font, string btn_name
		, Color btn_hcolor, Color btn_icolor, Color shp_hcolor, Color shp_icolor, TextureManager* t_manager
		, int index_t, string name, bool outline, int btn_id, short index_g){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index_g; i++) {
			new_eposition_y += getMaxELHeight(i);
		}
		new_eposition_y += outer_height - inner_height;

		int new_eposition_x = position.x;
		for (size_t i = 0; i < g_elements[index_g].size(); i++) {
			new_eposition_x += g_elements[index_g][i]->getGlobalBounds().width;
		}
		ImageButton* btn = new ImageButton(new_eposition_x, new_eposition_y, width, height, text_size, font, btn_name, t_manager, index_t, name, outline, btn_id);
		btn->setColors(btn_hcolor, btn_icolor, shp_hcolor, shp_icolor);
		g_elements[index_g].push_back(btn);
	}


	CRect<float>* Group::calculatePFNII(short fill_p_w, short fill_p_h, short index){
		int new_gposition_y = position.y;
		for (size_t i = 0; i < index; i++) {
			new_gposition_y += getMaxELHeight(i);
		}
		new_gposition_y += outer_height - inner_height;

		int new_gposition_x = position.x;
		for (size_t i = 0; i < g_elements[index].size(); i++) {
			new_gposition_x += g_elements[index][i]->getGlobalBounds().width;
		}

		return new CRect<float>(new_gposition_x, new_gposition_y, fill_p_w * inner_width / 100, fill_p_h * inner_height / 100);
	}

	void Group::resetActiveState(){
		for (int i = 0; i < g_elements.size(); i++) {
			for (int j = 0; j < g_elements[i].size(); j++) {
				g_elements[i][j]->resetActiveState();
			}
		}
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
		background.setPosition(position);
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

		background.setPosition(view_cords.left - view_cords.width / 2 + position.x,
			view_cords.top - view_cords.height / 2 + position.y
		);
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
		target->draw(background);
		if (name != nullptr) {
			target->draw(*name);
		}

		for (auto i : g_elements) {
			for (auto j : i) {
				j->render(target);
			}
		}

		//target->draw(g1);
		// 
		
		//target->draw(g2);
		//target->draw(g0);
	}
