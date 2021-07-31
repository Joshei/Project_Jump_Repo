#include <SFML/Window.hpp>
#include "Character.h"
#include <vector>
#include "Misc.h"
#include "enemyOnPlatform.h" 
#include <String>

int platformAnswer = 0;
#define VELOCITYX 4
#define VELOCITYY -20
// 400/2 - 76/2 - position x, cnetered
#define POSXCENTER 362  
#define GRAVITY 3
#define TIME 20

Character::Character(Enemy & eObject , Misc  &mObject, float x1, float y1, std::vector<Misc> &vector, sf::RenderWindow& inWindow)
{
	miscObject = &mObject;
	EnemyObject = &eObject;
	gPlatformsMoved = "none";


	x = x1;
	y = y1;
	
	rightEndzoneLine = (1200);
	leftEndzoneLine = (400 - 76/2);//1162
	//keeps track of every movement even in mid zone where positionx stays same (positionx used for local display)
	currentCharacterPlacement = 100;// 1162 - 75;//400 - (76 / 2);
	currentCharacterPlacementCopy = 0;
	wasOnPlatformA = 0;

}


int Character::IsCharacterInMidSection(float posX)
{
	if (posX == POSXCENTER)
	{
		return(1);
	}
	return(0);
}
//falling -  this one is not the one being used - 11/23/20
int Character::isOnPlatform(sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int SCEENHEIGHT, int&  goingDown, std::vector<platform>& vector, int screenWidth, int& characterX, int& characterY, float& positionY, float & positionX)
{
	
	
	 
	
	//finds a platform to land on
	for (std::vector<platform>::iterator it = vector.begin(); it != vector.end(); ++it)
	{
		
		
		

		
		if (((it->x >= ( -76)) && (it->x <= (screenWidth) )) &&
			((positionX + 76 >= it->x) && (positionX  <= (it->x+ 300  ))) &&
			
			((positionY + 76 <= (it->y + 20)) && (positionY + 76>= (it->y - 10   )))
			&& (goingDown = 1)  )
		{
			
			//this causes changes when a or s pressed
			marioSpriteL.setPosition(positionX, it->y - 76 );
			marioSpriteR.setPosition(positionX, it->y - 76);
			
			positionY = (it->y - 76);
			
			return(1);
		}
	}
	//not on bar
	
	return(0);
}



