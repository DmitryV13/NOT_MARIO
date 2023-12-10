#include "stdafx.h"
#include "RedMutant.h"

RedMutant::RedMutant(TileMap& map, Player& pl) :Enemy(map, pl)
{
	{
		RedMutant::init_texture();
		RedMutant::init_sprite();
	}
}

void RedMutant::init_texture()
{
	if (!chubacabra_t_.loadFromFile("Textures/chubacabra.png"))
	{
		std::cout << "Error -> Enemy_chubacabra -> couldn't load enemy_chubacabra texture" << std::endl;
	}
}

void RedMutant::init_sprite()
{

	current_area = IntRect(0, 0, 1280, 256);
	observation_area.setTextureRect(current_area);

	Enemy_S.setTexture(chubacabra_t_);
	current_frame = IntRect(0, 0, 60, 95);
	Enemy_S.setTextureRect(current_frame);
}

void RedMutant::update_movement()
{
	//decision explorer
	if (on_ground)
	{
		if (update_collision_x())
		{
			//переписать для подьема без прыжка
			if (!update_collision_x_jump())
			{

				
				jump(1);
				on_ground = false;
				jump_tile = true;
			}
			else moving *= -1.f;
		}
	}
	//step limits
	if (step_right == max_step)
	{
		moving *= -1.f;
		step_right = 0;
		animation_counter_think = 12;
	}
	if (step_left == max_step)
	{
		animation_counter_think = 12;
		moving *= -1.f;
		step_left = 0;
	}


	//turning when approaching the map boundaries


	//in case of random map generation
	// std::random_device rd;
	// std::mt19937 gen(rd());
	// std::uniform_int_distribution<int> decision_to_think(0, 10000);
	// int rand = decision_to_think(gen);
	// if(rand <25)
	// {
	// 	animation_counter_think = 12;
	// 	moving *= -1.f;
	// }
	walk(moving);
}

void RedMutant::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 60;
				if (current_frame.left >= 600.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 660.f)
				{
					current_frame.left = 60.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
			}

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_IDLE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 60;
				if (current_frame.left >= 600.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 660.f)
				{
					current_frame.left = 60.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
			}


			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			count_atack++;
			if (looks_to_the_right)
			{
				current_frame.left += 60;
				if (current_frame.left >= 600.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 660.f)
				{
					current_frame.left = 60.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
			}

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}

	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING_DOWN)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 60;
				if (current_frame.left >= 600.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 660.f)
				{
					current_frame.left = 60.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
			}


			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SHOT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 60;
				if (current_frame.left >= 600.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 660.f)
				{
					current_frame.left = 60.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
			}

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SLEEP)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 60;
				if (current_frame.left >= 600.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 660.f)
				{
					current_frame.left = 60.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
			}
			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}


	else
	{
		animation_timer.restart();
	}
}

void RedMutant::shot()
{
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;

}




