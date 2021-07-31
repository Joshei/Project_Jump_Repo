#include "Entity.h"

Entity::Entity(std::string  type1, sf::Sprite *  Object, int x1, int y1)
{
	x = x1;
	y = y1;
	sprite = Object;
	type = type1;
}
//sf::Sprite Entity::getSprite()
//{

//}
sf::Sprite * Entity::getSprite()
{
	return(sprite);
}

int Entity::SearchVectorForEntities(std::vector<Entity>& vector, sf::RenderWindow& inWindow, float changeX, float changeY, int isLeft1)
{

	sf::Sprite* gottenSprite;// = NULL;


	for (std::vector<Entity>::iterator it = vector.begin(); it != vector.end(); ++it)
	{
		//sprite is platform
		gottenSprite = it->getSprite();

		it->x = it->x + changeX;
		gottenSprite->setPosition((it->x), it->y);

		if (it->x > -150 && it->x < (800))
		{

			inWindow.draw(*it->sprite);
		}

	}
	

	return(1);
}