//change to jump right
int Character::JumpRightInEndZone(sf::Clock& clock3, sf::Time& Elapsed, Misc &miscObject,float & xDrift, int& line, const int SCREENWIDTH, const int SCREENHEIGHT, Character& character, std::vector<platform>& vector, float& positionX, float& positionY, float& velocityY, float& velocityX,
	float& gravity, int facingLeft, sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int& goingDown, int& characterOnBar)
{

	clock1.restart();
	

	velocityX = VELOCITYX + xDrift;

	int firstPositionX = positionX;
	int firstPositionY = positionY;
	//runs each time and updates postionx and positiony
	positionY += velocityY;
	positionX += velocityX;

	if (currentCharacterPlacement + VELOCITYX + xDrift >= leftCrossoverAmount && currentCharacterPlacement + VELOCITYX + xDrift < rightCrossovereAmount)
	{
		positionX = POSXCENTER;
	}

	velocityY += gravity;
	int secondPositionY = positionY;
	int secondPositionX = positionX;
	//if positive going down 
	int horizontalChange = secondPositionX - firstPositionX;

	//for dropping
	if (firstPositionY > secondPositionY)
	{
		
		goingDown = 0;
		
	}
	if (firstPositionY <= secondPositionY)
	{
		
		goingDown = 1;
	}

	
	if (goingDown)
	{
		float newPositionX = 0;
		newPositionX = positionX;
		if (positionX != 362)
		{
			newPositionX = positionX - xDrift;
		}
		//resets positionY is on platform
		platformAnswer = isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, positionY, newPositionX);

		if (platformAnswer == 1)
		{

			return(1);
		}

	}

	//bounce off ceiling
	if (positionY < 0)
	{
		velocityY = -velocityY;
		positionY = -positionY;

	}



	//positionX advanced above

	//check for movement that crossed left or right zone, or in leftzone entirely
	currentCharacterPlacementCopy = currentCharacterPlacement;
	currentCharacterPlacement = currentCharacterPlacement + VELOCITYX + xDrift;


	
	if (currentCharacterPlacement >= 1600 - 76)
	{
		currentCharacterPlacement = 1600 - 76;

		//josh, this!!!!!!!?
		positionX = SCREENWIDTH - 76;
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);

		
	}

	

	int flagReturn = 0;
	if (positionY > SCREENHEIGHT - 76)
	{
		flagReturn = 1;
		positionY = SCREENHEIGHT - 76;

	}

		
		//in left zone moves right and crossovers into mid
		if (currentCharacterPlacementCopy <= leftEndzoneLine && currentCharacterPlacement >= leftEndzoneLine)
		{
		
			

				
				int difference = leftEndzoneLine - currentCharacterPlacementCopy;
				leftCrossoverAmount = difference;
				rightCrossovereAmount = VELOCITYX + xDrift - leftCrossoverAmount;
				platform::advanceAllPlatforms(vector, -rightCrossovereAmount);
				EnemyObject->changePlatformEdgesForEnemy(window, -rightCrossovereAmount);

				
				positionX = POSXCENTER;
				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);
			
		
		}
		//in midzone moves right and crossevers into rightzone
		else if (currentCharacterPlacementCopy < rightEndzoneLine && currentCharacterPlacement >= rightEndzoneLine)

		{
			
			int difference = currentCharacterPlacement - rightEndzoneLine;
			leftCrossoverAmount = VELOCITYX - difference;
			rightCrossovereAmount = VELOCITYX - leftCrossoverAmount;

			platform::SearchVectorForPlatforms(vector, window, -leftCrossoverAmount, 0.0f, 0);
			platform::advanceAllPlatforms(vector, -leftCrossoverAmount);
			EnemyObject->changePlatformEdgesForEnemy(window, -leftCrossoverAmount);
			
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			
		

		}
		//in rigth zone moves right to offscreen
		else if (currentCharacterPlacement >= 1600 - 76)
		{
			currentCharacterPlacement = 1600 - 76;
			positionX = SCREENWIDTH - 76;
			
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			
		}
		//stays in left end zone
		else if (currentCharacterPlacement < leftEndzoneLine)
		{
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			
			
		}
		//stays in middle
		else if (currentCharacterPlacement < rightEndzoneLine)
		{
			positionX = POSXCENTER;
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			
			
			EnemyObject->changePlatformEdgesForEnemy(window, -5 - xDrift);
			platform::advanceAllPlatforms(vector, -5 - xDrift);
			
		}
		//stays in right zone
		else
		{
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			
		}

		if (flagReturn == 1)
		{

			return(1);

		}
	

	
	
	window.clear();
	
	window.draw(marioSpriteL);
	miscObject.moveEnemies(window, 5, 0, 1);

	
	//this is on platform
	character.EnemyObject->moveEnemies(window, 5 + xDrift, -10, 0);

	platform::drawAllPlatforms(vector, window);
	
	
	
	sf::Time elapsed1 = clock1.getElapsedTime();

	while ((elapsed1.asMilliseconds() + Elapsed.asMilliseconds()) <= ELAPSED)
	{
		elapsed1 = clock1.getElapsedTime();

	}


	window.display();
	
	
	return(3);


}


