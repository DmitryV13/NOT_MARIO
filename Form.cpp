#include "stdafx.h"
#include "Form.h"

	Form::Form(float x, float y, float width_, float height_)
	:Group(x, y, width_, height_){
		ii_type = INTERFACE_ITEM_TYPE::FORM;
		s_action = nullptr;
		activated = false; 
		action_done = false;
		static_parameters = true;
	}

	Form::~Form(){
	}
	
	void Form::addDCallbackParam(string* index_, string* param){
		int index = stoi(*index_);
		d_callback_params[static_cast<int>(index)] = *param;
	}

	void Form::addSCallbackParam(float index, float param){
		s_callback_params[static_cast<int>(index)] = param;
	}

	void Form::activateForm(float param1, float param2){
		if (!activated && !action_done) {
			for (auto i : g_elements) {
				for (auto j : i) {
					if (j->getIIType() == INTERFACE_ITEM_TYPE::FORM_ITEM) {
						//if (((CheckboxItem*)j)->getFIState() == FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1) {
						dynamic_cast<FormItem*>(j)->setFIState(FORM_ITEM_STATE::FORM_ITEM_ACTIVE_2);
						//}
					}
				}
			}
			activated = true;
		}
	}

	void Form::update(){
		Group::update();
		if(activated && !action_done){
			if (static_parameters) {
				if (s_action != nullptr) {
					(*s_action)(s_callback_params);
				}
			}
			else {
				if (d_action != nullptr) {
					(*d_action)(d_callback_params);
				}
			}
			action_done = true;
			activated = false;
		}
	}

	InterfaceItem* Form::getElement(int i, int j){
		return g_elements[i][j];
	}

	void Form::setStaticParametersType(bool type){
		static_parameters = type;
		if (static_parameters) {
			s_action = new function<void(std::vector<float>)>();
		}
		else {
			d_action = new function<void(std::vector<string>)>();
		}
	}

	void Form::resetFormUsage(){
		action_done = false;
		activated = false;
	}
