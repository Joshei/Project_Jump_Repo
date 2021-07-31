#pragma once
#include <vector>
#include "Enemy.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Misc
{
public:

	sf::Texture texture1;
	int x;
	int y;
	Misc(std::vector<Misc> & enemyVector1, sf::RenderWindow& inWindow, int x1, sf::Sprite * sprite);

	sf::Sprite test;
	Misc(int i);


	Misc();
	std::vector<Misc>  enemyVector;
	//Misc(std::vector<Enemy>& enemyVector1, sf::RenderWindow& inWindow);
	int moveEnemies(sf::RenderWindow& inWindow, float changeX, float changeY, int isLeft1);
	sf::Sprite * gottenSprite;
	sf::Sprite * getSprite(void);
};
