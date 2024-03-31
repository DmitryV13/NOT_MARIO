#pragma once
#include "InterfaceItem.h"
#include "INTERFACE_ITEM_TYPE.h"
#include "BUTTON_STATE.h"
#include "TextureManager.h"


class Button : public InterfaceItem{
protected:
	short button_prstate;
	short button_cstate;
	RectangleShape shape;

	Text text;

	Vector2f position;
	Color btn_idle_color;
	Color btn_hover_color;
	Color btn_active_color;

	Color shp_idle_color;
	Color shp_hover_color;
	Color shp_active_color;

public:
	Button();
	Button(float x, float y, short text_size, string text_, Color menuColor);
	Button(float x, float y, float width, float height, short text_size, string text_
		, Color btn_hcolor);
	Button(float x, float y, float width, float height, short text_size, string text_
		, bool outline);
	~Button();

	float getHeight();
	float getWidth();
	float getTextHeight();
	float getTextWidth();
	short* getButtonState();
	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	virtual void setPosition(Vector2f new_position);
	void setPositionX(float x) override;
	void setPositionY(float y) override;

	void changePosition(float offset_x, float offset_y) override;

	void setColors(Color btn_hcolor, Color btn_icolor, Color shp_hcolor, Color shp_icolor);
	void setBackgroundColor(Color shapeColor);
	void resetActiveState() override;
	
	const bool isPressed() const;

	virtual void updatePosition();
	void update() override;
	void render() override;
};

