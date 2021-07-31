#pragma once
#include <vector>
#include "platforms.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "platforms.h"
#include <windows.h>
#include "Misc.h"
//class Misc;

class Character
{
public:


	/////
	Character();
	int movesRightInLeftEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionY, float& positionX);


	int movesLeftInLeftEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	int movesRightInMidEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	int movesLeftInMidEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	int movesLeftInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);


	int movesRightInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	//int movesLeftInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY);
	int	 isOnPlatform(sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int SCREENHEIGHT, int goingDownBypass, std::vector<platform>& vector, int SCREENWIDTH, float& positionY, float& positionX);

	int leftCrossoverAmount;
	int rightCrossovereAmount;


	/////

	const int ELAPSED = 20;
	int gBouncedofftop = 0;
	std::string isMoving;
	std::string gPlatformsMoved;
	Enemy* EnemyObject = new Enemy;
	// (std::vector<Enemy>& vector, sf::RenderWindow& inWindow);
	Misc* miscObject = new Misc;

	//Misc miscObject(vector, inWindow);
	float x;
	float y;
	sf::Clock clock;
	sf::Clock clock1;
	int currentLeftEdge = 0;
	platform  platform1;
	// full scroll is zero to 800 * 5
	int rightEndzoneLine;
	int leftEndzoneLine;
	int currentCharacterPlacement;
	int currentCharacterPlacementCopy;
	int highestPlatform = 0;
	int wasOnPlatformA;
	int jumpagain;
	//Misc  miscObject;
	//Character(int, int);

	Character(Enemy& eObject, Misc & mObject, float x1, float x2, std::vector<Misc>& vector, sf::RenderWindow& inWindow);
	int whileFunction(int facingLeft, Character& character, sf::Clock& clock, sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, const int SCREENHEIGHT, int& goingDown, std::vector<platform>& vector, const int SCREENWIDTH, int no, int no1, int goingDown2, float& positionY, float& positionX);

	int isOnPlatform(sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int SCEENHEIGHT, int &  goingDown, std::vector<platform>& vector, int screenWidth, int& characterX, int& characterY, float& positionY, float & positionX);
	
	//int movesLeft(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, int& goingDown, int& characterLeft, int& characterY,std::vector<platform> &vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, Character& character, int& isLeft, float &positionY, float &positionX);
	//int movesRight(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, int& goingDown, int& characterLeft, int& characterY, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, Character& character, int& isLeft, float& positionY, float & positionX);
	
	//int movesRightInEndZoneToo(int facingLeft, const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, int& goingDown, int& characterLeft, int& characterY, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, Character& character, int& isLeft, float& positionY, float &positionX);
	
	//int movesLeftInEndZoneToo(int facingLeft, const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, int& goingDown, int& temp1, int& temp2, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, Character& character, int& isLeft, float& positionY, float& positonX);
	
	
	int JumpRightInEndZone(sf::Clock& clock3, sf::Time& Elapsed, Misc & miscObject, float & xDrift, int& line, const int SCREENWIDTH, const int SCREENHEIGHT, Character& character, std::vector<platform>& vector, float& positionX, float& positionY, float& velocityY, float& velocityX,
		float & gravity, int isLeft, sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int& goingDown, int& characterOnBar);
	
	int JumpLeftInEndZone(sf::Clock& clock3, sf::Time& Elpased , Misc & misceObject, float xDrift,int& line, const int SCREENWIDTH, const int SCREENHEIGHT, Character& character, std::vector<platform>& vector, float& positionX, float& positionY, float& velocityY, float& velocityX,
		float& gravity, int isLeft, sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int& goingDown, int& characterOnBar);


	//int movesRightInRightEndZoneToo(int facingLeft, const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, int& goingDown, int& characterLeft, int& characterY, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, Character& character, int& isLeft, float& positionY, float& positionX);
	//int movesLeftInRightEndZoneToo(int facingLeft,const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, int& goingDown, int& temp1, int& temp2, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, Character& character, int& isLeft, float& positionY, float& positionX);
	
	//int movesEnemyRightInLeftAndMidZone(int facingLeft, const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, int& goingDown, int& characterLeft, int& characterY, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, Character& character, int& isLeft, float& positionY, float& positionX);

	


};

