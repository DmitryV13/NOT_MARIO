#include "stdafx.h"
#include "Form.h"

	Form::Form(float x, float y, float width_, float height_)
	:Group(x, y, width_, height_){
		ii_type = INTERFACE_ITEM_TYPE::FORM;
		action = nullptr;
		activated = false; 
	}
	
	void Form::addCallbackParam(float index, string* param){
		callback_params[static_cast<int>(index)] = stof(*param);
	}

	void Form::activateForm(float param1, float param2){
		if (!activated) {
			for (auto i : g_elements) {
				for (auto j : i) {
					if (j->getIIType() == INTERFACE_ITEM_TYPE::FORM_ITEM) {
						if (((CheckboxItem*)j)->getFIState() == FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1) {
							((CheckboxItem*)j)->setFIState(FORM_ITEM_STATE::FORM_ITEM_ACTIVE_2);
						}
					}
				}
			}
			activated = true;
		}
		else {
			if (action != nullptr)
				(*action)(callback_params);
			else
				std::cout << "null";
		}
	}

	InterfaceItem* Form::getElement(int i, int j){
		return g_elements[i][j];
	}
