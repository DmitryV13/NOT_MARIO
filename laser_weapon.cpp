#include "stdafx.h"
#include "laser_weapon.h"

laser_weapon::laser_weapon(TileMap& map, int compar, float i,
	float j, bool direction, GeneralInfo* player_info_)
	:attack(12), player_info(player_info_)
{
	//player = pl;
	dir_x = direction;
	init_physics();
	sandbox = &map;

	init_variables(compar);
	
	init_texture();
	init_sprite();
	set_position(i, j);
	laser_timer.restart();
}

const bool& laser_weapon::get_animation_switch()
{
	bool tmpSwitch = animation_switch;
	if (animation_switch)
	{
		animation_switch = false;
	}
	return tmpSwitch;
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


//void laser_weapon::update(sf::Vector2f pos_Enemy)
void laser_weapon::update()
{
	//FIXED:add a provision
	//set_position(pos_Enemy.x, pos_Enemy.y);
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
				if (current_frame.top >= 180.f)
				{
					current_frame.top = 0.f;
				}
				current_frame.width = 65;
			}
			else
			{
				

				current_frame.top += 60;
				if (current_frame.top >= 180.f)
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
			if (current_frame.top >= 180.f)
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
		std::cout << "Error -> laser -> couldn't load laser texture" << std::endl;
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

void laser_weapon::init_variables(int compar)
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

//bool laser_weapon::update_collision_x(float x)
//{
//	bool wasCollision = false;
//	sf::Vector2f newPosition(get_position().x, get_position().y);
//	int i = (laser_S.getPosition().y + laser_S.getGlobalBounds().height) / 64;
//	
//	int j = (laser_S.getPosition().x + x +
//		laser_S.getGlobalBounds().width) / 64;
//	
//	if (i >= 0 && i < sandbox->getMapHeight() / 64 && j >= 0 && j < sandbox->getMapWidth() / 64)return wasCollision;
//	if (sandbox->isBlock(i, j) || j <= 0 || j > sandbox->getMapWidth() / 64)
//	{
//		wasCollision = true;
//		if (x >= 0)
//		{
//			newPosition.x = j * sandbox->getSizeTexture() - laser_S.getGlobalBounds().width;
//		}
//		if (x < 0)
//		{
//			newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
//		}
//	}
//	//}
//	//}
//	//laser_S.setPosition(newPosition.x, newPosition.y);
//	return wasCollision;
//}

sf::Vector2f laser_weapon::calculateEndPosition(float x)
{
	sf::Vector2f newPosition(get_position().x, get_position().y);
	int j;
	int i = (laser_S.getPosition().y) / 64;
	if (dir_x)j = (laser_S.getPosition().x + x + laser_S.getGlobalBounds().width) / 64;
	else j = (laser_S.getPosition().x + x) / 64;

	int g = 0;
	
	while (sandbox->outOfMap(i, j) && !sandbox->isBlock(i, j) && g < 64)
	{
		g++;
		newPosition.x += x / 2;
		i = (newPosition.y) / 64;
		if (dir_x)j = (newPosition.x + laser_S.getGlobalBounds().width) / 64;
		else j = (newPosition.x) / 64;
	}
	if (dir_x) {
		newPosition.x = (j - 1) * 64;
	}
	else {
		newPosition.x = (j + 1) * 64;
	}
	return newPosition;
}
void laser_weapon::render_FL(sf::RenderTarget& target)
{

	float x = dir_x ? 64.0f : -64.0f;

	



	sf::Vector2f startPosition = get_position();
	sf::Vector2f endPosition = calculateEndPosition(x);
	damage(startPosition, endPosition);
	if (startPosition.x / 64 == endPosition.x / 64)return;
	if (startPosition == endPosition)return;
	if(abs(endPosition.x + startPosition.x)>128)
	{
		if (dir_x)
		{
			endPosition.x += 32;
			update_animation();
			laser_S.setPosition(startPosition);
			target.draw(laser_S);

			current_frame.left = 80;
			current_frame.width = -120;
			laser_S.setTextureRect(current_frame);
			if (endPosition.x >= startPosition.x)
			{
				laser_S.setPosition(endPosition);
				target.draw(laser_S);
			}


			laser_S.setPosition(startPosition);
			current_frame.width = 65;
			current_frame.left = 0;
			laser_S.setTextureRect(current_frame);

		}

		else
		{
			endPosition.x -= 32;
			laser_S.setPosition(startPosition);
			target.draw(laser_S);

			current_frame.width = 120;
			current_frame.left = 8;
			laser_S.setTextureRect(current_frame);
			if (endPosition.x + 64 < startPosition.x)
			{
				laser_S.setPosition(endPosition);
				target.draw(laser_S);
			}

			laser_S.setPosition(startPosition);
			current_frame.left = 65;
			current_frame.width = -65;
			laser_S.setTextureRect(current_frame);
		}
	}
	else {

		if (dir_x)
		{
			endPosition.x += 32;
			update_animation();
			laser_S.setPosition(startPosition);
			target.draw(laser_S);

			current_frame.left = 67;
			current_frame.width = -67;
			laser_S.setTextureRect(current_frame);
			if (endPosition.x >= startPosition.x)
			{
				laser_S.setPosition(endPosition);
				target.draw(laser_S);
			}


			laser_S.setPosition(startPosition);
			current_frame.width = 65;
			current_frame.left = 0;
			laser_S.setTextureRect(current_frame);

		}

		else
		{
			endPosition.x -= 32;
			laser_S.setPosition(startPosition);
			target.draw(laser_S);

			current_frame.width = 60;
			current_frame.left = 8;
			laser_S.setTextureRect(current_frame);
			if (endPosition.x + 64 < startPosition.x)
			{
				laser_S.setPosition(endPosition);
				target.draw(laser_S);
			}

			laser_S.setPosition(startPosition);
			current_frame.left = 65;
			current_frame.width = -65;
			laser_S.setTextureRect(current_frame);
		}
	}
}
bool laser_weapon::collision_block(int i, int j)
{
	float blockSize = 64.f;
	float blockX = static_cast<float>(j * blockSize);
	float blockY = static_cast<float>(i * blockSize);

	
	sf::FloatRect blockRect(blockX, blockY, blockSize, blockSize);
	if (sandbox->outOfMap(i,j) && sandbox->isBlock(i,j) && blockRect.intersects(laser_S.getGlobalBounds()))
	{
		return false;
	}
	return true;
}

bool laser_weapon::update_collision_x()
{
	int blockSize = 64;
	int totalPixels = 0;
	int collidedPixels = 0;

	sf::Vector2f startPosition = get_position();
	sf::Vector2f newPosition = startPosition;

	for (float y = laser_S.getPosition().y; y < laser_S.getPosition().y + laser_S.getGlobalBounds().height; ++y)
	{
		for (float x = laser_S.getPosition().x; x < laser_S.getPosition().x + laser_S.getGlobalBounds().width; ++x)
		{
			int i = static_cast<int>(y / blockSize);
			int j = static_cast<int>(x / blockSize);
			++totalPixels;
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j))
			{
					++collidedPixels;
			}
		}
	}

	set_position(newPosition.x, newPosition.y);

	return (collidedPixels > totalPixels * 0.2);
}

