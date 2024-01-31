#include "stdafx.h"
#include "laser_weapon.h"

laser_weapon::laser_weapon(TileMap& map, const int compar, const float i,
                           const float j, const bool direction, GeneralInfo* player_info_)
	: attack(12), player_info(player_info_)
{
	dir_x = direction;
	init_physics();
	sandbox = &map;

	init_variables(compar);

	init_texture();
	init_sprite();
	set_position(i, j);
	init_animation();
	laser_timer.restart();
}

const bool& laser_weapon::get_animation_switch()
{
	bool tmp_switch = animation_switch;
	if (animation_switch)
	{
		animation_switch = false;
	}
	return tmp_switch;
}

sf::Vector2f laser_weapon::get_position() const
{
	return laser_S.getPosition();
}

const FloatRect laser_weapon::get_global_bounds() const
{
	return laser_S.getGlobalBounds();
}

void laser_weapon::set_position(const float x, const float y)
{
	laser_S.setPosition(x, y);
}


void laser_weapon::update()
{
	//FIXED:add a provision
	update_animation();
}

void laser_weapon::update_animation()
{
	if (animation_state == LASER_ANIMATION_STATES::LASER_FIRST)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (dir_x)
			{
				current_frame.left = 0;
				current_frame.top += 60;
				if (current_frame.top >= 180)
				{
					current_frame.top = 0.f;
				}
				current_frame.width = 65;
			}
			else
			{
				current_frame.top += 60;
				if (current_frame.top >= 180)
				{
					current_frame.top = 0.f;
				}
				current_frame.left = 64;
				current_frame.width = -64;
			}
			laser_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == LASER_ANIMATION_STATES::LASER_NEXT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			current_frame.left = 120;
			current_frame.top += 60;
			if (current_frame.top >= 180)
			{
				current_frame.top = 0.f;
			}
			current_frame.width = 64;

			laser_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
}

void laser_weapon::reset_animation_timer()
{
	animation_timer.restart();
	animation_switch = true;
}


void laser_weapon::init_texture()
{
	if (!laser_T.loadFromFile("Textures/Enemies/laser.png"))
	{
		std::cout << "Error -> laser -> couldn't load laser texture" << '\n';
	}
}


void laser_weapon::init_sprite()
{
	if (LASER_ANIMATION_STATES::LASER_FIRST == animation_state && dir_x)
	{
		laser_S.setTexture(laser_T);
		current_frame = IntRect(0, 0, 65, 60);
		laser_S.setTextureRect(current_frame);
	}
	else
	{
		laser_S.setTexture(laser_T);
		current_frame = IntRect(65, 0, -65, 60);
		laser_S.setTextureRect(current_frame);
	}
	if (LASER_ANIMATION_STATES::LASER_NEXT == animation_state)
	{
		laser_S.setTexture(laser_T);
		current_frame = IntRect(120, 0, 64, 60);
		laser_S.setTextureRect(current_frame);
	}
}

void laser_weapon::init_variables(const int compar)
{
	if (compar == first)
		animation_state = LASER_ANIMATION_STATES::LASER_FIRST;
	else animation_state = LASER_ANIMATION_STATES::LASER_NEXT;
}

void laser_weapon::init_animation()
{
	animation_switch = true;
	animation_timer.restart();
}

void laser_weapon::init_physics()
{
	first = 1;
	next = 2;
}

sf::Vector2f laser_weapon::calculate_end_position(float x) const
{
	sf::Vector2f new_position(get_position().x, get_position().y);
	int j;
	int i = (laser_S.getPosition().y) / 64;
	if (dir_x)j = (laser_S.getPosition().x + x + laser_S.getGlobalBounds().width) / 64;
	else j = (laser_S.getPosition().x + x) / 64;

	int g = 0;

	while (sandbox->outOfMap(i, j) && !sandbox->isBlock(i, j) && g < 40)
	{
		g++;
		new_position.x += x / 2;
		i = (new_position.y) / 64;
		if (dir_x)j = (new_position.x + laser_S.getGlobalBounds().width) / 64;
		else j = (new_position.x) / 64;
	}
	if (dir_x)
	{
		new_position.x = (j - 1) * 64;
	}
	else
	{
		new_position.x = (j + 1) * 64;
	}
	return new_position;
}

