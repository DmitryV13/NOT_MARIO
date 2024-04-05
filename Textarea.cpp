#include "stdafx.h"
#include "Textarea.h"

	Textarea::Textarea(float x, float y, float width_, float height_, int text_size_, 
		Color text_color_, Color background_color_, Color border_color_, short overflow_, bool multiline_)
		: position(Vector2f(x, y)), width(width_), height(height_), overflow(overflow_), multiline(multiline_)
		, text_size(text_size_){
		ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;
		id = GlobalProcessData::getUnicId();

		visibility = true;
		offset_y = 0;

		background.setSize(Vector2f(
			width - 4,
			height - 4)
		);
		background.setPosition(
			position.x + 2,
			position.y + 2
		);
		background.setFillColor(background_color_);
		background.setOutlineThickness(2);
		background.setOutlineColor(border_color_);

		text = new Text();
		text->setFont(*GlobalProcessData::getFont());
		text->setString("a");
		text->setCharacterSize(text_size);
		text->setFillColor(text_color);
		text->setPosition(
			background.getPosition().x + 8 + 2 - text->getLocalBounds().left,//left offset
			background.getPosition().y + (multiline ? (8 + 2) : ((background.getGlobalBounds().height - text->getGlobalBounds().height) / 2.f)) - text->getLocalBounds().top
		);
		text->setString("");
		text_str = new string();
		cursor = ' ';
	}
	
	Textarea::Textarea(float x, float y, float width_, float height_, int text_size_, 
		bool multiline_)
		: position(Vector2f(x, y)), width(width_), height(height_), overflow(ITEM_OVERFLOW::HIDDEN), 
		multiline(multiline_), text_size(text_size_) {
		ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;
		id = GlobalProcessData::getUnicId();

		visibility = true;
		offset_y = 0;

		background.setSize(Vector2f(
			width - 4,
			height - 4)
		);
		background.setPosition(
			position.x + 2,
			position.y + 2
		);
		background.setFillColor(Color::White);
		background.setOutlineThickness(2);
		background.setOutlineColor(Color(60, 60, 118, 255));

		text = new Text();
		text->setFont(*GlobalProcessData::getFont());
		text->setString("a");
		text->setCharacterSize(text_size);
		text->setFillColor(text_color);
		text->setPosition(
			background.getPosition().x + 8 + 2 - text->getLocalBounds().left,
			background.getPosition().y + (multiline ? (8 + 2) : ((background.getGlobalBounds().height - text->getGlobalBounds().height) / 2.f)) - text->getLocalBounds().top
		);
		text->setString("");
		text_str = new string();
		cursor = ' ';
	}

	Textarea::~Textarea(){
		delete text;
		delete text_str;
	}
	
	FloatRect Textarea::getLocalBounds(){
		return FloatRect(background.getPosition(), background.getSize());
	}
	
	FloatRect Textarea::getGlobalBounds(){
		return background.getGlobalBounds();
	}
	
	std::string* Textarea::getString(){
		return text_str;
	}

	char Textarea::getLastCharacter(){
		return text_str->empty() ? ' ' : text_str->at(text_str->size()-1);
	}

	bool Textarea::getVisibility(){
		return visibility;
	}

	bool Textarea::hasCursor(){
		return cursor == ' ' ? false : true;
	}

	bool Textarea::contentOverflows(){	
		return text->getGlobalBounds().height >= background.getSize().y ? true : false;
	}
	
	void Textarea::setVisibility(bool visibility_){
		visibility = visibility_;
	}

	void Textarea::setOverflow(short overflow_){
		overflow = overflow_;
	}

	void Textarea::setBackgroungColor(Color color){
		background.setFillColor(color);
	}

	void Textarea::setOutlineColor(Color color){
		background.setOutlineColor(color);
	}

	void Textarea::setTextColor(Color color){
		text->setFillColor(color);
	}

	void Textarea::setString(std::string new_str){
		*text_str = new_str;
		normalization();
	}
	
	void Textarea::addCharacter(char ch){
		if (!hasCursor()) {
			*text_str += ch;
		}
		else {
			text_str->insert(text_str->size() - 2, 1, ch);
		}
		normalization();
	}

	void Textarea::addCursor(char cursor_){
		cursor = cursor_;
		normalization();
	}
	
	void Textarea::removeCharacter(int index){
		if (text_str->empty())
			return;
		text_str->erase(index, index + 1);
		normalization();
		if (!contentOverflows())
			offset_y = 0;
	}
	
	void Textarea::removeLastCharacter(){
		if (text_str->empty())
			return;
		if (!hasCursor()) {
			text_str->pop_back();
		}
		else {
			text_str->erase(text_str->size() - 1, 1);
		}
		normalization();
		if (!contentOverflows())
			offset_y = 0;
	}

	void Textarea::removeCursor(){
		cursor = ' ';
		normalization();
		if (!contentOverflows())
			offset_y = 0;
	}

	vector<string> Textarea::splitString(const string& str, char delimiter){
		vector<string> tokens;
		string token;
		std::istringstream tokenStream(str);
		while (getline(tokenStream, token, delimiter)) {
			tokens.push_back(token);
		}
		return tokens;
	}
	
	void Textarea::setPositionX(float x){
		float offset = x - position.x;
		changePosition(offset, 0);
	}
	
	void Textarea::setPositionY(float y){
		float offset = y - position.y;
		changePosition(0, offset);
	}
	
	void Textarea::changePosition(float offset_x, float offset_y){
		position.x += offset_x;
		position.y += offset_y;

		background.setPosition(
			position.x + 2,
			position.y + 2
		);

		string tmp = text->getString();
		text->setString("a");
		text->setPosition(
			background.getPosition().x + 8 + 2 - text->getLocalBounds().left,//left offset
			background.getPosition().y + (multiline ? (8 + 2) : ((background.getGlobalBounds().height - text->getGlobalBounds().height) / 2.f)) - text->getLocalBounds().top
		);
		text->setString(tmp);
	}
	
	void Textarea::scroll(float delta){
		float offset = delta * 16;
		if (delta > 0) {

			if (background.getPosition().y <= text->getPosition().y - text->getLocalBounds().top + offset) {
				offset_y = 0;
			}
			else {
				offset_y += delta * 16;
			}
		}
		else {
			if (background.getPosition().y + background.getGlobalBounds().height 
				>= text->getPosition().y - text->getLocalBounds().top + text->getGlobalBounds().height + offset) {
				offset_y = background.getSize().y - text->getGlobalBounds().height - 10;
			}
			else {
				offset_y += delta * 16;
			}
		}
	}

	void Textarea::normalization(){
		string output;
		if (multiline) {
			if (overflow == ITEM_OVERFLOW::HORIZONTAL) {

			}else if (overflow == ITEM_OVERFLOW::VERTICAL) {
				vector<string> words = splitString(*text_str + cursor, ' ');
				string current_line = *words.begin() + (words.size() == 1 ? "" : " ");
				for (auto word = words.begin()+1; word != words.end(); word++) {
					text->setString(current_line + *word);
					if ((text->getGlobalBounds().width + 2 + 8) > background.getSize().x) {
						output += current_line + '\n';
						current_line.clear();
						current_line += *word + ' ';
					}
					else {
						if (word + 1 == words.end()) {
							current_line += *word;
						}
						else {
							current_line += *word + ' ';
						}
					}
				}
				output += current_line;
			}
			else if (overflow == ITEM_OVERFLOW::HIDDEN) {
				vector<string> words = splitString(*text_str, ' ');
				string current_line;
				for (const auto& word : words) {
					text->setString(current_line + word);
					if ((text->getGlobalBounds().width + 2 + 8) > background.getSize().x) {
						output += current_line + '\n';
						current_line.clear();
						if (word.length() > 0) {
							if (word[word.length() - 1] != '_') {
								current_line += word + ' ';
							}
							else {
								current_line += word;
							}
						}
					}
					else if (word.length() > 0) {
						if (word[word.length() - 1] != '_') {
							current_line += word + ' ';
						}
						else {
							current_line += word;
						}
					}
				}
				output += current_line;
			}
		}
		else {
			if (overflow == ITEM_OVERFLOW::HORIZONTAL) {

			}
			else if (overflow == ITEM_OVERFLOW::HIDDEN) {
				output = *text_str;
				if (hasCursor()) {
					output += cursor;
				}
			}
		}
		if (!visibility) {
			std::transform(output.begin(), output.end(), output.begin(), [](char c) {
				return (c != ' ') ? '*' : c;
				});
			if (hasCursor()) {
				output.pop_back();
			}
		}
		text->setString(output);
	}
	
	void Textarea::update(){
		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();

		background.setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 2,
			view_cords.top - view_cords.height / 2 + position.y + 2
		);

		string tmp = text->getString();
		text->setString("a");
		text->setPosition(
			view_cords.left - view_cords.width / 2 + background.getPosition().x + 8 + 2 - text->getLocalBounds().left,
			view_cords.top - view_cords.height / 2 + background.getPosition().y + 
			(multiline ? (8 + 2) : ((background.getGlobalBounds().height - text->getGlobalBounds().height) / 2.f)) - 
			text->getLocalBounds().top + offset_y
		);
		text->setString(tmp);
	}
	
	void Textarea::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		target->draw(background);
		View oldView{ target->getView() };
		View view{ createLocalView(this->getLocalBounds(), target)};
		target->setView(view);
		target->draw(*text);
		target->setView(oldView);
	}
