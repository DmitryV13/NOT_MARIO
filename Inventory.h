#pragma once

using namespace::sf;

class Inventory{
private:
	unordered_map<string, pair<int*, int>> items;
public:
	Inventory();
	pair<int*, int>& getItemInfo(string name);
};

