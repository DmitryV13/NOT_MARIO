#include "stdafx.h"
#include "MainMenuOption.h"

void MainMenuOption::enter(RenderWindow* window){
}

void MainMenuOption::close(float param1, float param2){
	state = PAGE_STATE::PAGE_CLOSED;
}
