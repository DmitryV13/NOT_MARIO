#pragma once
#include "Group.h"
#include "FormItem.h"
#include "FORM_ITEM_STATE.h"
#include "CheckboxItem.h"

using namespace::sf;
using std::function;

using action_type = function<void(std::vector<float>)>*;

class Form : public Group{
private:
	std::vector<float> callback_params;
	action_type action;
	bool activated;
public:
	Form(float x, float y, float width_, float height_);

	InterfaceItem* getElement(int i, int j);

	template<class T>
	void addFormAction(int params_amount, void(T::* l_func)(float), T* l_instance);

	void addCallbackParam(float index, string* param);
	void activateForm(float param1, float param2);
};

template<class T>
inline void Form::addFormAction(int params_amount, void(T::* l_func)(float), T* l_instance) {
	callback_params.resize(params_amount);
	*action = std::bind(l_func, l_instance, std::placeholders::_1);
}