void laser_weapon::damage(sf::Vector2f startPosition, sf::Vector2f endPosition)
{
	if (laser_timer.getElapsedTime().asSeconds() >= 0.5f)
	{
		laser_timer.restart();
		if(dir_x)
		{
			sf::RectangleShape greenSquare(sf::Vector2f(((endPosition.x- startPosition.x)+64), 40));
		greenSquare.setFillColor(sf::Color::Green);
		greenSquare.setPosition(startPosition.x, startPosition.y);
		if (greenSquare.getGlobalBounds().intersects(player_info->getGlobalBounds())) {
			//player->changeHP(-attack - (rand() % 5));
			player_info->changeHP(-attack - (rand() % 5));
		}
		
		
		}
		else
		{
			sf::RectangleShape greenSquare(sf::Vector2f((abs( startPosition.x- endPosition.x) + 64), 40));
			greenSquare.setFillColor(sf::Color::Green);
			greenSquare.setPosition(endPosition.x, endPosition.y);
			if (greenSquare.getGlobalBounds().intersects(player_info->getGlobalBounds())) {
				//player->changeHP(-attack - (rand() % 5));
				player_info->changeHP(-attack - (rand() % 5));
			}
		
		
		}
		



	}
}

void laser_weapon::render(sf::RenderTarget& target)
{

	float x = dir_x ? 64.0f : -64.0f;
	sf::Vector2f startPosition = get_position();
	sf::Vector2f currentPosition = startPosition;
	sf::Vector2f endPosition = calculateEndPosition(x);

	//if (startPosition == endPosition) return;
	laser_S.setPosition(currentPosition);
	if (!update_collision_x())target.draw(laser_S);

	while (true)
	{
		currentPosition.x += x;

		if (hit_a_wall(currentPosition, x))
		{
			if(!dir_x){
				current_frame.left = 200;
				current_frame.width = 64;
				laser_S.setPosition(currentPosition);
				laser_S.setTextureRect(current_frame);
				if(!update_collision_x())target.draw(laser_S);

				current_frame.left = 120;
			current_frame.width = 64;
			
			laser_S.setTextureRect(current_frame);
			}
			else
			{
				current_frame.left = 220;
				current_frame.width = 50;
				laser_S.setPosition(currentPosition);
				laser_S.setTextureRect(current_frame);
				if (!update_collision_x())target.draw(laser_S);

				current_frame.left = 120;
				current_frame.width = 64;

				laser_S.setTextureRect(current_frame);
			}
			laser_S.setPosition(startPosition);
			// If hit a wall, stop drawing
			return;
		}

		laser_S.setPosition(currentPosition);
		
		if (!update_collision_x())target.draw(laser_S);

		// Optionally, you may want to check if currentPosition is close enough to endPosition
		// to avoid an infinite loop. For example:
		// if (std::abs(currentPosition.x - endPosition.x) < 1.0f) break;
	}

	//float x = dir_x ? 64.0f : -64.0f;
	//sf::Vector2f startPosition = get_position();
	//sf::Vector2f currentPosition = startPosition;
	//sf::Vector2f endPosition = calculateEndPosition(x);

	//if (startPosition == endPosition) return;
	//laser_S.setPosition(currentPosition);
	//target.draw(laser_S);
	//while (true)
	//{
	//	currentPosition.x += x;
	//	if (hit_a_wall(currentPosition, x))
	//	{
	//		// ≈сли достигли блока, прекращаем отрисовку
	//		break;
	//	}
	//	//if (dir_x)
	//	//{
	//	//	currentPosition.x += 64.0f;
	//	//}
	//	//else
	//	//{
	//	//	currentPosition.x -= 64.0f;
	//	//}

	//	laser_S.setPosition(currentPosition);
	//	target.draw(laser_S);
	//}
	//laser_S.setPosition(currentPosition);
	//target.draw(laser_S);

	//laser_S.setPosition(startPosition);
}


