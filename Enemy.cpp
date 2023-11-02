#include "stdafx.h"
#include "Enemy.h"
#include "TileMap.h"


sf::Vector2f Enemy::generateRandomStartPosition(int mapWidth, int mapHeight)
{
	//positional distribution
	//sf::Vector2f startPos;
	// int x = rand() % 6;
	//// return sf::Vector2f(8 * 73, 73 * 7);
	// 
	// if(x == 1)return sf::Vector2f(73, mapHeight - 73 * 4);
	// if(x == 2) return sf::Vector2f(mapWidth - 73 * 50, mapHeight - 73 * 4);
	// if (x == 3)return sf::Vector2f(mapWidth - 73 * 80, mapHeight - 73 * 4);
	// if (x == 4) return sf::Vector2f(8 * 73, 73 * 7);
	// if (x == 5) return sf::Vector2f(32 * 73, 73 * 6);

	//  randomized distribution
	int maxAttempts = 100000;

	for (int i = 0; i < maxAttempts; i++)
	{
		int x = 60 + rand() % (mapWidth - 60 * 2 + 1);
		int y = 60 + rand() % (mapHeight - 60 * 2 + 1);

		int centerX = (x + 60) / 60;
		int centerY = (y + 60) / 60;

		bool collisionDetected = false;

		if (sandbox->isBlock(centerY, centerX))
		{
			collisionDetected = true;
		}
		else
		{
			for (int dx = -2; dx <= 2; dx++)
			{
				for (int dy = -3; dy <= 3; dy++)
				{
					int blockX = (x + dx) / 60;
					int blockY = (y + dy) / 60;
					if (sandbox->isBlock(blockY, blockX))
					{
						collisionDetected = true;
						break;
					}
				}
				if (collisionDetected)
				{
					break;
				}
			}
		}

		if (!collisionDetected)
		{
			return sf::Vector2f(x, y);
		}
	}

	return sf::Vector2f(0, 0);
}

void Enemy::init_variables()
{
	animationState = Enemy_ANIMATION_STATES::ENEMY_IDLE;
}

Enemy::Enemy(TileMap& map)
{
	sandbox = &map;
	//pos_Player[TileFactory::n][TileFactory::m] = sandbox.getTile();
	init_variables();
	init_animation();
	init_physics();
	startPosition = generateRandomStartPosition(sandbox->getMapWidth(), sandbox->getMapHeight());
	setPosition(startPosition.x, startPosition.y);

}

sf::Vector2f Enemy::getPosition() const
{
	return Enemy_S.getPosition();
}

const FloatRect Enemy::getGlobalBounds() const
{
	return Enemy_S.getGlobalBounds();
}

void Enemy::setPosition(const float x, const float y)
{
	Enemy_S.setPosition(x, y);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(Enemy_S);
}

void Enemy::update()
{
	updateMovement();
	//search_for_enemies();
	updateAnimation();
	updatePhysics();
}

void Enemy::resetAnimationTimer()
{
	animationTimer.restart();
	animationSwitch = true;
}

bool Enemy::search_for_enemies() {
	int centerX = getPosition().x / 60;
	int centerY = getPosition().y / 60;

	for (int i = centerY - 2; i <= centerY + 2; i++) {
		for (int j = centerX - 2; j <= centerX +2; j++) {
			if (i >= 0 && i < 40 && j >= 0 && j < 200) {
				if (sandbox->isOccupied(i, j)) {
					animationState = Enemy_ANIMATION_STATES::ENEMY_ATTENTION;
					return true;
				}
			}
		}
	}

	return false;
}


void Enemy::updateAnimation()
{
	if (animationState == Enemy_ANIMATION_STATES::ENEMY_MOVING_RIGHT)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			currentFrame.left += 60;
			if (currentFrame.left >= 360.f)
			{
				currentFrame.left = 0.f;
			}
			currentFrame.width = 60;
			currentFrame.top = 0;
			Enemy_S.setTextureRect(currentFrame);
			animationTimer.restart();
		}
	}
	else if (animationState == Enemy_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			currentFrame.top = 60;
			currentFrame.left = 0;
			currentFrame.width = 60;

			
			Enemy_S.setTextureRect(currentFrame);
			animationTimer.restart();
		}
	}
	else if (animationState == Enemy_ANIMATION_STATES::ENEMY_MOVING_LEFT)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			currentFrame.left -= 60;
			if (currentFrame.left <= 0.f)
			{
				currentFrame.left = 360.f;
			}
			currentFrame.width = -60;
			currentFrame.top = 0;
			Enemy_S.setTextureRect(currentFrame);
			animationTimer.restart();
		}
	}

	else
	{
		animationTimer.restart();
	}
}

