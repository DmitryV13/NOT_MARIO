#include "stdafx.h"
#include "Reviewer.h"

	Reviewer::Reviewer(float x, float y, float width_, float height_)
		: max_height(height_), max_width(width_), position(Vector2f(x, y)){
		ii_type = INTERFACE_ITEM_TYPE::REVIEWER;
		id = GlobalProcessData::getUnicId();
	}

	Reviewer::~Reviewer(){
		for (auto i : images) {
			delete i;
		}
	}

	FloatRect Reviewer::getLocalBounds(){
		return FloatRect(position, Vector2f(max_width, max_height));
	}

	FloatRect Reviewer::getGlobalBounds(){
		return FloatRect(position, Vector2f(max_width, max_height));
	}
	
	void Reviewer::addAnimatedImage(TextureManager* t_manager, int index, string name, IntRect first_frame, short frames_number_){
		if (images.empty()) {
			current_image = 0;
		}
		images.push_back(new AnimatedImage(t_manager, index, name, first_frame, frames_number_));
		float scale = (max_width / images[images.size() - 1]->getLocalBounds().width) <
			(max_height / images[images.size() - 1]->getLocalBounds().height) ?
			(max_width / images[images.size() - 1]->getLocalBounds().width) :
			(max_height / images[images.size() - 1]->getLocalBounds().height);

		images[images.size() - 1]->setScale(scale);
		images[images.size() - 1]->setPosition(
			position.x + (max_width - images[images.size() - 1]->getGlobalBounds().width) / 2,
			position.y + (max_height - images[images.size() - 1]->getGlobalBounds().height) / 2
		);
	}

	void Reviewer::addAnimatedImage(TextureManager* t_manager, Warehouse* w_object, string name){
		if (images.empty()) {
			current_image = 0;
		}
		images.push_back(new AnimatedImage(t_manager, w_object, name));
		short scale = (max_width / images[images.size() - 1]->getLocalBounds().width) <
			(max_height / images[images.size() - 1]->getLocalBounds().height) ?
			(max_width / images[images.size() - 1]->getLocalBounds().width) :
			(max_height / images[images.size() - 1]->getLocalBounds().height);
		images[images.size() - 1]->setScale(scale);
		images[images.size() - 1]->setPosition(
			position.x + (max_width - images[images.size() - 1]->getGlobalBounds().width) / 2,
			position.y + (max_height - images[images.size() - 1]->getGlobalBounds().height) / 2
		);
	}

	void Reviewer::addStaticImage(TextureManager* t_manager, int index, string name, IntRect first_frame){
		if (images.empty()) {
			current_image = 0;
		}
		images.push_back(new BasicImage(t_manager, index, name, first_frame));
		short scale = (max_width / images[images.size() - 1]->getLocalBounds().width) <
			(max_height / images[images.size() - 1]->getLocalBounds().height) ?
			(max_width / images[images.size() - 1]->getLocalBounds().width) :
			(max_height / images[images.size() - 1]->getLocalBounds().height);
		images[images.size() - 1]->setScale(scale);
		images[images.size() - 1]->setPosition(
			position.x + (max_width - images[images.size() - 1]->getGlobalBounds().width) / 2,
			position.y + (max_height - images[images.size() - 1]->getGlobalBounds().height) / 2
		);
	}

	void Reviewer::addStaticImage(TextureManager* t_manager, Warehouse* w_object, string name){
		if (images.empty()) {
			current_image = 0;
		}
		images.push_back(new BasicImage(t_manager, w_object, name));
		short scale = (max_width / images[images.size() - 1]->getLocalBounds().width) <
			(max_height / images[images.size() - 1]->getLocalBounds().height) ?
			(max_width / images[images.size() - 1]->getLocalBounds().width) :
			(max_height / images[images.size() - 1]->getLocalBounds().height);
		images[images.size() - 1]->setScale(scale);
		images[images.size() - 1]->setPosition(
			position.x + (max_width - images[images.size() - 1]->getGlobalBounds().width) / 2,
			position.y + (max_height - images[images.size() - 1]->getGlobalBounds().height) / 2
		);
	}

	void Reviewer::setPosition(Vector2f position_){
		position = position_;
		for (auto i : images) {
			float x = position.x + (max_width - i->getGlobalBounds().width) / 2;
			float y = position.y + (max_height - i->getGlobalBounds().height) / 2;
			i->setPosition(
				position.x + (max_width - i->getGlobalBounds().width) / 2,
				position.y + (max_height - i->getGlobalBounds().height) / 2
			);
		}
	}

	void Reviewer::setPositionX(float x){
		setPosition(Vector2f(x, position.y));
	}

	void Reviewer::setPositionY(float y){
		setPosition(Vector2f(position.x, y));
	}

	void Reviewer::changePosition(float offset_x, float offset_y){
		setPosition(Vector2f(position.x + offset_x, position.y + offset_y));
	}

	void Reviewer::changeCurrentImage(float next, float param2){
		if (current_image + static_cast<int>(next) < images.size() 
			&& current_image + static_cast<int>(next)>=0) {	
		current_image += static_cast<int>(next);
		}
	}

	void Reviewer::update(){
		FloatRect view_cords = GlobalProcessData::getViewCords();

		setPosition(Vector2f(
			position.x + view_cords.left - view_cords.width / 2,
			position.y + view_cords.top - view_cords.height / 2)
		);
		if (!images.empty()) {
			images[current_image]->update();
		}
	}

	void Reviewer::render(){
		if (!images.empty()) {
			images[current_image]->render();
		}
	}
	