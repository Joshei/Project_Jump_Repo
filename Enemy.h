#pragma once
#include <vector>
#include "platforms.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "platforms.h"
#include <windows.h>
#include "enemyOnPlatform.h"

//enum Facing { left, right };



class Enemy
{
public:
	enum Facing { left, right };

	sf::Texture texture2;
	sf::Texture texture1;
	int platformY;
	Facing direction;
	//right
	sf::Sprite* gottenSprite1;
	//left
	sf::Sprite* gottenSprite2;
	std::vector<EnemyOnPlatform> enemyVector2;
	int x;
	int y;
	//int platformLeftEdge;
	//int platformRightEdge;
	
	//sf::Sprite * enemySprite;
	//(int rightEdge1, int leftEdge1, int platformY1, float x1, float y1, sf::Sprite* sprite1, sf::Sprite* sprite2, std::vector<enemyOnPlatform>& enemyVector1);
	Enemy();
	Enemy(std::vector<EnemyOnPlatform>& enemyVector1);
	int moveEnemies(sf::RenderWindow& inWindow, float changeX, float changeY, int isLeft1);
	int changePlatformEdgesForEnemy(sf::RenderWindow& inWindow, int changeX);
	
	sf::Sprite * getSprite(void);
};