void Enemy::init_animation()
{
	animationSwitch = true;
	animationTimer.restart();
}

const bool& Enemy::get_animation_switch()
{
	bool tmpSwitch = animationSwitch;
	if (animationSwitch)
	{
		animationSwitch = false;
	}
	return tmpSwitch;
}

void Enemy::init_physics()
{
	displacementMax = 1.f;
	displacementMin = 0.3f;
	acceleration = 0.4f; //óñêîðåíèå
	deceleration = 0.77f; //0.77 çàìåäëåíèå 
	gravity = 2.5f;
	velocityMaxY = 15.f;

	onGround = false;
	onWall = false;
	jumpVelocity = 7.f;

	moving = 1.f;

	stepLeft = 0;
	stepRight = 0;
	jumpTile = false;
	displacement.x = 0.f; //ïåðåìåùåíèå 
	displacement.y = 0.f;
}

void Enemy::walk(const float dir_x)
{
	if (dir_x > 0)
		stepRight++;
	if (dir_x < 0)
		stepLeft++;
	if (onWall)
	{
		displacement.x += dir_x * acceleration;

	}

	if (onGround)
	{
		displacement.x += dir_x * acceleration;
	}
	/*else if (jumpTile)
	{
		displacement.x += dir_x * acceleration;
		displacement.y += 1.f * gravity * 2;
	}*/

	// limits
	if (std::abs(displacement.x) > displacementMax)
	{
		displacement.x = displacementMax * ((displacement.x > 0.f) ? 1.f : -1.f);
	}
	if (dir_x > 0.f) animationState = Enemy_ANIMATION_STATES::ENEMY_MOVING_RIGHT;
	else animationState = Enemy_ANIMATION_STATES::ENEMY_MOVING_LEFT;

	if (search_for_enemies())
	{
		displacement.x = 0;

	}
}

void Enemy::updateMovement()
{


	if (onGround)
	{


		if (updateCollisionX())
		{

			if (!updateCollisionXJump())
			{
				onWall = true;
				jump(-65);
				onGround = false;
			}
			else moving *= -1.f;

		}
		if (Enemy_S.getPosition().x <= 0)
		{

			displacement.x = 0;
		}

		if (Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width > sandbox->getMapWidth())
		{

			displacement.x = 0;
		}

		//if (block.intersects(currentFrame))moving += -1.f;
		//if (updateCollisionXJump())moving *= -1.f;



		//if (!updateCollisionX())jumpTile = false;

	}
	/*if (stepRight == maxStep)
	{
		iterationStart = 0;
		moving *= -1.f;
		stepRight = 0;
	}
	if (stepLeft == maxStep)
	{
		moving *= -1.f;
		stepLeft = 0;
		iterationStart = 0;
	}*/
	if (Enemy_S.getPosition().x <= 0.1f || Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width > sandbox->getMapWidth())
	{

		moving *= -1.f;
	}

	walk(moving);

	/*if (!onGround)iterationStart = 0;
	if (displacement.x == 0.f && displacement.x == 0.f && !onGround)
	{
		iterationStart++;
		walk(-1.f);
		walk(1.f);
	}
	animationState = Enemy_ANIMATION_STATES::ENEMY_IDLE;
	if (updateCollisionY())
		onGround = true;
	if (updateCollisionX())
		jump(-20.0f);
	if (displacement.x == 0.f && iterationStart > iterationEnd)
	{
		moving *= -1.f;
		iterationStart = 0;
	}
	else iterationStart++;
	if (stepRight == maxStep)
	{
		iterationStart = 0;
		moving *= -1.f;
		stepRight = 0;
	}
	if (stepLeft == maxStep)
	{
		moving *= -1.f;
		stepLeft = 0;
		iterationStart = 0;
	}
	if (moving > 0.f) animationState = Enemy_ANIMATION_STATES::ENEMY_MOVING_RIGHT;
	else animationState = Enemy_ANIMATION_STATES::ENEMY_MOVING_LEFT;
	walk(moving);*/
}