void laser_weapon::render_fl(sf::RenderTarget& target)
{
	float x = dir_x ? 64.0f : -64.0f;


	const sf::Vector2f start_position = get_position();
	sf::Vector2f end_position = calculate_end_position(x);
	damage(start_position, end_position);
	if (start_position.x / 64 == end_position.x / 64)return;
	if (start_position == end_position)return;
	if (abs(end_position.x + start_position.x) > 128)
	{
		if (dir_x)
		{
			end_position.x += 32;
			update_animation();
			laser_S.setPosition(start_position);
			target.draw(laser_S);

			current_frame.left = 80;
			current_frame.width = -120;
			laser_S.setTextureRect(current_frame);
			if (end_position.x >= start_position.x)
			{
				laser_S.setPosition(end_position);
				target.draw(laser_S);
			}


			laser_S.setPosition(start_position);
			current_frame.width = 65;
			current_frame.left = 0;
			laser_S.setTextureRect(current_frame);
		}

		else
		{
			end_position.x -= 32;
			laser_S.setPosition(start_position);
			target.draw(laser_S);

			current_frame.width = 120;
			current_frame.left = 8;
			laser_S.setTextureRect(current_frame);
			if (end_position.x + 64 < start_position.x)
			{
				laser_S.setPosition(end_position);
				target.draw(laser_S);
			}

			laser_S.setPosition(start_position);
			current_frame.left = 65;
			current_frame.width = -65;
			laser_S.setTextureRect(current_frame);
		}
	}
	else
	{
		if (dir_x)
		{
			end_position.x += 32;
			update_animation();
			laser_S.setPosition(start_position);
			target.draw(laser_S);

			current_frame.left = 67;
			current_frame.width = -67;
			laser_S.setTextureRect(current_frame);
			if (end_position.x >= start_position.x)
			{
				laser_S.setPosition(end_position);
				target.draw(laser_S);
			}


			laser_S.setPosition(start_position);
			current_frame.width = 65;
			current_frame.left = 0;
			laser_S.setTextureRect(current_frame);
		}

		else
		{
			end_position.x -= 32;
			laser_S.setPosition(start_position);
			target.draw(laser_S);

			current_frame.width = 60;
			current_frame.left = 8;
			laser_S.setTextureRect(current_frame);
			if (end_position.x + 64 < start_position.x)
			{
				laser_S.setPosition(end_position);
				target.draw(laser_S);
			}

			laser_S.setPosition(start_position);
			current_frame.left = 65;
			current_frame.width = -65;
			laser_S.setTextureRect(current_frame);
		}
	}
}

bool laser_weapon::collision_block(int i, int j) const
{
	constexpr float block_size = 64.f;
	const float block_x = static_cast<float>(j * block_size);
	const float block_y = static_cast<float>(i * block_size);


	const sf::FloatRect block_rect(block_x, block_y, block_size, block_size);
	if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j) && block_rect.intersects(laser_S.getGlobalBounds()))
	{
		return false;
	}
	return true;
}

bool laser_weapon::update_collision_x()
{
	constexpr int block_size = 64;
	int total_pixels = 0;
	int collided_pixels = 0;

	const sf::Vector2f start_position = get_position();
	const sf::Vector2f new_position = start_position;

	for (float y = laser_S.getPosition().y; y < laser_S.getPosition().y + laser_S.getGlobalBounds().height; ++y)
	{
		for (float x = laser_S.getPosition().x; x < laser_S.getPosition().x + laser_S.getGlobalBounds().width; ++x)
		{
			int i = static_cast<int>(y / block_size);
			int j = static_cast<int>(x / block_size);
			++total_pixels;
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j))
			{
				++collided_pixels;
			}
		}
	}

	set_position(new_position.x, new_position.y);

	return (collided_pixels > total_pixels * 0.2);
}

void laser_weapon::damage(sf::Vector2f start_position, sf::Vector2f end_position)
{
	if (laser_timer.getElapsedTime().asSeconds() >= 0.5f)
	{
		laser_timer.restart();
		if (dir_x)
		{
			sf::RectangleShape greenSquare(sf::Vector2f(((end_position.x - start_position.x) + 64), 40));
			greenSquare.setPosition(start_position.x, start_position.y);
			if (greenSquare.getGlobalBounds().intersects(player_info->getGlobalBounds()))
			{
				player_info->changeHP(-attack - (rand() % 5));
			}
		}
		else
		{
			sf::RectangleShape greenSquare(sf::Vector2f((abs(start_position.x - end_position.x) + 64), 40));
			greenSquare.setPosition(end_position.x, end_position.y);
			if (greenSquare.getGlobalBounds().intersects(player_info->getGlobalBounds()))
			{
				player_info->changeHP(-attack - (rand() % 5));
			}
		}
	}
}

void laser_weapon::render(sf::RenderTarget& target)
{
	float x = dir_x ? 64.0f : -64.0f;
	const sf::Vector2f start_position = get_position();
	sf::Vector2f current_position = start_position;
	sf::Vector2f end_position = calculate_end_position(x);

	laser_S.setPosition(current_position);
	if (!update_collision_x())target.draw(laser_S);

	while (true)
	{
		current_position.x += x;
		cout_las++;
		if (hit_a_wall(current_position, x)|| cout_las>20)
		{
			if (!dir_x)
			{
				current_frame.left = 200;
				current_frame.width = 64;
				laser_S.setPosition(current_position);
				laser_S.setTextureRect(current_frame);
				if (!update_collision_x())target.draw(laser_S);

				current_frame.left = 120;
				current_frame.width = 64;

				laser_S.setTextureRect(current_frame);
			}
			else
			{
				current_frame.left = 220;
				current_frame.width = 50;
				laser_S.setPosition(current_position);
				laser_S.setTextureRect(current_frame);
				if (!update_collision_x())target.draw(laser_S);

				current_frame.left = 120;
				current_frame.width = 64;

				laser_S.setTextureRect(current_frame);
			}
			laser_S.setPosition(start_position);
			// If hit a wall, stop drawing

			cout_las= 0;
			return;
		}

		laser_S.setPosition(current_position);

		if (!update_collision_x())target.draw(laser_S);

		
	}
}


bool laser_weapon::hit_a_wall(const sf::Vector2f& current_position, const float x) const

{
	const int center_x = static_cast<int>((current_position.x + (laser_S.getGlobalBounds().width * 0.5f)) / 64);
	const int center_y = static_cast<int>(current_position.y / 64);

	const int direction = (x > 0) ? 1 : -1;
	const int next_x = center_x + direction;
	const int next_y = center_y;

	if (sandbox->outOfMap(next_y, next_x) && sandbox->isBlock(next_y, next_x))
	{
		return true;
	}

	return false;
}