//off platform falls
int Character::whileFunction(int facingLeft, Character& character, sf::Clock& clock, sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, const int SCREENHEIGHT, int& goingDown, std::vector<platform>& vector, const int SCREENWIDTH, int no, int no1, int goingDown2, float& positionY, float& positionX)
{
	
	{
		
		positionY = positionY + 6;

		
		marioSpriteR.setPosition(positionX, positionY);
		marioSpriteL.setPosition(positionX, positionY);
		

		if (facingLeft == 1)
		{
			window.draw(marioSpriteR);
		}
		else
		{
			window.draw(marioSpriteL);
		}
		platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);

		window.display();

		int no1 = 0;
		int no2 = 0; 
		int answer3 = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, no1, no2, positionY, positionX);
		//lands on platform
		if (answer3)
		{
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			return(-1);
		}
		else if (positionY >= (SCREENHEIGHT - 76))
		{
			positionY = 600 - 76;
			
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			
			
			if (facingLeft == 1)
			{
				window.draw(marioSpriteR);
			}
			else
			{
				window.draw(marioSpriteL);
			}
			platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);

			window.display();
			return(-1);
		}

		if (facingLeft == 1)
		{
			window.draw(marioSpriteR);
		}
		else
		{
			window.draw(marioSpriteL);
		}
		
		platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);

		window.display();


	}
	return(1);
}




//here
/////////////////

Character::Character()
{
	leftEndzoneLine = 400 - 76 / 2;
	rightEndzoneLine = 1200;
}


