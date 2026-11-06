#include "stdafx.h"
#include "ui/CallbacksHandler.h"

	CallbacksHandler::CallbacksHandler(){
	}
	
	void CallbacksHandler::update(){
		for (auto i : w_callbacks) {
			for (auto j : i.second) {
				auto g = (j.first);
				if (i.first == *(j.first)) {
					j.second(c_parameters[j.first]);
				}
			}
		}
	}
