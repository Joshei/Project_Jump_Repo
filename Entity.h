#pragma once
#include <SFML/Graphics.hpp>
#include <String.h>

class Entity 
{
public:
	int x;
	int y;
	std::string type;
	sf::Sprite * sprite;
	sf::Sprite * getSprite();
	
	Entity(std::string type, sf::Sprite * Object, int x1, int y1);
	static int SearchVectorForEntities(std::vector<Entity>& vector, sf::RenderWindow& inWindow, float changeX, float changeY, int isLeft1);


	//int xx = x;
};

