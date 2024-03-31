#include "stdafx.h"
#include "PopUpAutocWindow.h"

	PopUpAutocWindow::PopUpAutocWindow(double screen_width, double screen_height, int width_, int height_,
		RenderWindow* window_, TextureManager* t_manager_)
		:PopUpWindow(screen_width, screen_height, width_, height_, window_, t_manager_) {
		header.setSize(Vector2f(width, 40));
		header.setPosition(position);
		header.setFillColor(Color(60, 60, 118, 255));

		close_b = new ImageButton(position.x + width - 3 - 34, position.y + 3, 34, 34, 0, new Font(), "", t_manager_, 0, "CloseB", true, 1);
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
			GlobalProcessData::getFont(),
			20,
			false);
		window_name->setTextColor(Color::White);
		window_name->setBackgroungColor(Color(0, 0, 0, 0));
		window_name->setOutlineColor(Color(0, 0, 0, 0));
		window_name->setString(name);
	}

	void PopUpAutocWindow::update(FloatRect view_cords){
		w_background->update(view_cords);

		header.setPosition(
			view_cords.left - view_cords.width / 2 + position.x,
			view_cords.top - view_cords.height / 2 + position.y - 40
		);
		window_name->update(Vector2f(Mouse::getPosition(*window)), view_cords);
		close_b->update(Vector2f(Mouse::getPosition(*window)), view_cords);

		if (label != nullptr)
			label->update(view_cords);

		for (auto i = groups.begin(); i != groups.end(); ++i) {
			for (auto j = i->begin(); j != i->end(); ++j) {
				(*j)->update(Vector2f(Mouse::getPosition(*window)), view_cords);
			}
		}

		callbacks_handler->update();
		dcallbacks_handler->update();
	}

	void PopUpAutocWindow::render(){
		if (background)
			window->draw(*background);

		w_background->render(window);

		window->draw(header);
		if (window_name) {
			window_name->render(window);
		}
		close_b->render(window);

		if (label != nullptr)
			label->render(window);

		for (auto i : groups) {
			for (auto j : i) {
				j->render(window);
			}
		}
	}
