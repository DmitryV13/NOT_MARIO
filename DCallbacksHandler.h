#pragma once

using namespace::sf;

using DCallbackFunctions = vector <std::function<void(float, string*)>>;

using DCallbackContainer = unordered_map<
	short*, DCallbackFunctions>;

using DCallbacks = unordered_map<
	short, DCallbackContainer>;

using DParameters = unordered_map<
	short*, std::pair<float, string*>>;

class DCallbacksHandler {
private:
	DCallbacks w_callbacks;
	DParameters c_parameters;
public:
	DCallbacksHandler();

	template<class T>
	bool addCallback(short* b_state, short a_state, float param1, string* param2, void(T::* l_func)(float, string*), T* l_instance);
	void update();
};

template<class T>
inline bool DCallbacksHandler::addCallback(short* c_state, short a_state, float param1, string* param2, void(T::* l_func)(float, string*), T* l_instance) {
	c_parameters.insert({ c_state, {param1, param2} });
	auto itr = w_callbacks.emplace(a_state, DCallbackContainer()).first;
	auto temp = std::bind(l_func, l_instance, std::placeholders::_1, std::placeholders::_2);
	bool inserted = itr->second.emplace(c_state, DCallbackFunctions()).second;
	itr->second.at(c_state).push_back(temp);
	return inserted;
}