void RedMutant::attack()
{
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;
	FloatRect en = get_global_bounds();
	FloatRect pl = player_->getGlobalBounds();
	if (displacement.x != 0.f && en.intersects(pl) && !player_->stan() )
	{
		sf::Vector2f tmp = calculateRandomPosition(get_global_bounds(), 10);
		std::cout << tmp.x / 64 << " " << tmp.y / 64 << "\n";
		if (tmp.x / 64 == 0)tmp.x = 64;
		if (tmp.x / 64 == sandbox->getMapWidth() / 64)tmp.x = sandbox->getMapWidth() - 64;
		if (!sandbox->isBlock(tmp.x / 64, tmp.y / 64))set_position(tmp.x, tmp.y);
		else set_position(get_position().x, get_position().y);

	}
	if (sting())
	{
		shot();
		displacement.x = 0;
		displacement_max = 1.f;
		
		if (pl.left < en.left)
		{
			if (looks_to_the_right)
			{
				looks_to_the_right = false;
				looks_to_the_left = true;
			}
		}
		else if (pl.left > en.left)
		{
			if (looks_to_the_left)
			{
				looks_to_the_right = true;
				looks_to_the_left = false;
			}
		}
		if (en.intersects(pl))count_atack++;
		
		if(count_atack > 100)//Зависит от количества кадров атаки
		{
			count_atack = 0;
			sf::Vector2f tmp = calculateRandomPosition(get_global_bounds(), 10);
			std::cout << tmp.x / 64 << " " << tmp.y / 64 << "\n";
			if (tmp.x / 64 == 0)tmp.x = 64;
			if (tmp.x / 64 == sandbox->getMapWidth() / 64)tmp.x = sandbox->getMapWidth() - 64;
			if (!sandbox->isBlock(tmp.x / 64, tmp.y / 64))set_position(tmp.x, tmp.y);
			else set_position(get_position().x,get_position().y);
			
		}

	}
	else
	{
		if (player_l_r[0] && displacement.x > 0)
		{
			displacement.x = 0;
			moving = -1.f;
			looks_to_the_right = false;
			looks_to_the_left = true;
		}
		else if (player_l_r[0] && displacement.x < 0)
		{
			displacement.x = 0;
			//moving= 1.f;
			looks_to_the_right = false;
			looks_to_the_left = true;
		}
		else if (player_l_r[1] && displacement.x > 0)
		{
			displacement.x = 0;
			looks_to_the_right = true;
			looks_to_the_left = false;
			//moving = 1.f;
		}
		else
		{
			displacement.x = 0;
			moving = 1.f;
			looks_to_the_right = true;
			looks_to_the_left = false;
		}
		displacement.x += 5 * moving * acceleration;
		//displacement.x += 10 * moving * acceleration;
	}
	


	if (!isPlayerInRadius(observation_area.getGlobalBounds(), player_->getGlobalBounds(),128))
	{
		reset_attention();
		//float intersectionRadius = 50.0f;
		//teleportBehindPlayer(Enemy_S, sandbox->get_player_glob_bound(), intersectionRadius);
	}
	
	// displacement.x = 0;
}
//sf::Vector2f RedMutant::calculateRandomPosition(const sf::FloatRect& playerBounds, int jumpDistance)
//{
//	int maxAttempts = 1000000;
//
//	for (int i = 0; i < maxAttempts; ++i)
//	{
//		
//		int direction = (rand() % 2 == 0) ? -1 : 1;
//
//		float newX = playerBounds.left + direction * jumpDistance * sandbox->getSizeTexture();
//		float newY = playerBounds.top;
//
//		if (newX >= 0 && newX < sandbox->getMapWidth() && newY >= 0 && newY < sandbox->getMapHeight())
//		{
//			if (!sandbox->isBlock(newY / sandbox->getSizeTexture(), newX / sandbox->getSizeTexture()))
//			{
//				return sf::Vector2f(newX, newY);
//			}
//		}
//		newY -= sandbox->getSizeTexture();
//		if (newX >= 0 && newX < sandbox->getMapWidth() && newY >= 0 && newY < sandbox->getMapHeight())
//		{
//			if (!sandbox->isBlock(newY / sandbox->getSizeTexture(), newX / sandbox->getSizeTexture()))
//			{
//				return sf::Vector2f(newX, newY);
//			}
//		}
//	}
//
//	return get_position();
//}
sf::Vector2f RedMutant::calculateRandomPosition(const sf::FloatRect& playerBounds, int jumpDistance)
{
	int x = static_cast<int>(get_position().x / sandbox->getSizeTexture());
	int y = static_cast<int>(get_position().y / sandbox->getSizeTexture());
	int count = 10000;
	int startDirection = (rand() % 2 == 0) ? 1 : -1;
	while (true)
	{
		for (int i = startDirection * jumpDistance; i != 0; i -= startDirection) {
			int newX = x + i;
			int newY = y;

			if (sandbox->outOfMap(newY + 1, newX) && sandbox->isBlock(newY + 1, newX)) {
				newY += 1;
			}

			if (sandbox->outOfMap(newY, newX)) {
				if (!sandbox->isBlock(newY, newX)) {
					return sf::Vector2f(newX * sandbox->getSizeTexture(), newY * sandbox->getSizeTexture());
				}
			}
		}
		if(!count--)return get_position();
	}
	

	
}




void RedMutant::clear_shot()
{
}

bool RedMutant::search_for_enemies()
{

	FloatRect look = observation_area.getGlobalBounds();
	FloatRect pl = player_->getGlobalBounds();

	PL_SIDE playerSide = getPlayerSide(player_->getPosition().x, get_position().x);
	if (playerSide == PL_SIDE::RIGHT && look.intersects(pl))
	{
		player_l_r[1] = true;
		player_l_r[0] = false;
		return true;
	}
	else if (playerSide == PL_SIDE::LEFT && look.intersects(pl))
	{
		player_l_r[0] = true;
		player_l_r[1] = false;
		return true;
	}

	player_l_r[0] = false;
	player_l_r[1] = false;
	return false;
	// int centerX = get_position().x / 60;
	// int centerY = get_position().y / 60;
	//
	//
	// for (int i = centerY - 3;  i <= centerY + 3; i++)
	// {
	// 	for (int j = centerX - 6; j <= centerX + 6; j++)
	// 	{
	// 		if (i >= 0 && i < 40 && j >= 0 && j < TileFactory::m && i < TileFactory::n && i > 0)
	// 		{
	// 			if (sandbox->isOccupied(i, j))
	// 			{
	// 				return true;
	// 			}
	// 		}
	// 	}
	// }
	//
	// return false;
	int centerX = get_position().x / 64;
	int centerY = get_position().y / 64;


	for (int i = centerY - 1; i <= centerY + 1; i++)
	{
		for (int j = centerX + 1; j <= centerX + 15; j++)
		{
			if (i >= 0 && i < sandbox->getMapHeight() / 64 && j >= 0 && j < sandbox->getMapWidth() / 64)
			{
				if (sandbox->isOccupied(i, j))
				{
					player_l_r[1] = true;
					player_l_r[0] = false;
					return true;
				}
			}
		}
	}


	for (int i = centerY - 1; i <= centerY + 1; i++)
	{
		for (int j = centerX - 15; j <= centerX; j++)
		{
			if (i >= 0 && i < sandbox->getMapHeight() / 64 && j >= 0 && j < sandbox->getMapWidth() / 64)
			{
				if (sandbox->isOccupied(i, j))
				{
					player_l_r[0] = true;
					player_l_r[1] = false;
					return true;
				}
			}
		}
	}

	player_l_r[0] = false;
	player_l_r[1] = false;
	return false;
}

void RedMutant::reset_attention()
{
	displacement_max = 1.f;
	displacement.x += moving * acceleration;
	count_jump = 0;
}
