#include "stdafx.h"
#include "PopUpAutocWindow.h"

	PopUpAutocWindow::PopUpAutocWindow(double screen_width, double screen_height, int width_, int height_,
		TextureManager* t_manager_)
		:PopUpWindow(screen_width, screen_height, width_, height_, t_manager_) {
		header.setSize(Vector2f(width, 40));
		header.setPosition(position);
		header.setFillColor(Color(60, 60, 118, 255));

		close_b = new ImageButton(position.x + width - 3 - 34, position.y + 3, 34, 34, 0, "", t_manager_, 0, "CloseB", true, 1);
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

	void PopUpAutocWindow::update(){
		FloatRect view_cords = GlobalProcessData::getViewCords();

		w_background->update();

		header.setPosition(
			view_cords.left - view_cords.width / 2 + position.x,
			view_cords.top - view_cords.height / 2 + position.y - 40
		);
		window_name->update();
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
