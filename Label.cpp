#include "stdafx.h"
#include "Label.h"

	Label::Label(const string& label_text_,  int text_size_, TextureManager* manager, int index)
		:text_size(text_size_){
		label_text = new Text();
		label_text->setFont(*GlobalProcessData::getFont());
		label_text->setString(label_text_);
		label_text->setFillColor(sf::Color::White);
		label_text->setCharacterSize(text_size);
		label_text->setOutlineThickness(3.f);
		label_text->setOutlineColor(sf::Color(0, 0, 0, 0));
		label_background = new ComposedIMG(label_text->getLocalBounds().width + label_text->getLocalBounds().width / 2, label_text->getLocalBounds().height + label_text->getLocalBounds().height / 4, 6, manager, 1);

	}

	void Label::setPosition(int x, int y){
		label_background->setPosition(x, y);
		label_text->setPosition(label_background->getLocalBounds().left, label_background->getLocalBounds().top);
	}

	void Label::setPosition(string positionX, string positionY, int screen_width, int screen_height){
		label_background->setPosition(positionX, positionY, screen_width, screen_height);
		label_text->setPosition(label_background->getLocalBounds().left, label_background->getLocalBounds().top);
	}

	void Label::setPosition(string positionX, int y, int screen_width, int screen_height){
		label_background->setPosition(positionX, y, screen_width, screen_height);
		label_text->setPosition(label_background->getLocalBounds().left, label_background->getLocalBounds().top);
	}

	void Label::setPosition(int x, string positionY, int screen_width, int screen_height){
		label_background->setPosition(x, positionY, screen_width, screen_height);
		label_text->setPosition(label_background->getLocalBounds().left, label_background->getLocalBounds().top);
	}

	FloatRect Label::getLocalBounds(){
		return label_background->getLocalBounds();
	}

	FloatRect Label::getGlobalBounds(){
		return label_background->getGlobalBounds();
	}

	void Label::update(){
		label_background->update();
		label_text->setPosition(label_background->getLocalBounds().left - label_text->getLocalBounds().left + label_text->getLocalBounds().width / 4, label_background->getLocalBounds().top - label_text->getLocalBounds().top + label_text->getLocalBounds().height / 8);
	}

	void Label::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		label_background->render();
		target->draw(*label_text);
	}
	
