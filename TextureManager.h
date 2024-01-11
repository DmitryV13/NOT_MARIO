#pragma once

using namespace::sf;

class TextureManager {
private:
	vector<unordered_map<string, Texture>> textures;
public:
	TextureManager();
	Texture& getTexture(int number, string name);
};

