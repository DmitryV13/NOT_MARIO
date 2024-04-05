#pragma once
#include "InterfaceItem.h"
#include "ITEM_OVERFLOW.h"


class Textarea : public InterfaceItem{
protected:
	Text* text;
	string* text_str;
	char cursor;

	RectangleShape background;

	int text_size;
	Color text_color;

	float offset_y;
	short overflow;
	bool multiline;
	bool visibility;

	float width;
	float height;
	Vector2f position;
public:
	Textarea(float x, float y, float width_, float height_,  int text_size_, Color text_color_, 
		Color background_color_, Color border_color, short overflow_, bool multiline_);
	Textarea(float x, float y, float width_, float height_, int text_size_, bool multiline_);
	~Textarea();

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;
	std::string* getString();
	char getLastCharacter();
	bool getVisibility();

	bool hasCursor();
	bool contentOverflows();

	void setVisibility(bool visibility_);
	void setOverflow(short overflow_);
	void setBackgroungColor(Color color);
	void setOutlineColor(Color color);
	void setTextColor(Color color);
	void setString(std::string new_str);
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	void changePosition(float offset_x, float offset_y) override;

	void addCharacter(char ch);
	void addCursor(char cursor_);
	void removeCharacter(int index);
	void removeLastCharacter();
	void removeCursor();
	vector<string> splitString(const string& str, char delimiter);

	void scroll(float delta);
	void normalization();

	void update() override;
	void render() override;
};