void Enemy::resetVelocityY()
{
	displacement.y = 0.f;
}


void Enemy::resetJumpAccess()
{
	resetVelocityY();
	onGround = true;
	onWall = false;
	jumpTile = false;
}


void Enemy::jump(const float dir_y)
{

	if (onGround)
	{
		onGround = false;
		jumpTile = true;

		jumpVelocity = 5.5f;
	}
}


void Enemy::updatePhysics()
{
	// gravity
	displacement.y += 1.f * gravity;

	if (std::abs(displacement.y) > velocityMaxY)
	{
		displacement.y = velocityMaxY * ((displacement.y > 0.f) ? 1.f : -1.f);
	}

	//jumping
	if (jumpTile)
	{
		displacement.y -= jumpVelocity;
		displacement.x += moving * acceleration;
		//jump deceleratin
		jumpVelocity *= 0.96;
	}

	// deceleration
	displacement *= deceleration;

	// limits
	if (std::abs(displacement.x) < displacementMin || updateCollisionX())
	{
		displacement.x = 0.f;
	}
	if (std::abs(displacement.y) < displacementMin || updateCollisionY())
	{
		displacement.y = 0.f;
	}


	Enemy_S.move(displacement);
}


bool Enemy::updateCollisionX()
{
	bool wasCollision = false;

	sf::Vector2f newPosition(getPosition().x, getPosition().y);
	if (jumpTile)currentBlockX = getPosition().x / 60;
	for (int i = Enemy_S.getPosition().y / 60; i < (Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height) / 60; i
		++)
	{
		for (int j = (Enemy_S.getPosition().x + displacement.x) / 60; j < (Enemy_S.getPosition().x + displacement.x +
			Enemy_S.getGlobalBounds().width) / 60; j++)
		{
			if (sandbox->isBlock(i, j))
			{
				block.top = (i - 1) * 60;
				block.height = 60;
				block.left = (j + 1) * 60;
				block.width = 60;
				wasCollision = true;
				if (displacement.x >= 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() - Enemy_S.getGlobalBounds().width;
				}
				if (displacement.x < 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}

	//Enemy_S.setPosition(newPosition.x, newPosition.y);
	return wasCollision;
}

bool Enemy::updateCollisionXJump()
{
	bool wasCollision = false;

	sf::Vector2f newPosition(getPosition().x, getPosition().y);
	if (jumpTile)currentBlockX = getPosition().x / 60;
	for (int i = Enemy_S.getPosition().y / 60; i < (Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height) / 60; i
		++)
	{
		for (int j = (Enemy_S.getPosition().x + displacement.x) / 60; j < (Enemy_S.getPosition().x + displacement.x +
			Enemy_S.getGlobalBounds().width) / 60; j++)
		{
			if (sandbox->isBlock(i - 1, j))
			{
				wasCollision = true;
				if (displacement.x >= 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() - Enemy_S.getGlobalBounds().width;
				}
				if (displacement.x < 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}

	//Enemy_S.setPosition(newPosition.x, newPosition.y);
	return wasCollision;
}

bool Enemy::updateCollisionY()
{
	bool wasCollision = false;

	sf::Vector2f newPosition(Enemy_S.getPosition().x, Enemy_S.getPosition().y);

	for (int i = (Enemy_S.getPosition().y + displacement.y) / 60; i < (Enemy_S.getPosition().y + displacement.y +
		Enemy_S.getGlobalBounds().height) / 60; i++)
	{
		for (int j = Enemy_S.getPosition().x / 60; j < (Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width) / 60;
			j++)
		{
			if (sandbox->isBlock(i, j))
			{
				//onGround = true;
				wasCollision = true;
				if (displacement.y > 0)
				{
					resetJumpAccess();
					newPosition.y = (i * sandbox->getSizeTexture() - Enemy_S.getGlobalBounds().height);
				}
				if (displacement.y < 0)
				{
					resetJumpAccess();
					newPosition.y = i * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}
	//if (dobcoll)displacement.y = 0.f;
		//setPosition(newPosition.x, newPosition.y);
	return wasCollision;
}