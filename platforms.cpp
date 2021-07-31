#include "platforms.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>"
#include "enemyOnPlatform.h"

platform::platform()
{
	
}
platform::platform(int width, int height,std::string string1, sf::Sprite * sprite)
{
	type = string1;
	platformSprite = sprite;
	
	sf::Vector2f vect;
	//vect = 0;
	vect = sprite->getPosition();
	this->x = vect.x;
	this->y = vect.y;
	this->width = width;
	this->height = height;
}

sf::Sprite * platform::getSprite()
{
	return(platformSprite);
}



int platform::advanceAllPlatforms(std::vector<platform>& vector, int changeX)
{
	sf::Sprite* gottenSprite;

	for (std::vector<platform>::iterator it = vector.begin(); it != vector.end(); ++it)
	{
		//sprite is platform
		gottenSprite = it->getSprite();

		it->x = it->x + changeX;


		gottenSprite->setPosition((it->x), it->y);

		

	}
	
	return(1);
}

int platform::drawAllPlatforms(std::vector<platform>& vector, sf::RenderWindow& inWindow )
{
	sf::Sprite* gottenSprite;

	for (std::vector<platform>::iterator it = vector.begin(); it != vector.end(); ++it)
	{
		if (it->x > -300 && it->x < (800))
		{

			inWindow.draw(*it->platformSprite);
		}

	}
	return(1);
}

//loop through platforms and move them horizontally
int platform::SearchVectorForPlatforms( std::vector<platform>& vector,sf::RenderWindow& inWindow, float changeX, float changeY, int isLeft1)
{

	sf::Sprite * gottenSprite;


	for (std::vector<platform>::iterator it = vector.begin(); it != vector.end(); ++it)
	{
		//sprite is platform
		gottenSprite = it->getSprite();

		it->x = it->x + changeX;

		gottenSprite->setPosition((it->x), it->y);

		if (it->x > -300 && it->x < (800))
		{

			inWindow.draw(*it->platformSprite);
		}

	}
	
	
	return(1);
}