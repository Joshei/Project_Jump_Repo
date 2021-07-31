#include "character2.h"


#define VELOCITYX 10
#define VELOCITYY -20
// 400/2 - 76/2 - position x, cnetered
#define POSXCENTER 362  
#define GRAVITY 3
#define TIME 20

character2::character2()
{
	leftEndzoneLine = 400 - 76 / 2;
	rightEndzoneLine = 1200;
}



int character2::isOnPlatform(sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int SCREENHEIGHT, int goingDownBypass, std::vector<platform>& vector, int SCREENWIDTH, float& positionY, float& positionX)
{
	//finds a platform to land on
	for (std::vector<platform>::iterator it = vector.begin(); it != vector.end(); ++it)
	{
		if (it->type != "platform")
		{
			continue;
		}
		//if (((it->x >= -76) && (it->x <= screenWidth)) &&
		//	((characterX + 76 >= it->x) && (characterX <= (it->x + 150))) &&
		//	//(characterY >= (it->y - 96)) && (characterY <= (it->y - 76 + 11))
		//	//josh,this isn't exactly right!
		//	((characterY + 76 <= (it->y + 35)) && (characterY + 76 >= (it->y - 15)))
		//	&& (goingDown == 1))
		//{
		//currentLeftEdge = currentLeftEdge + VELOCITYX;

		if (((it->x >= (-76)) && (it->x <= (SCREENWIDTH))) &&
			((positionX + 76 >= it->x) && (positionX <= (it->x + 300))) &&
			//(characterY >= (it->y - 96)) && (characterY <= (it->y - 76 + 11))
			//josh,this isn't exactly right!
			((positionY + 76 <= (it->y + 35)) && (positionY + 76 >= (it->y - 15)))
			&& (goingDownBypass == 1))
		{

			//this causes changes when a or s pressed
			marioSpriteL.setPosition(positionX, it->y - 76);
			marioSpriteR.setPosition(positionX, it->y - 76);

			positionY = (it->y - 76);

			return(1);
		}
	}
	//not on bar

	return(0);


}

int character2::movesRightInLeftEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{
	

	int goingDownBypass = 1;

	//is not on ground
	if (positionY < SCREENHEIGHT - 76)
	{
		int answer = isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, positionY, positionX);
		//is dropping
		if (answer == 1)
		{
			return(-1);
		}



	}
	//not in this section
	if (currentCharacterPlacement >= rightEndzoneLine)
	{
		//calls while to drop
		int val = movesRightInRightEndZone(SCREENHEIGHT, SCREENWIDTH, window, vector, marioSpriteL, marioSpriteR, positionY, positionX);
		{
			if (val == -1)
			{
				return(-1);
			}
			return(1);
		}
	}



	if (currentCharacterPlacement >= leftEndzoneLine)
	{
		//calls while to drop
		int val = movesRightInMidEndZone(SCREENHEIGHT, SCREENWIDTH, window, vector, marioSpriteL, marioSpriteR, positionY, positionX);
		{
			if (val == -1)
			{
				return(-1);
			}
			return(1);
		}
	}




	currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
	positionX = positionX + VELOCITYX;


	//mid zone
	if (currentCharacterPlacement >= leftEndzoneLine)
	{



		int difference = currentCharacterPlacement - leftEndzoneLine;
		leftCrossoverAmount = VELOCITYX - difference;
		rightCrossovereAmount = VELOCITYX - leftCrossoverAmount;
		platform::SearchVectorForPlatforms(vector, window, -rightCrossovereAmount, 0.0f, 0);
		isMoving = "yes";
	}
	else
	{
		platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0.0f, 0);
		
	}
	marioSpriteL.setPosition(positionX, positionY);
	marioSpriteR.setPosition(positionX, positionY);

	

}



int character2::movesLeftInLeftEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{


	int goingDownBypass = 1;

	//is not on ground
	if (positionY < SCREENHEIGHT - 76)
	{
		int answer = isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, positionY, positionX);
		//is dropping
		if (answer == 1)
		{
			return(-1);
		}



	}

	//not in this section
	if (currentCharacterPlacement >= rightEndzoneLine)
	{
		//calls while to drop
		int val = movesLeftInRightEndZone(SCREENHEIGHT, SCREENWIDTH, window, vector, marioSpriteL, marioSpriteR, positionY, positionX);
		{
			if (val == -1)
			{
				return(-1);
			}
			return(1);
		}
	}



	if (currentCharacterPlacement >= leftEndzoneLine)
	{
		//calls while to drop
		int val = movesLeftInMidEndZone(SCREENHEIGHT, SCREENWIDTH, window, vector, marioSpriteL, marioSpriteR, positionY, positionX);
		{
			if (val == -1)
			{
				return(-1);
			}
			return(1);
		}
	}




	currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
	positionX = positionX - VELOCITYX;


	if (currentCharacterPlacement < -76)
	{

		currentCharacterPlacement = -76;
		positionX = -76;


	}
	marioSpriteL.setPosition(positionX, positionY);
	marioSpriteR.setPosition(positionX, positionY);

	//is not on ground
	if (positionY < SCREENHEIGHT - 76)
	{
		int answer = isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, positionY, positionX);
		//is dropping
		if (answer == 0)
		{
			return(-1);
		}



	}

}




