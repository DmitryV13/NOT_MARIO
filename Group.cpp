#include "stdafx.h"
#include "Group.h"

	Group::Group(float x, float y, float width_, float height_)
		: outer_width(width_), outer_height(height_), inner_width(width_), inner_height(height_)
		, position(Vector2f(x, y)){
		ii_type = INTERFACE_ITEM_TYPE::GROUP;
		id = GlobalProcessData::getUnicId();
		is_scrollable = true;

		background.setFillColor(Color(0, 0, 0, 0));

		shape0.setSize(Vector2f(width_ - 2, height_ - 2));
		shape0.setOutlineThickness(1.f);
		shape0.setFillColor(Color(0, 0, 0, 0));
		
		shape1.setOutlineThickness(1.f);
		shape1.setFillColor(Color(0, 0, 0, 0));

		shape2.setOutlineThickness(1.f);
		shape2.setFillColor(Color(0, 0, 0, 0));
	}

	Group::~Group(){
		clearInfo();
		delete name;
	}

	FloatRect Group::getGlobalBounds(){
		return FloatRect(position, Vector2f(outer_width, outer_height));
	}

	FloatRect Group::getLocalBounds() {
		Vector2f pos;
		pos.x = position.x;
		pos.y = outer_height - inner_height + position.y;
		return FloatRect(pos, Vector2f(inner_width, inner_height));
	}

	std::pair<float, float> Group::getMaxELHeight(short index){
		float height = 0;
		float pos_y = g_elements[0][0]->getGlobalBounds().top;
		for (size_t i = 0; i < g_elements[index].size(); i++) {
			if (g_elements[index][i]->getGlobalBounds().height > height) {
				height = g_elements[index][i]->getGlobalBounds().height;
				pos_y = g_elements[index][i]->getGlobalBounds().top;
			}
		}
		return {pos_y, height };
	}

	void Group::setAlignment(string horiz_a, string vertic_a){
		setVAlignment(vertic_a);
		setHAlignment(horiz_a);
		normalization();
	}

	void Group::setVAlignment(string vertic_a){
		int substring;

		substring = vertic_a.find("space around");
		if (substring != string::npos) {
			float elements_height = 0;
			for (size_t i = 0; i < g_elements.size(); i++) {
				elements_height += getMaxELHeight(i).second;
			}
			float space_arnd = (inner_height - elements_height) / (g_elements.size() + 1);
			float height_acc = 0;
			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					(*j)->setPositionY(outer_height - inner_height + space_arnd + position.y
						+ height_acc + (i - g_elements.begin()) * space_arnd);
				}
				height_acc += getMaxELHeight(i - g_elements.begin()).second;
			}
			return;
		}

		substring = vertic_a.find("space between ");
		if (substring != string::npos) {
			string add_parameter = vertic_a.substr(substring + string("space between ").length());
			float elements_height = 0;
			for (size_t i = 0; i < g_elements.size(); i++) {
				elements_height += getMaxELHeight(i).second;
			}
			float add_offset = 0;
			if (add_parameter == "auto") {
				add_offset = getMaxELHeight(0).second / 2;
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
				height_acc += getMaxELHeight(i - g_elements.begin()).second;
			}
			return;
		}

		substring = vertic_a.find("center ");
		if (substring != string::npos) {
			string add_parameter = vertic_a.substr(substring + string("center ").length());
			float elements_height = 0;
			for (size_t i = 0; i < g_elements.size(); i++) {
				elements_height += getMaxELHeight(i).second;
			}
			float add_offset = 0;
			if (add_parameter == "auto") {
				add_offset = getMaxELHeight(0).second / 2;
			}
			else {
				add_offset = stof(add_parameter);
			}
			float space_edge = (inner_height - elements_height
				- add_offset * (g_elements.size() - 1)) / 2;
			float height_acc = 0;
			for (auto i = g_elements.begin(); i != g_elements.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					float el_offset = (getMaxELHeight(i - g_elements.begin()).second - (*j)->getGlobalBounds().height) / 2;
					(*j)->setPositionY(outer_height - inner_height + space_edge + position.y
						+ height_acc + el_offset + (i - g_elements.begin()) * add_offset);
				}
				height_acc += getMaxELHeight(i - g_elements.begin()).second;
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
				add_offset = getMaxELHeight(0).second / 2;
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
				height_acc += getMaxELHeight(i - g_elements.begin()).second;
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
				elements_height += getMaxELHeight(i).second;
			}
			float add_offset = 0;
			if (add_parameter == "auto") {
				add_offset = getMaxELHeight(0).second / 2;
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
				height_acc += getMaxELHeight(i - g_elements.begin()).second;
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

	void Group::normalization(){
		float initial_position_y = position.y + outer_height - inner_height;
		float content_height = getMaxELHeight(g_elements.size() - 1).first + getMaxELHeight(g_elements.size() - 1).second;
			- getMaxELHeight(0).first;
		if (content_height > inner_height) {
			overflow_y = true;
			float offset = initial_position_y - getMaxELHeight(0).first;
			if (offset > 0) {
				for (auto i : g_elements) {
					for (auto j : i) {
						j->changePosition(0, offset + 20);
					}
				}
			}
		}
	}

	void Group::changeChildrenPosition(float offset_x, float offset_y){
		for (auto i : g_elements) {
			for (auto j : i) {
				j->changePosition(offset_x, offset_y);
			}
		}
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

	void Group::clearInfo(){
		for (auto i : g_elements) {
			for (auto j : i) {
				delete j;
			}
		}
		g_elements.clear();
	}

	short* Group::getButtonState(int btn_id){
		for (int i = 0; i < g_elements.size(); i++){
			for (int j = 0; j < g_elements[i].size(); j++) {
				if (g_elements[i][j]->getIIType() == INTERFACE_ITEM_TYPE::BUTTON) {
					//string u = static_cast<Button*>(g_elements[i][j])->getName();
					if (static_cast<Button*>(g_elements[i][j])->getId() == btn_id) {
						return static_cast<Button*>(g_elements[i][j])->getButtonState();
					}
				}
			}
		}
	}

	void Group::addIElement(InterfaceItem* new_element, short index) {
		g_elements[index].push_back(new_element);
	}

	void Group::addGroupName(string text_name, int name_size){
		name = new Text();
		name->setFont(*GlobalProcessData::getFont());
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
		shape1.setSize(Vector2f(inner_width - 2, inner_height - 2));
		shape2.setSize(Vector2f(inner_width - 2, outer_height - inner_height - 2));
	}

	int Group::addGroup(short fill_p_w, short fill_p_h, short index){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index; i++) {
			new_eposition_y += getMaxELHeight(i).second;
		}
		new_eposition_y += 2 * (name == nullptr ? 0 : name->getLocalBounds().width);
		
		int new_eposition_x = position.x;
		for (size_t i = 0; i < g_elements[index].size(); i++) {
			new_eposition_x += g_elements[index][i]->getGlobalBounds().width;
		}
		Group* tmp = new Group(new_eposition_x, new_eposition_y, fill_p_w * inner_width / 100, fill_p_h * inner_height / 100);
		g_elements[index].push_back(tmp);
		return tmp->getId();
	}



	int Group::addButton(short text_size, string btn_name, Color btn_color, short index_g){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index_g; i++) {
			new_eposition_y += getMaxELHeight(i).second;
		}
		new_eposition_y += outer_height-inner_height;

		int new_eposition_x = position.x;
		for (size_t i = 0; i < g_elements[index_g].size(); i++) {
			new_eposition_x += g_elements[index_g][i]->getGlobalBounds().width;
		}
		Button* tmp = new Button(new_eposition_x, new_eposition_y, text_size, btn_name, btn_color);
		g_elements[index_g].push_back(tmp);
		return tmp->getId();
	}

	int Group::addButton(float width, float height, short text_size
		, string btn_name, Color btn_hcolor, Color btn_icolor, Color shp_hcolor, Color shp_icolor
		, bool outline, short index_g){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index_g; i++) {
			new_eposition_y += getMaxELHeight(i).second;
		}
		new_eposition_y += outer_height - inner_height;

		int new_eposition_x = position.x;
		for (size_t i = 0; i < g_elements[index_g].size(); i++) {
			new_eposition_x += g_elements[index_g][i]->getGlobalBounds().width;
		}
		Button* tmp = new Button(new_eposition_x, new_eposition_y, width, height, text_size, btn_name, outline);
		tmp->setColors(btn_hcolor, btn_icolor, shp_hcolor, shp_icolor);
		g_elements[index_g].push_back(tmp);
		return tmp->getId();
	}

	int Group::addButton(float width, float height, short text_size, string btn_name
		, Color btn_hcolor, Color btn_icolor, Color shp_hcolor, Color shp_icolor, TextureManager* t_manager
		, int index_t, string name, bool outline, short index_g){
		int new_eposition_y = position.y;
		for (size_t i = 0; i < index_g; i++) {
			new_eposition_y += getMaxELHeight(i).second;
		}
		new_eposition_y += outer_height - inner_height;

		int new_eposition_x = position.x;
		for (size_t i = 0; i < g_elements[index_g].size(); i++) {
			new_eposition_x += g_elements[index_g][i]->getGlobalBounds().width;
		}
		ImageButton* tmp = new ImageButton(new_eposition_x, new_eposition_y, width, height, text_size, btn_name, t_manager, index_t, name, outline);
		tmp->setColors(btn_hcolor, btn_icolor, shp_hcolor, shp_icolor);
		g_elements[index_g].push_back(tmp);
		return tmp->getId();
	}


	CRect<float>* Group::calculatePFNII(short fill_p_w, short fill_p_h, short index){
		int new_gposition_y = position.y;
		for (size_t i = 0; i < index; i++) {
			new_gposition_y += getMaxELHeight(i).second;
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

	bool Group::itemScroll(float delta){
		bool was_scrolling = false;

		for (int i = 0; i < g_elements.size(); i++) {
			for (int j = 0; j < g_elements[i].size(); j++) {
				was_scrolling |= g_elements[i][j]->itemScroll(delta);
				if (was_scrolling)
					return true;
			}
		}

		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();
		if (getGlobalBounds().contains(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
			if (overflow_y) {
				float initial_position_y = position.y + outer_height - inner_height;
				float offset = delta * 16;
				if (delta > 0) {
					if (getMaxELHeight(0).first - 20 + offset >= initial_position_y) {
						offset=initial_position_y - getMaxELHeight(0).first;
						changeChildrenPosition(0, offset + 20);
					}
					else {
						changeChildrenPosition(0, offset);
					}
				}
				else {
					if (getMaxELHeight(g_elements.size() - 1).first +
						getMaxELHeight(g_elements.size() - 1).second + 20 + offset <= position.y + inner_height) {
						offset = position.y + inner_height - (getMaxELHeight(g_elements.size() - 1).first +
							getMaxELHeight(g_elements.size() - 1).second) - 20;
						changeChildrenPosition(0, offset);
					}
					else {
						changeChildrenPosition(0, offset);
					}
				}
				return true;
			}
		}
		return false;
	}

	void Group::formInput(Event event){
		for (auto i : g_elements) {
			for (auto j : i) {
				if (j->getIIType() == INTERFACE_ITEM_TYPE::FORM_ITEM) {
					switch (dynamic_cast<FormItem*>(j)->getFIType()) {
					case FORM_ITEM_TYPE::INPUT_FIELD:
						((InputField*)j)->formEInput(event);
						break;
					case FORM_ITEM_TYPE::TEXTAREA_FIELD:
						((TextareaField*)j)->formEInput(event);
						break;
					case FORM_ITEM_TYPE::NUMBER_FIELD:
						((NumberField*)j)->formEInput(event);
						break;
					}
				}
				else if (j->getIIType() == INTERFACE_ITEM_TYPE::GROUP) {
					((Group*)j)->formInput(event);
				}
			}
		}
	}

	void Group::update(){
		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();
		if (name != nullptr) {
			name->setPosition(
				view_cords.left - view_cords.width / 2 + position.x + (outer_width - name->getLocalBounds().width) / 2 - name->getLocalBounds().left,
				view_cords.top - view_cords.height / 2 + position.y - name->getLocalBounds().top + name->getLocalBounds().height/4
			);
		}

		shape0.setPosition(position.x + 1, position.y + 1);
		shape1.setPosition(position.x + 1, position.y + 1 + outer_height - inner_height);
		shape2.setPosition(position.x + 1, position.y + 1);
		background.setPosition(position);
		if (FloatRect(mouse_pos, Vector2f(100, 100)).intersects(shape0.getGlobalBounds())) {
			shape0.setOutlineColor(Color::Green);
			shape1.setOutlineColor(Color::Blue);
			shape2.setOutlineColor(Color::Red);
		}
		else {
			shape0.setOutlineColor(Color(0, 0, 0, 0));
			shape1.setOutlineColor(Color(0, 0, 0, 0));
			shape2.setOutlineColor(Color(0, 0, 0, 0));
		}

		background.setPosition(view_cords.left - view_cords.width / 2 + position.x,
			view_cords.top - view_cords.height / 2 + position.y
		);
		shape0.setPosition(view_cords.left - view_cords.width / 2 + shape0.getPosition().x,
			view_cords.top - view_cords.height / 2 + shape0.getPosition().y
		);
		shape1.setPosition(view_cords.left - view_cords.width / 2 + shape1.getPosition().x,
			view_cords.top - view_cords.height / 2 + shape1.getPosition().y
		);
		shape2.setPosition(view_cords.left - view_cords.width / 2 + shape2.getPosition().x,
			view_cords.top - view_cords.height / 2 + shape2.getPosition().y
		);


		for (auto i : g_elements) {
			for (auto j : i) {
				j->update();
			}
		}
	}

	void Group::render(){
		RenderWindow* target = GlobalProcessData::getWindow();

		target->draw(background);
		if (name != nullptr) {
			target->draw(*name);
		}
		View oldView{ target->getView() };
		View view{ createLocalView(this->getLocalBounds(), target) };
		target->setView(view);
		for (auto i : g_elements) {
			for (auto j : i) {
				j->render();
			}
		}
		target->setView(oldView);
		//target->draw(shape1);
		//target->draw(shape2);
		//target->draw(shape0);
	}
