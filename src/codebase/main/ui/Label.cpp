#include "stdafx.h"
#include "ui/Label.h"

	Label::Label(const string& label_text_, Font* font_, int text_size_, TextureManager* manager, int index)
		:text_size(text_size_){
		label_text = new Text(*font_);
		label_text->setString(label_text_);
		label_text->setFillColor(sf::Color::White);
		label_text->setCharacterSize(text_size);
		label_text->setOutlineThickness(3.f);
		label_text->setOutlineColor(sf::Color(0, 0, 0, 0));
		label_background = new ComposedIMG(label_text->getLocalBounds().size.x + label_text->getLocalBounds().size.x / 2, label_text->getLocalBounds().size.y + label_text->getLocalBounds().size.y / 4, 6, manager, 1);

	}

	void Label::setPosition(int x, int y){
		label_background->setPosition(x, y);
		label_text->setPosition(Vector2(label_background->getLocalBounds().position.x, label_background->getLocalBounds().position.y));
	}

	void Label::setPosition(string positionX, string positionY, int screen_width, int screen_height){
		label_background->setPosition(positionX, positionY, screen_width, screen_height);
		label_text->setPosition(Vector2(label_background->getLocalBounds().position.x, label_background->getLocalBounds().position.y));
	}

	void Label::setPosition(string positionX, int y, int screen_width, int screen_height){
		label_background->setPosition(positionX, y, screen_width, screen_height);
		label_text->setPosition(Vector2(label_background->getLocalBounds().position.x, label_background->getLocalBounds().position.y));
	}

	void Label::setPosition(int x, string positionY, int screen_width, int screen_height){
		label_background->setPosition(x, positionY, screen_width, screen_height);
		label_text->setPosition(Vector2(label_background->getLocalBounds().position.x, label_background->getLocalBounds().position.y));
	}

	FloatRect Label::getLocalBounds(){
		return label_background->getLocalBounds();
	}

	FloatRect Label::getGlobalBounds(){
		return label_background->getGlobalBounds();
	}

	void Label::update(FloatRect view_cords){
		label_background->update(view_cords);
		label_text->setPosition(Vector2(label_background->getLocalBounds().position.x - label_text->getLocalBounds().position.x + label_text->getLocalBounds().size.x / 4, label_background->getLocalBounds().position.y - label_text->getLocalBounds().position.y + label_text->getLocalBounds().size.y / 8));
	}

	void Label::render(RenderTarget* target){
		label_background->render(target);
		target->draw(*label_text);
	}
	
