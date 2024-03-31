#pragma once

using namespace sf;

class InterfaceItem{
protected:
	short ii_type;
	bool is_scrollable = false;
	bool overflow_x = false;
	bool overflow_y = false;
	int id;
public:
	virtual FloatRect getLocalBounds();
	virtual FloatRect getGlobalBounds();
	short& getIIType();
	const int& getId() const;

	virtual void setPositionX(float x);
	virtual void setPositionY(float y);

	View createLocalView(FloatRect rect, RenderTarget* target) const;

	virtual bool itemScroll(float delta);
	virtual void changeChildrenPosition(float offset_x, float offset_y);
	virtual void changePosition(float offset_x, float offset_y);
	virtual void resetActiveState();

	virtual void render();
	virtual void update();
};

