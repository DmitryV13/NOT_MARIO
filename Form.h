#pragma once
#include "Group.h"
#include "FormItem.h"
#include "FORM_ITEM_STATE.h"
#include "CheckboxItem.h"

using namespace::sf;
using std::function;

using saction_type = function<void(std::vector<float>)>*;
using daction_type = function<void(std::vector<string>)>*;

class Form : public Group{
private:
	std::vector<float> s_callback_params;
	std::vector<string> d_callback_params;
	saction_type s_action;
	daction_type d_action;
	bool activated;
	bool action_done;
	bool static_parameters;
public:
	Form(float x, float y, float width_, float height_);
	~Form();

	InterfaceItem* getElement(int i, int j);
	void setStaticParametersType(bool type);
	void resetFormUsage();
	template<class T>
	void addSFormAction(int params_amount, void(T::* l_func)(vector<float>), T* l_instance);

	template<class T>
	void addDFormAction(int params_amount, void(T::* l_func)(vector<string>), T* l_instance);

	void addDCallbackParam(string* index, string* param);
	void addSCallbackParam(float index, float param);
	void activateForm(float param1, float param2);

	void update() override;
};

template<class T>
inline void Form::addSFormAction(int params_amount, void(T::* l_func)(vector<float>), T* l_instance) {
	s_callback_params.resize(params_amount);
	*s_action = std::bind(l_func, l_instance, std::placeholders::_1);
}

template<class T>
inline void Form::addDFormAction(int params_amount, void(T::* l_func)(vector<string>), T* l_instance) {
	d_callback_params.resize(params_amount);
	*d_action = std::bind(l_func, l_instance, std::placeholders::_1);
}
