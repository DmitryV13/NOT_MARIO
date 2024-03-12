#include "stdafx.h"
#include "CallbacksHandler.h"

	CallbacksHandler::CallbacksHandler(){
	}
	
	void CallbacksHandler::update(){
		for (auto i : w_callbacks) {
			for (auto j : i.second) {
				auto g = (j.first);
				if (i.first == *(j.first)) {
					for (size_t ind = 0; ind < j.second.size(); ind++){
						j.second[ind](c_parameters[j.first]);
					}
				}
			}
		}
	}
