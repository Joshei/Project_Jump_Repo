#include "enemyOnPlatform.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
 
 
EnemyOnPlatform::EnemyOnPlatform(int x1, int y1, int leftEdge, int rightEdge, sf::Sprite * spriteL, sf::Sprite * spriteR)
{

	platformLeftEdge = leftEdge;
	platformRightEdge = rightEdge;

	gottenSprite1 = spriteL;
	gottenSprite2 = spriteR;

	height = 0;
	width = 0;
	
	if (!texture1.loadFromFile("enemyL.png"))
	{
		int a = 0;
	}
	if (!texture2.loadFromFile("enemyR.png"))
	{
		int a = 0;
	}

	gottenSprite1->setTexture(texture1);
	
	gottenSprite2->setTexture(texture2);
	x = x1;
	y = y1;
	
	
}

sf::Sprite * EnemyOnPlatform::getSpriteL(void)
{
	return(gottenSprite1);
}

sf::Sprite* EnemyOnPlatform::getSpriteR(void)
{
	return(gottenSprite2);
}