//this is the one being used - 11/23/20
//fix bypass
int Character::isOnPlatform(sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int SCREENHEIGHT, int goingDownBypass, std::vector<platform>& vector, int SCREENWIDTH, float& positionY, float& positionX)
{
	//finds a platform to land on
	for (std::vector<platform>::iterator it = vector.begin(); it != vector.end(); ++it)
	{
		if (it->type != "platform")
		{
			continue;
		}
		


		

		if (((it->x >= (-76)) && (it->x <= (SCREENWIDTH))) &&
			((positionX + 76 >= it->x) && (positionX <= (it->x + 300)))
			
			
			
			&&
			
			((positionY + 76 <= (it->y + 40)) && (positionY + 76 >= (it->y - 20)))
			&& (goingDownBypass = 1))
		
		
		
		
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


int Character::movesRightInLeftEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{


	int goingDownBypass = 1;

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
	
	if (currentCharacterPlacement >= rightEndzoneLine)
	{
		//calls while to drop
		int val = movesRightInRightEndZone(SCREENHEIGHT, SCREENWIDTH, window, vector, marioSpriteL, marioSpriteR, positionX, positionY);
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
		int val = movesRightInMidEndZone(SCREENHEIGHT, SCREENWIDTH, window, vector, marioSpriteL, marioSpriteR, positionX, positionY);
		{
			if (val == -1)
			{
				return(-1);
			}
			return(1);
		}
	}




	currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
	


	//mid zone
	if (currentCharacterPlacement >= leftEndzoneLine)
	{
		
		positionX = POSXCENTER;

		int difference = currentCharacterPlacement - leftEndzoneLine;
		leftCrossoverAmount = VELOCITYX - difference;
		rightCrossovereAmount = VELOCITYX - leftCrossoverAmount;
		platform::advanceAllPlatforms(vector, -rightCrossovereAmount );
		EnemyObject->changePlatformEdgesForEnemy(window, -rightCrossovereAmount);

		isMoving = "right";
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
	}
	else
	{
		positionX = positionX + VELOCITYX;
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
	}
	



}



int Character::movesLeftInLeftEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{


	int goingDownBypass = 1;

	if (currentCharacterPlacement >= rightEndzoneLine)
	{
		//calls while to drop
		int val = movesLeftInRightEndZone(SCREENHEIGHT, SCREENWIDTH, window, vector, marioSpriteL, marioSpriteR, positionX, positionY);
		{
			if (val == -1)
			{
				return(-1);
			}
			return(1);
		}
	}


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


	if (currentCharacterPlacement >= leftEndzoneLine)
	{
		//calls while to drop
		int val = movesLeftInMidEndZone(SCREENHEIGHT, SCREENWIDTH, window, vector, marioSpriteL, marioSpriteR, positionX, positionY);
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


	if (currentCharacterPlacement < 0)
	{

		currentCharacterPlacement = 0;
		positionX = 0;


	}
	marioSpriteL.setPosition(positionX, positionY);
	marioSpriteR.setPosition(positionX, positionY);

	

}




int Character::movesRightInMidEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{


	int goingDownBypass = 1;

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

	currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
	
	//moves from mid zone to right zone, so move platform for that section and set character position for the rest of distance
	if (currentCharacterPlacement >= rightEndzoneLine)
	{
		
		
		int difference = currentCharacterPlacement - rightEndzoneLine;
		leftCrossoverAmount = VELOCITYX - difference;
		rightCrossovereAmount = VELOCITYX - leftCrossoverAmount;

		positionX = positionX + rightCrossovereAmount;

		platform::advanceAllPlatforms(vector, -leftCrossoverAmount);
		EnemyObject->changePlatformEdgesForEnemy(window, -leftCrossoverAmount);

		marioSpriteL.setPosition(positionX , positionY);
		marioSpriteR.setPosition(positionX , positionY);
		
	}
	//stays in mid zone;
	else
	{
		

		
		EnemyObject->changePlatformEdgesForEnemy(window, - 5);

		platform::advanceAllPlatforms(vector, -5);
		isMoving = "right";
		positionX = POSXCENTER;
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
		


	}






}



int Character::movesLeftInMidEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{



	int goingDownBypass = 1;

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



	currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;

	
	//enters left zone after moving left from mid zone
	if (currentCharacterPlacement <= leftEndzoneLine)
	{
		
		int difference = leftEndzoneLine - currentCharacterPlacement;
		rightCrossovereAmount = VELOCITYX - difference;
		leftCrossoverAmount = VELOCITYX - rightCrossovereAmount;
		
		positionX = positionX - leftCrossoverAmount;

		platform::advanceAllPlatforms(vector, rightCrossovereAmount);

		EnemyObject->changePlatformEdgesForEnemy(window, rightCrossovereAmount);

		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
		isMoving = "left";
	}
	//mid zone
	else
	{
		

		
		platform::advanceAllPlatforms(vector, 5);
		EnemyObject->changePlatformEdgesForEnemy(window ,5);
		isMoving = "left";
		positionX = POSXCENTER;
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
		
	}




}



int Character::movesRightInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{

	int goingDownBypass = 1;

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


	currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
	positionX = positionX + VELOCITYX;


	if (currentCharacterPlacement > 1600 - 76)
	{
		currentCharacterPlacement = 1600 - 76;
		positionX = SCREENWIDTH - 76;


	}
	marioSpriteL.setPosition(positionX, positionY);
	marioSpriteR.setPosition(positionX, positionY);


	
	return(1);
}


int Character::movesLeftInRightEndZone(const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow& window, std::vector<platform>& vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, float& positionX, float& positionY)
{


	int goingDownBypass = 1;
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


	currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
	
	//in midzone from moving left in right zone
	if (currentCharacterPlacement < rightEndzoneLine)
	{
		
		positionX = POSXCENTER;
		int difference = rightEndzoneLine - currentCharacterPlacement;
		leftCrossoverAmount = difference;
		rightCrossovereAmount = VELOCITYX - leftCrossoverAmount;

		
		EnemyObject->changePlatformEdgesForEnemy(window, leftCrossoverAmount);

		platform::advanceAllPlatforms(vector, leftCrossoverAmount);
		isMoving = "left";
		marioSpriteL.setPosition(POSXCENTER, positionY);
		marioSpriteR.setPosition(POSXCENTER, positionY);



	}
	//entirely in right zone
	else
	{
		
		positionX = positionX - VELOCITYX;
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
	}



}









//jump left!
int Character::JumpLeftInEndZone(sf::Clock& clock, sf::Time& Elapsed, Misc& miscObject, float xDrift, int& line, const int SCREENWIDTH, const int SCREENHEIGHT, Character& character, std::vector<platform>& vector, float& positionX, float& positionY, float& velocityY, float& velocityX,
	float& gravity, int facingLeft, sf::RenderWindow& window, sf::Sprite& marioSpriteR, sf::Sprite& marioSpriteL, int& goingDown, int& characterOnBar)
{

	clock1.restart();

	velocityX = -VELOCITYX - xDrift;

	int firstPositionX = positionX;
	int firstPositionY = positionY;
	
	//runs each time and updates postionx and positiony
	positionY += velocityY;
	positionX += velocityX ;
	
	velocityY += gravity;
	int secondPositionY = positionY;
	int secondPositionX = positionX;
	//if positive going down - not working yet
	int horizontalChange = secondPositionX - firstPositionX;

	//for dropping
	if (firstPositionY > secondPositionY)
	{
		//use this later
		goingDown = 0;
		
	}
	if (firstPositionY <= secondPositionY)
	{
		
		goingDown = 1;
	}

	

		//falling
		int answer = isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, positionY, positionX);
		//josh, is dropping!!!

		{
			if (answer == 1)
				

			if (goingDown)
			{
				 return(1);
			}

		}

		//bounce off ceiling
		if (positionY < 0)
		{
			velocityY = -velocityY;
			positionY = -positionY;
			
		}
	
		int flagReturn = 0;
		if (positionY > SCREENHEIGHT - 76)
		{
			flagReturn = 1;
			positionY = SCREENHEIGHT - 76;

		}
	//positionX advanced above

	//check for movement that crossed left or right zone, or in leftzone entirely
	currentCharacterPlacementCopy = currentCharacterPlacement;
	currentCharacterPlacement = currentCharacterPlacement - VELOCITYX - xDrift;

	//moves from mid zone to right zone, so move platform for that section and set character position for the rest of distance


	//jump left from right endzone to midzone

	if (currentCharacterPlacementCopy > rightEndzoneLine && currentCharacterPlacement <= rightEndzoneLine)
	{
		
		int difference = currentCharacterPlacementCopy - rightEndzoneLine;
		rightCrossovereAmount = difference;
		leftCrossoverAmount = VELOCITYX + xDrift - rightCrossovereAmount;

		platform::advanceAllPlatforms(vector, leftCrossoverAmount);

		EnemyObject->changePlatformEdgesForEnemy(window, leftCrossoverAmount);

		
		positionX = POSXCENTER;
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
		


	}
	//mid zone heading left and crossing over to leftenczone
	else if (currentCharacterPlacementCopy > leftEndzoneLine && currentCharacterPlacement <= leftEndzoneLine)
	{
		
		int difference = currentCharacterPlacementCopy - leftEndzoneLine;
		rightCrossovereAmount = difference;
		leftCrossoverAmount = VELOCITYX +xDrift - rightCrossovereAmount;
		
		platform::advanceAllPlatforms(vector, rightCrossovereAmount);
		EnemyObject->changePlatformEdgesForEnemy(window, rightCrossovereAmount);

		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
		

	}
	//in left endzone, crossed over to screen end
	else if (currentCharacterPlacement <= 0)
	{
		currentCharacterPlacement = 0;
		positionX = 0;
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
		
		
	}
	//stays in right zone
	else if (currentCharacterPlacement > rightEndzoneLine)
	{
		
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
		
	}
	//stays in midzone because of condition right abobe
	else if (currentCharacterPlacement > leftEndzoneLine)
	{
		
		positionX = POSXCENTER;
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
		//jpe changed from 4
		
		EnemyObject->changePlatformEdgesForEnemy(window, 5 + xDrift);
		platform::advanceAllPlatforms(vector, 5 + xDrift);
		
	}
	//stays in left zone
	else
	{
		
		marioSpriteL.setPosition(positionX, positionY);
		marioSpriteR.setPosition(positionX, positionY);
		//return(1);
	}

	if (flagReturn == 1)
	{
		
		return(1);
	
	}

	///////////////////


	window.clear();

	window.draw(marioSpriteR);
	
	miscObject.moveEnemies(window, 5, 0, 1);

	//is enemy on platform
	character.EnemyObject->moveEnemies(window, 5 + xDrift, -10, 0);
	platform::drawAllPlatforms(vector, window);

	sf::Time elapsed1 = clock1.getElapsedTime();
	
	while ((elapsed1.asMilliseconds() + Elapsed.asMilliseconds()) <= ELAPSED)
	{
		elapsed1 = clock1.getElapsedTime();
		
	}

	window.display();

	return(3);
}




