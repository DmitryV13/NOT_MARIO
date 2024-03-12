#pragma once

using namespace::sf;

using CallbackFunctions = vector <std::function<void(float)>>;

using CallbackContainer = unordered_map<
	short*, CallbackFunctions>;

using Callbacks = unordered_map<
	short, CallbackContainer>;

using Parameters = unordered_map<
	short*, float>;

class CallbacksHandler{
private:
	Callbacks w_callbacks;
	Parameters c_parameters;
public:
	CallbacksHandler();

	template<class T>
	bool addCallback(short* b_state, short a_state, float param, void(T::* l_func)(float), T* l_instance);
	void update();
};

template<class T>
inline bool CallbacksHandler::addCallback(short* c_state, short a_state, float param, void(T::* l_func)(float), T* l_instance) {
	c_parameters.insert({ c_state, param });
	auto itr = w_callbacks.emplace(a_state, CallbackContainer()).first;
	auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
	bool inserted = itr->second.emplace(c_state, CallbackFunctions()).second;
	itr->second.at(c_state).push_back(temp);
	return inserted;
}