bool laser_weapon::hit_a_wall(const sf::Vector2f& currentPosition, float x) const

{


	int centerX = static_cast<int>((currentPosition.x + (laser_S.getGlobalBounds().width * 0.5f)) / 64);
	int centerY = static_cast<int>(currentPosition.y / 64);

	const int direction = (x > 0) ? 1 : -1;
	const int nextX = centerX + direction;
	const int nextY = centerY;

	if (sandbox->outOfMap(nextY, nextX) && sandbox->isBlock(nextY, nextX))
	{
		return true;
	}

	return false;
	/*int centerX;
	int centerY;
	const int direction = dir_x ? 1 : -1;

	if (direction == 1)
	{
		centerX = static_cast<int>((currentPosition.x + (laser_S.getGlobalBounds().width)) / 64);
		centerY = static_cast<int>(currentPosition.y / 64);
	}
	else
	{
		centerX = static_cast<int>((currentPosition.x + (laser_S.getGlobalBounds().width)) / 64)+direction;
		centerY = static_cast<int>(currentPosition.y / 64);
	}

	const int nextX = centerX + direction;
	const int nextY = centerY;

	if (sandbox->outOfMap(nextY, nextX) && sandbox->isBlock(nextY, nextX))
	{
		return true;
	}

	return false;*/
}
