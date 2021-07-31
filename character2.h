#pragma once
#include <vector>
#include "platforms.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "platforms.h"
#include <windows.h>
#include "Misc.h"

class character2
{
public:
	//these are for keeping track of movement of platforms for crossover existance in endzone
	character2();
	std::string isMoving;
	int leftCrossoverAmount;
	int rightCrossovereAmount;
	int rightEndzoneLine;
	int leftEndzoneLine;
	int currentCharacterPlacement;

	Enemy* EnemyObject = new Enemy;

	int movesRightInLeftEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionY, float& positionX);
	
	
	int movesLeftInLeftEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	int movesRightInMidEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	int movesLeftInMidEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	int movesLeftInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	
	
	int movesRightInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	//int movesLeftInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	int	 isOnPlatform(sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int SCREENHEIGHT, int goingDownBypass, std::vector<platform>& vector, int SCREENWIDTH, float& positionY, float& positionX);



	//RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int SCEENHEIGHT, int& goingDown, std::vector<platform>& vector, int screenWidth, int& characterX, int& characterY, float& positionY, float& positionX)



};