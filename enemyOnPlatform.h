#pragma once
#include "enemyOnPlatform.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "enemyOnPlatform.h"
class EnemyOnPlatform
{
public:
	//int vari;
	int height;
	int width;
	
	EnemyOnPlatform(int x, int y, int leftEdge, int rightEdge, sf::Sprite * spriteLeft, sf::Sprite * spriteRight);
	int x;
	int y;
	int platformLeftEdge;
	int platformRightEdge;
	sf::Texture texture1;
	sf::Texture texture2;
	sf::Sprite* gottenSprite1;
	sf::Sprite* gottenSprite2;
	sf::Sprite* getSpriteR(void);
	sf::Sprite* getSpriteL(void);
};