int character2::movesRightInMidEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{


	int goingDownBypass = 1;

	//is not on ground
	if (positionY < SCREENHEIGHT - 76)
	{
		int answer = isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, positionY, positionX);
		//is dropping
		if (answer == 1)
		{
			return(-1);
		}



	}

	currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
	//positionX = positionX + VELOCITYX;


	//moves from mid zone to right zone, so move platform for that section and set character position for the rest of distance
	if (currentCharacterPlacement >= rightEndzoneLine)
	{

		int difference = currentCharacterPlacement - rightEndzoneLine;
		leftCrossoverAmount = VELOCITYX - difference;
		rightCrossovereAmount = VELOCITYX - leftCrossoverAmount;

		platform::SearchVectorForPlatforms(vector, window, -leftCrossoverAmount, 0.0f, 0);
		marioSpriteL.setPosition(positionX + rightCrossovereAmount, positionY);
		marioSpriteR.setPosition(positionX + rightCrossovereAmount, positionY);


	}
	//stays in mid zone
	else
	{
		platform::SearchVectorForPlatforms(vector, window, -5, 0.0f, 0);
		isMoving = "yes";
		marioSpriteL.setPosition(POSXCENTER, positionY);
		marioSpriteR.setPosition(POSXCENTER, positionY);
	
	
	}


	

	

}



int character2::movesLeftInMidEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{


	
	int goingDownBypass = 1;

	//is not on ground
	if (positionY < SCREENHEIGHT - 76)
	{
		int answer = isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, positionY, positionX);
		//is dropping
		if (answer == 1)
		{
			return(-1);
		}



	}


	currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
	//positionX = positionX - VELOCITYX;


	if (currentCharacterPlacement < leftEndzoneLine)
	{

		int difference = leftEndzoneLine - currentCharacterPlacement;
		rightCrossovereAmount = VELOCITYX - difference;
		leftCrossoverAmount = VELOCITYX - rightCrossovereAmount;
		platform::SearchVectorForPlatforms(vector, window, rightCrossovereAmount, 0.0f, 0);
		marioSpriteL.setPosition(leftCrossoverAmount, positionY);
		marioSpriteR.setPosition(leftCrossoverAmount, positionY);
	}
	else
	{
		platform::SearchVectorForPlatforms(vector, window, 5, 0.0f, 0);
		isMoving = "yes";
		marioSpriteL.setPosition(POSXCENTER, positionY);
		marioSpriteR.setPosition(POSXCENTER, positionY);
	}
	

	

}



int character2::movesRightInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{

	int goingDownBypass = 1;
	
	//is not on ground
	if (positionY < SCREENHEIGHT - 76)
	{
		int answer = isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, positionY, positionX);
		//is dropping
		if (answer == 1)
		{
			return(-1);
		}



	}


	currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
	positionX = positionX + VELOCITYX;


	if (currentCharacterPlacement >= SCREENWIDTH - 76)
	{
		currentCharacterPlacement = SCREENWIDTH - 76;
		positionX = SCREENWIDTH - 76;
		

	}
	marioSpriteL.setPosition(positionX, positionY);
	marioSpriteR.setPosition(positionX, positionY);

	

}


int character2::movesLeftInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{


	int goingDownBypass = 1;
	//is not on ground
	if (positionY < SCREENHEIGHT - 76)
	{
		int answer = isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, positionY, positionX);
		//is dropping
		if (answer == 1)
		{
			return(-1);
		}



	}


	currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
	//positionX = positionX - VELOCITYX;


	//in midzone
	if (currentCharacterPlacement < rightCrossovereAmount)
	{
		
		int difference = rightEndzoneLine - currentCharacterPlacement;
		rightCrossovereAmount = difference;
		leftCrossoverAmount = VELOCITYX - rightCrossovereAmount;

		platform::SearchVectorForPlatforms(vector, window, leftCrossoverAmount, 0.0f, 0);
		isMoving = "yes";
		marioSpriteL.setPosition(POSXCENTER, positionY);
		marioSpriteR.setPosition(POSXCENTER, positionY);



	}
	else
	{
		positionX = positionX - VELOCITYX;
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
	}

	

}
