#include "stdafx.h"
#include "Notification.h"

	Notification::Notification(float x, float y, float dest_x, float dest_y, short text_size, string text_, Color text_color)
		:position(Vector2f(x, y)), active(false){
		text.setFont(*GlobalProcessData::getFont());
		text.setString(text_);
		text.setFillColor(text_color);
		text.setCharacterSize(text_size);
		text.setOutlineThickness(3.f);
		text.setOutlineColor(sf::Color(0, 0, 0, 0));
		text.setPosition(position);

		Vector2f s = Vector2f(dest_x, dest_y) - text.getPosition();
		norm_s = s / static_cast<float>(sqrt(pow(s.x, 2) + pow(s.y, 2)));

		display_time.restart();
	}

	Notification::Notification(FloatRect object_cords, short text_size, string text_, Color text_color)
		:active(false){
		position.x = object_cords.left + object_cords.width / 2;
		position.y = object_cords.top + object_cords.height / 2;
		text.setFont(*GlobalProcessData::getFont());
		text.setString(text_);
		text.setFillColor(text_color);
		text.setCharacterSize(text_size);
		text.setOutlineThickness(3.f);
		text.setOutlineColor(sf::Color(0, 0, 0, 0));
		text.setPosition(position);

		Vector2f s = Vector2f(position.x, position.y-30) - text.getPosition();
		norm_s = s / static_cast<float>(sqrt(pow(s.x, 2) + pow(s.y, 2)));

		display_time.restart();
	}

	void Notification::activation(float q){
		active = true;
		text.setPosition(position);
		display_time.restart();
	}
	
	void Notification::update(){
		updateDT();
		if (active) {
			text.setPosition(text.getPosition()+(norm_s * 2.f));
		}
		else {
			text.setPosition(position);
		}
	}

	void Notification::updateDT(){
		if (display_time.getElapsedTime().asSeconds() > 0.3) {
			active = false;
			display_time.restart();
		}
	}
	
	void Notification::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		if (active) {
			target->draw(text);
		}
	}
	