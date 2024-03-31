#include "stdafx.h"
#include "PopUpAutocWindow.h"

	PopUpAutocWindow::PopUpAutocWindow(double screen_width, double screen_height, int width_, int height_,
		TextureManager* t_manager_)
		:PopUpWindow(screen_width, screen_height, width_, height_, t_manager_) {
		chosen = false;
		mouse_pressed_pos.x = 0.f;
		mouse_pressed_pos.y = 0.f;

		header.setSize(Vector2f(width, 40));
		header.setPosition(position);
		header.setFillColor(Color(60, 60, 118, 255));

		close_b = new ImageButton(position.x + width - 3 - 34, position.y + 3, 34, 34, 0, "", t_manager_, 0, "CloseB", true);
		close_b->setColors(Color(0, 0, 0), Color(0, 0, 0), Color(212, 24, 22, 255), Color(212, 24, 22, 255));
		position.y += 40;
		height -= 40;

		addCallback(close_b->getButtonState(), BUTTON_STATE::BTN_ACTIVE, POP_UP_WINDOW_STATE::PUW_CLOSED, 0,
			&PopUpWindow::setPUWState, (PopUpWindow*)this);
	}

	void PopUpAutocWindow::setWindowName(string name){
		window_name = new Textarea(
			position.x,
			position.y - 40,
			width - 40,
			40,
			20,
			false);
		window_name->setTextColor(Color::White);
		window_name->setBackgroungColor(Color(0, 0, 0, 0));
		window_name->setOutlineColor(Color(0, 0, 0, 0));
		window_name->setString(name);
	}

	void PopUpAutocWindow::dragWindow(Vector2f mouse_current_pos){
		float tmp_offset_x = mouse_current_pos.x - mouse_pressed_pos.x;
		offset_x += tmp_offset_x;
		mouse_pressed_pos.x = mouse_current_pos.x;

		float tmp_offset_y = mouse_current_pos.y - mouse_pressed_pos.y;
		offset_y += tmp_offset_y;
		mouse_pressed_pos.y = mouse_current_pos.y;

		position.x += tmp_offset_x;
		position.y += tmp_offset_y;

		for (auto i : groups) {
			for (auto j : i) {
				j->changePosition(tmp_offset_x, tmp_offset_y);
			}
		}

		w_background->changePosition(tmp_offset_x, tmp_offset_y);
		close_b->changePosition(tmp_offset_x, tmp_offset_y);
	}

	void PopUpAutocWindow::update(){
		FloatRect view_cords = GlobalProcessData::getViewCords();
		Vector2f mouse_pos = GlobalProcessData::getMousePos();

		float mouse_current_pos_x = mouse_pos.x + (view_cords.left - view_cords.width / 2);
		float mouse_current_pos_y = mouse_pos.y + (view_cords.top - view_cords.height / 2);
		if (header.getGlobalBounds().contains(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
			if (Mouse::isButtonPressed(sf::Mouse::Left) && !chosen) {
				chosen = true;
				mouse_pressed_pos.x = mouse_pos.x + (view_cords.left - view_cords.width / 2);
				mouse_pressed_pos.y = mouse_pos.y + (view_cords.top - view_cords.height / 2);
			}
			else if (!Mouse::isButtonPressed(sf::Mouse::Left) && chosen) {
				chosen = false;
				mouse_pressed_pos.x = 0.f;
				mouse_pressed_pos.y = 0.f;
			}
		}
		else if (!header.getGlobalBounds().contains(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
			chosen = false;
			mouse_pressed_pos.x = 0.f;
			mouse_pressed_pos.y = 0.f;
		}

		if (chosen) {
			dragWindow(Vector2f(mouse_current_pos_x, mouse_current_pos_y));
		}

		w_background->update();
		header.setPosition(
			view_cords.left - view_cords.width / 2 + position.x,
			view_cords.top - view_cords.height / 2 + position.y - 40
		);
		if (window_name) {
			window_name->update();
		}
		close_b->update();

		if (label != nullptr)
			label->update();

		for (auto i = groups.begin(); i != groups.end(); ++i) {
			for (auto j = i->begin(); j != i->end(); ++j) {
				(*j)->update();
			}
		}

		callbacks_handler->update();
		dcallbacks_handler->update();
	}

	void PopUpAutocWindow::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		if (background)
			target->draw(*background);

		w_background->render();

		target->draw(header);
		if (window_name) {
			window_name->render();
		}
		close_b->render();

		if (label != nullptr)
			label->render();

		for (auto i : groups) {
			for (auto j : i) {
				j->render();
			}
		}
	}
