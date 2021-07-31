#include "Misc.h"
#include <SFML/Graphics.hpp>

Misc::Misc(int a)
{

}
Misc::Misc()
{

}
Misc::Misc(std::vector<Misc> &  enemyVector1, sf::RenderWindow& inWindow, int x1, sf::Sprite * sprite)
{
	enemyVector = enemyVector1;
	x = x1;
	gottenSprite = sprite;
	
	if (!texture1.loadFromFile("enemyL.png"))
	{
		int a = 0;
	}
	
	gottenSprite->setTexture(texture1);
}

int Misc::moveEnemies(sf::RenderWindow& inWindow, float changeX, float changeY, int isLeft1)
{
	
	for (std::vector<Misc>::iterator it = enemyVector.begin(); it != enemyVector.end(); ++it)
	{
		
		gottenSprite = it->getSprite();

		it->x = it->x - changeX;
		gottenSprite->setPosition((it->x), 524);
		//}

		if (it->x > -76 && it->x <= (800))
		{
			
			inWindow.draw(*gottenSprite);
		}
		if (it->x < -76)
		{
			it->x = 1600;
		}
	}
	
	return(1);
}
sf::Sprite * Misc::getSprite(void)
{
	return(gottenSprite);
}