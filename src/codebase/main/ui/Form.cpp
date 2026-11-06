#include "stdafx.h"
#include "Form.h"

	Form::Form(float x, float y, float width_, float height_)
	:Group(x, y, width_, height_){
		ii_type = INTERFACE_ITEM_TYPE::FORM;
	}
	
	void Form::activateForm(float q){
		for (auto i : g_elements) {
			for (auto j : i) {
				if (j->getIIType() == INTERFACE_ITEM_TYPE::FORM_ITEM) {
					if (((CheckboxItem*)j)->getFIState() == FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1) {
						((CheckboxItem*)j)->setFIState(FORM_ITEM_STATE::FORM_ITEM_ACTIVE_2);
					}
				}
			}
		}
	}

	InterfaceItem* Form::getElement(int i, int j){
		return g_elements[i][j];
	}
