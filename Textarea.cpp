#include "stdafx.h"
#include "Textarea.h"

	Textarea::Textarea(float x, float y, float width_, float height_, Font* font_, int text_size_, 
		Color text_color_, Color background_color_, Color border_color_, short overflow_, bool multiline_)
		: position(Vector2f(x, y)), width(width_), height(height_), overflow(overflow_), multiline(multiline_)
		, text_size(text_size_){
		ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;

		shape.setSize(Vector2f(
			width - 4,
			height - 4)
		);
		shape.setPosition(
			position.x + 2,
			position.y + 2
		);
		shape.setFillColor(background_color_);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(border_color_);

		text = new Text();
		text->setFont(*font_);
		text->setString("a");
		text->setCharacterSize(text_size);
		text->setFillColor(text_color);
		text->setPosition(
			shape.getPosition().x + 8 + 2 - text->getLocalBounds().left,//left offset
			shape.getPosition().y + (multiline ? (8 + 2) : ((shape.getGlobalBounds().height - text->getGlobalBounds().height) / 2.f)) - text->getLocalBounds().top
		);
		text->setString("");
		text_str = new string();
		cursor = ' ';
	}
	
	Textarea::Textarea(float x, float y, float width_, float height_, Font* font_, int text_size_, 
		bool multiline_)
		: position(Vector2f(x, y)), width(width_), height(height_), overflow(ITEM_OVERFLOW::HIDDEN), 
		multiline(multiline_), text_size(text_size_) {
		ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;

		shape.setSize(Vector2f(
			width - 4,
			height - 4)
		);
		shape.setPosition(
			position.x + 2,
			position.y + 2
		);
		shape.setFillColor(Color::White);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(Color(60, 60, 118, 255));

		text = new Text();
		text->setFont(*font_);
		text->setString("a");
		text->setCharacterSize(text_size);
		text->setFillColor(text_color);
		text->setPosition(
			shape.getPosition().x + 8 + 2 - text->getLocalBounds().left,
			shape.getPosition().y + (multiline ? (8 + 2) : ((shape.getGlobalBounds().height - text->getGlobalBounds().height) / 2.f)) - text->getLocalBounds().top
		);
		text->setString("");
		text_str = new string();
		cursor = ' ';
	}
	
	FloatRect Textarea::getLocalBounds(){
		return FloatRect(shape.getPosition(), shape.getSize());
	}
	
	FloatRect Textarea::getGlobalBounds(){
		return shape.getGlobalBounds();
	}
	
	std::string* Textarea::getString(){
		return text_str;
	}

	char Textarea::getLastCharacter(){
		return text_str->empty() ? ' ' : text_str->at(text_str->size()-1);
	}

	bool Textarea::hasCursor(){
		return cursor == ' ' ? false : true;
	}
	
	void Textarea::setOverflow(short overflow_){
		overflow = overflow_;
	}

	void Textarea::setOutlineColor(Color color){
		shape.setOutlineColor(color);
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
	}

	void Textarea::removeCursor(){
		cursor = ' ';
		normalization();
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

		shape.setPosition(
			position.x + 2,
			position.y + 2
		);

		string tmp = text->getString();
		text->setString("a");
		text->setPosition(
			shape.getPosition().x + 8 + 2 - text->getLocalBounds().left,//left offset
			shape.getPosition().y + (multiline ? (8 + 2) : ((shape.getGlobalBounds().height - text->getGlobalBounds().height) / 2.f)) - text->getLocalBounds().top
		);
		text->setString(tmp);
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
					if ((text->getGlobalBounds().width + 2 + 8) > shape.getSize().x) {
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
					if ((text->getGlobalBounds().width + 2 + 8) > shape.getSize().x) {
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

		text->setString(output);
	}
	
	void Textarea::update(Vector2f mouse_pos, FloatRect view_cords){
		shape.setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 2,
			view_cords.top - view_cords.height / 2 + position.y + 2
		);

		string tmp = text->getString();
		text->setString("a");
		text->setPosition(
			view_cords.left - view_cords.width / 2 + shape.getPosition().x + 8 + 2 - text->getLocalBounds().left,
			view_cords.top - view_cords.height / 2 + shape.getPosition().y + (multiline ? (8 + 2) : ((shape.getGlobalBounds().height - text->getGlobalBounds().height) / 2.f)) - text->getLocalBounds().top
		);
		text->setString(tmp);
	}
	
	void Textarea::render(sf::RenderTarget* target){
		target->draw(shape);
		View oldView{ target->getView() };
		View view{ createLocalView(this->getLocalBounds(), target)};
		target->setView(view);
		target->draw(*text);
		target->setView(oldView);
	}
