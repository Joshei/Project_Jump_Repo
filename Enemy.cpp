#include "Enemy.h"

Enemy::Enemy()
{

}
Enemy::Enemy(std::vector<EnemyOnPlatform>& enemyVector1)
{
	


	
	enemyVector2 = enemyVector1;
	
	direction = right;
	

}


sf::Sprite* Enemy::getSprite()
{
	if (direction == right)
	{
		return(gottenSprite1);
	}
	else
	{
		return(gottenSprite2);
	}
}


int Enemy::changePlatformEdgesForEnemy(sf::RenderWindow& inWindow, int changeX)
{
	for (std::vector<EnemyOnPlatform>::iterator it = enemyVector2.begin(); it != enemyVector2.end(); ++it)
	{
		
		{

			it->platformLeftEdge = it->platformLeftEdge + changeX;
			
		}
		
		{
			it->platformRightEdge = it->platformRightEdge + changeX;
			
		}
	}

	return(1);
}

int Enemy::moveEnemies(sf::RenderWindow& inWindow, float changeX, float changeY, int isLeft1)
{
	
	for (std::vector<EnemyOnPlatform>::iterator it = enemyVector2.begin(); it != enemyVector2.end(); ++it)
	{
			//
			if (direction == right)
			{
				gottenSprite1 = it->getSpriteR();
			}
			else
			{
				gottenSprite2 = it->getSpriteL();
			}
			
			


		if (direction == right)
		{
			it->x = it->x + changeX;

			int remaining = it->platformRightEdge - (it->x + 76);
			if (remaining < 0)
			{
				it->x = it->platformRightEdge -76 + remaining;
				direction = left;
			}
			
			
			gottenSprite1->setPosition(it->x, it->y);
			inWindow.draw(*gottenSprite1);
			
		}


		else if (direction == left)
		{
			it->x = it->x - changeX;
			int remaining = (it->x - (it->platformRightEdge - 300));
			if (remaining < 0)
			{
				it->x = (it->platformRightEdge - 300) + (-1 * remaining);
				direction = right;
			}
			

			gottenSprite2->setPosition(it->x, it->y);
			inWindow.draw(*gottenSprite2);
		}
	}



	return(1);
}