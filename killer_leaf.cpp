#include "stdafx.h"
#include "killer_leaf.h"

void killer_leaf::init_texture()
{
	if (!leaf_T.loadFromFile("Textures/Enemies/sheet.png"))
	{
		std::cout << "Error -> sheet -> couldn't load sheet texture" << std::endl;
	}
}

void killer_leaf::init_sprite()
{
	leaf_S.setTexture(leaf_T);
	current_frame = IntRect(120, 0,9, 10);
	leaf_S.setTextureRect(current_frame);
}

void killer_leaf::init_animation()
{
	animation_switch = true;
	animation_timer.restart();
}


killer_leaf::killer_leaf(TileMap& map,
	vector<float>flightCord,
	GeneralInfo* player_info_):attack(20),player_info(player_info_), flight_cord_(std::move(flightCord)),extermination_flag(false)
{
	sandbox = &map;
	init_texture();
	init_sprite();
	init_animation();
	set_position(flight_cord_[0], flight_cord_[1]);
	calculation_formula();

}

sf::Vector2f killer_leaf::get_position() const
{
	return leaf_S.getPosition();
}

const FloatRect killer_leaf::get_global_bounds() const
{
	return  leaf_S.getGlobalBounds();
}

void killer_leaf::set_position(const float x, const float y)
{
	leaf_S.setPosition(x, y);
}

void killer_leaf::render(sf::RenderTarget& target)
{
	target.draw(leaf_S);

}

void killer_leaf::update()
{
	damage();
	displacement.x = moveX;
	displacement.y = moveY;
	if (update_collision_x()) { displacement.x = 0.f; extermination_flag = true; }
	if (update_collision_y()) { displacement.y = 0.f;  extermination_flag = true; }
	if (get_global_bounds().intersects(player_info->getGlobalBounds()))extermination_flag = true;
	leaf_S.move(displacement);
	update_animation();
}

void killer_leaf::update_animation()
{
	if (animation_timer.getElapsedTime().asSeconds() >= 0.1f)
	{
		
		
			current_frame.left += 9;
			if (current_frame.left >= 45)
			{
				current_frame.left = 0.f;
			}


		leaf_S.setTextureRect(current_frame);
		animation_timer.restart();
	}
}

void killer_leaf::reset_animation_timer()
{
	animation_timer.restart();
	animation_switch = true;
}

bool killer_leaf::update_collision_x()
{
	bool wasCollision = false;
	sf::Vector2f newPosition(get_position().x, get_position().y);
	for (int i = leaf_S.getPosition().y / 64; i < (leaf_S.getPosition().y + leaf_S.getGlobalBounds().height) / 64; i
		++)
	{
		for (int j = (leaf_S.getPosition().x + displacement.x) / 64; j < (leaf_S.getPosition().x + displacement.x +
			leaf_S.getGlobalBounds().width) / 64; j++)
		{
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j) || j <= 0 || j > sandbox->getMapWidth() / 64)
			{
				wasCollision = true;
				if (displacement.x >= 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() - leaf_S.getGlobalBounds().width;
				}
				if (displacement.x < 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}
	set_position(newPosition.x, newPosition.y);
	return wasCollision;
}

bool killer_leaf::update_collision_y()
{
	bool wasCollision = false;

	sf::Vector2f newPosition(leaf_S.getPosition().x, leaf_S.getPosition().y);

	for (int i = (leaf_S.getPosition().y + displacement.y) / 64; i < (leaf_S.getPosition().y + displacement.y +
		leaf_S.getGlobalBounds().height) / 64; i++)
	{
		for (int j = leaf_S.getPosition().x / 64; j < (leaf_S.getPosition().x + leaf_S.getGlobalBounds().width) / 64;
			j++)
		{
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j))
			{
				wasCollision = true;
				if (displacement.y > 0)
				{
					newPosition.y = (i * sandbox->getSizeTexture() - leaf_S.getGlobalBounds().height);
				}
				if (displacement.y < 0)
				{
					newPosition.y = i * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}

	set_position(newPosition.x, newPosition.y);
	return wasCollision;
}

void killer_leaf::damage()
{
	if(get_global_bounds().intersects(player_info->getGlobalBounds()))
	{
		player_info->changeHP(-attack - (rand() % 5));
	}
}

void killer_leaf::calculation_formula()
{


	float targetX = flight_cord_[2];
	float targetY = flight_cord_[3];

	float startX = flight_cord_[0];
	float startY = flight_cord_[1];

	float directionX = targetX - startX;
	float directionY = targetY - startY;

	float length = std::sqrt(directionX * directionX + directionY * directionY);

	if (length != 0.0f)
	{
		float normalizedDirectionX = directionX / length;
		float normalizedDirectionY = directionY / length;


		moveX = normalizedDirectionX;
		moveY = normalizedDirectionY;
	}
	/*float a, b,ax,by;
	a = ax= flight_cord_[2] - flight_cord_[0];
	b = by = flight_cord_[3] - flight_cord_[1];
	float epsilon = 1e-6;
	while (std::fabs(b) > epsilon) {
		float temp = b;
		b = std::fmod(a, b);
		a = temp;
	}


	moveX = ax/a;
	moveY = by/a;*/
}

bool killer_leaf::leaf_existence()
{
	return extermination_flag;
}









