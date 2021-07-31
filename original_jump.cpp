//OLD JUMP FUNCTION (for landing):


#include <SFML/Window.hpp>
#include "Character.h"
#include <vector>
#include "Misc.h"
#include "enemyOnPlatform.h"
#include <String>

#define VELOCITYX 10
#define VELOCITYY -20
	// 400/2 - 76/2 - position x, cnetered
#define POSXCENTER 362  
#define GRAVITY 3
#define TIME 20



// endzones need VELOCITYX changed to 5 to slow player down
//
//
//


Character::Character(Enemy & eObject, Misc & mObject, float x1, float y1, std::vector<Misc> & vector, sf::RenderWindow & inWindow)
{
	miscObject = &mObject;
	EnemyObject = &eObject;
	gPlatformsMoved = "none";


	x = x1;
	y = y1;

	rightEndzoneLine = (1200);
	leftEndzoneLine = (400 - 76 / 2);//1162
	//keeps track of every movement even in mid zone where positionx stays same (positionx used for local display)
	currentCharacterPlacement = 100;// 1162 - 75;//400 - (76 / 2);
}
//falling
int Character::isOnPlatform(sf::RenderWindow & window, sf::Sprite & marioSpriteR, sf::Sprite & marioSpriteL, int SCEENHEIGHT, int& goingDown, std::vector<platform> & vector, int screenWidth, int& characterX, int& characterY, float& positionY, float& positionX)
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

		if (((it->x >= (-76)) && (it->x <= (screenWidth))) &&
			((positionX + 76 >= it->x) && (positionX <= (it->x + 300))) &&
			//(characterY >= (it->y - 96)) && (characterY <= (it->y - 76 + 11))
			//josh,this isn't exactly right!
			((positionY + 76 <= (it->y + 35)) && (positionY + 76 >= (it->y - 15)))
			&& (goingDown == 1))
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

////////////

int Character::movesLeftInRightEndZoneToo(int facingLeft, const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow & window, int& goingDown, int& temp1, int& temp2, std::vector<platform> & vector, sf::Sprite & marioSpriteL, sf::Sprite & marioSpriteR, Character & character, int& isLeft, float& positionY, float& positionX)
{


	int goingDownBypass = 1;

	int answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, temp1, temp2, positionY, positionX);
	//on platform
	if (answer == 1)
	{




		currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
		//currentLeftEdge = currentLeftEdge - VELOCITYX;
		positionX = positionX - VELOCITYX;
		//if (currentCharacterPlacement < rightEndzoneLine)
		//{
		//	character.isMoving = "left";
		//	return(1);
		//}
	//is still on platform?
		answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, temp1, temp2, positionY, positionX);
		//was on, moved off
		if (answer == 0)
		{
			//drop - off platform
			return(-1);



		}
		//still on platform after move - left in right endzone
		else
		{
			//josh, this uncommented doesn't work ?
			//currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
			//currentLeftEdge = currentLeftEdge - VELOCITYX;
			//positionX = positionX - VELOCITYX;

			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);

			if (currentCharacterPlacement < rightEndzoneLine)
			{
				character.isMoving = "left";
				return(1);
			}

			//window.clear();
			//EnemyObject->moveEnemies(window, 10, -1, 0);
			//window.draw(marioSpriteR);
			//EnemyObject->moveEnemies(window, 10, -1, 0);
			//miscObject.moveEnemies(window, 10, 0, 1);



			//platform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);

			//window.display();
			return(1);
		}

	}
	//just walk left   not on platform starts here - right endzone
	else
	{


		//////////
		if (positionY >= SCREENHEIGHT - 76)
		{
			currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
			positionX = positionX - VELOCITYX;

			if (currentCharacterPlacement < rightEndzoneLine)
			{
				character.isMoving = "left";
				return(1);
			}

			//currentLeftEdge = currentLeftEdge - VELOCITYX;

			marioSpriteL.setPosition(positionX, (SCREENHEIGHT)-(76));
			marioSpriteR.setPosition(positionX, (SCREENHEIGHT)-(76));
			//plasaatform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);
			//window.clear();
			//window.draw(marioSpriteR);
			//platform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);
			//window.display();
			return(1);
		}
		else
		{
			//remove these in time -- //josh, look at this, there are four
			int no = 0;
			int goingDown2 = 0;
			//whileFunction(facingLeft, character, clock, window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, no, no, goingDown2, positionY, positionX);
			return(-1);
		}

	}

	return(1);
}

//movent in left endzone and mid section
int Character::movesLeftInEndZoneToo(int facingLeft, const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow & window, int& goingDown, int& temp1, int& temp2, std::vector<platform> & vector, sf::Sprite & marioSpriteL, sf::Sprite & marioSpriteR, Character & character, int& isLeft, float& positionY, float& positionX)
{
	//not in this section


	int goingDownBypass = 1;
	if (currentCharacterPlacement > rightEndzoneLine)
	{
		//checks for while function in main
		int val = movesLeftInRightEndZoneToo(facingLeft, SCREENHEIGHT, SCREENWIDTH, window, goingDown, temp1, temp2, vector, marioSpriteL, marioSpriteR, character, isLeft, positionY, positionX);
		if (val == -1)
		{
			return(-1);
		}

		return(1);
	}

	if (positionX <= 0)
	{
		positionX = 0;
		//return(1);
	}


	// calls this when not on platform last run with updated positionx, etc.
	// if playrt starts off platform cannot step onto a platform
	//int notNeeded1, notNeeded2 = 0;
	int answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, temp1, temp2, positionY, positionX);
	//on platform
	if (answer == 1)
	{
		//in mid section
		if (currentCharacterPlacement >= leftEndzoneLine)
		{
			//josh, bit of a hack, was 10 to small, : 652
			positionX = POSXCENTER;
			//platform::SearchVectorForPlatforms(vector, window, VELOCITYX, 0.0f, 0);
			currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;


			if (currentCharacterPlacement < leftEndzoneLine)
			{
				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);
				return(1);
			}

			//currentLeftEdge = currentLeftEdge - VELOCITYX;
			marioSpriteL.setPosition(POSXCENTER, positionY);
			marioSpriteR.setPosition(POSXCENTER, positionY);
			//platform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);

			//window.clear();
			//window.draw(marioSpriteR);
			isMoving = "left";
			//platform::SearchVectorForPlatforms(vector, window, VELOCITYX, 0.0f, 0);
			////window.display();
			return(1);


		}
		//in left endzone, on platform
		else
		{



			currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;


			//currentLeftEdge = currentLeftEdge - VELOCITYX;

			//left wall

			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			positionX = positionX - VELOCITYX;

			////window.clear();
			//window.draw(marioSpriteR);

			////character.isMoving == "none";
			//platform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);
			//window.display();

			//JOSH, ?
			return(1);


		}
		//is still on platform?
		answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, temp1, temp2, positionY, positionX);
		//was on, moved off
		if (answer == 0)
		{
			return(-1);


		}
		//still on platform after move
		else
		{	//mid section
			if (currentCharacterPlacement >= leftEndzoneLine)
			{
				currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;

				if (currentCharacterPlacement < leftEndzoneLine)
				{
					marioSpriteL.setPosition(positionX, positionY);
					marioSpriteR.setPosition(positionX, positionY);
					return(1);
				}

				marioSpriteL.setPosition(POSXCENTER, positionY);
				marioSpriteR.setPosition(POSXCENTER, positionY);
				//window.clear();

				window.draw(marioSpriteR);
				//isMoving = "yes";
				platform::SearchVectorForPlatforms(vector, window, VELOCITYX, 0.0f, 0);
				//window.display();
				return(1);
			}
			//leftendzone
			else
			{
				//josh
				currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
				positionX = positionX - VELOCITYX;


				//left wall 

				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);
				//window.clear();
				////window.draw(marioSpriteR);
				//haracter.isMoving == "none";
				/////platform::SearchVectorForPlatforms(vector, window, 0 , 0.0f, 0);

				////window.display();
				return(1);
			}
		}

	}//end of answer 1 - original, off platform
	else
	{

		// was never on platform
		//in left endzone 
		//move character twice to stay consistant with abpve.  Idea is the player is on the ground
		//so can't move on to a platform with double move

		if (positionY >= SCREENHEIGHT - 76)
		{
			if (currentCharacterPlacement < leftEndzoneLine)
			{

				if (positionX < (0))
				{

					marioSpriteL.setPosition(0, positionY);
					marioSpriteR.setPosition(0, positionY);
					positionX = 0;
					currentCharacterPlacement = 0;
					return(1);


				}
				//not less than zero and is in left endzone
				else
				{

					//left wall  


					currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
					positionX = positionX - VELOCITYX;
					//currentLeftEdge = currentLeftEdge - VELOCITYX;
					marioSpriteL.setPosition(positionX, positionY);
					marioSpriteR.setPosition(positionX, positionY);
					window.clear();
					window.draw(marioSpriteR);
					//character.isMoving == "none";
					platform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);
					//window.display();
					return(1);
				}

			}
			// moving left in mid zone
			else
			{

				//josh, !!!!

				//float rightSide = currentCharacterPlacement - leftEndzoneLine;
				//float currentCharacterPlacement2 = currentCharacterPlacement;
				currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
				//float remainder = currentCharacterPlacement - currentCharacterPlacement2;
				//if (currentCharacterPlacement2 >= leftEndzoneLine && currentCharacterPlacement < leftEndzoneLine)
				//{

				if (currentCharacterPlacement < leftEndzoneLine)
				{
					//here
					//int leftAmount = leftEndzoneLine - currentCharacterPlacement;
					//positionX = 362 - leftAmount;

					marioSpriteL.setPosition(positionX, positionY);
					marioSpriteR.setPosition(positionX, positionY);
					return(1);
					//platform::SearchVectorForPlatforms(vector, window, 1, 0.0f, 0);




				}
				else
				{
					//positionX = positionX - 2;
					marioSpriteL.setPosition(POSXCENTER, positionY);
					marioSpriteR.setPosition(POSXCENTER, positionY);
					//window.clear();

					isMoving = "left";
					//josh, is this okay?
					positionX = 362;
				}

				//character.EnemyObject->changePlatformEdgesForEnemy(window, 10);
				////platform::SearchVectorForPlatforms(vectorPlatforms, window, -10, 0.0f, 0);

				//character.EnemyObject->moveEnemies(window, 20, -10, 0);

				//window.clear();
				//window.draw(marioSpriteR);







				//platform::SearchVectorForPlatforms(vector, window, VELOCITYX, 0.0f, 0);
				//window.display();
				return(1);
			}
		}
		else
		{
			//not used //josh, look at this, there are four
			int no = 0;
			int goingDown2 = 0;
			/////
			//whileFunction(facingLeft, character, clock, window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, no, no, goingDown2, positionY, positionX);
			return(-1);
			/////
		}



	}


	return(1);
}



int Character::movesRightInRightEndZoneToo(int facingLeft, const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow & window, int& goingDown, int& characterLeft, int& characterY, std::vector<platform> & vector, sf::Sprite & marioSpriteL, sf::Sprite & marioSpriteR, Character & character, int& isLeft, float& positionY, float& positionX)
{
	int goingDownBypass = 1;
	//stops character at right wall
	if (currentCharacterPlacement >= ((SCREENWIDTH / 2) + SCREENWIDTH + (SCREENWIDTH / 2) - 38))
	{
		currentCharacterPlacement = ((SCREENWIDTH / 2) + SCREENWIDTH + (SCREENWIDTH / 2) - 38);
		return(1);
	}

	//not used
	sf::Vector2f  position = marioSpriteR.getPosition();
	int temp1 = position.x;
	int temp2 = position.y;
	positionX = temp1;
	positionY = temp2;


	// first there is a check if on platform, than there is a change in position
	// after position is changed there is an immediate check for off platform
	// if not off platfomr the function runs again and once again is on platform
	// changes position and checks for off platform.
	//int notNeeded1, notNeeded2 = 0;
	int answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, characterLeft, characterY, positionY, positionX);
	//on platform
	if (answer == 1)
	{

		//right endzone
		//josh,...
		platform::SearchVectorForPlatforms(vector, window, 0.0f, 0.0f, 0);
		currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
		positionX = positionX + VELOCITYX;
		//currentLeftEdge = currentLeftEdge + VELOCITYX;


		marioSpriteR.setPosition(positionX, positionY);
		marioSpriteL.setPosition(positionX, positionY);


		//is still on platform?
		answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, characterLeft, characterY, positionY, positionX);
		//was on, moved off
		if (answer == 0)
		{
			return(-1);




		}
		//still on platform after move - right endzone - mmoves right
		//josh, hack, two of these solve later
		else
		{
			//platform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);
			//currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
			//currentLeftEdge = currentLeftEdge - VELOCITYX;
			//positionX = positionX + VELOCITYX;
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			//window.clear();
			//window.draw(marioSpriteL);
			//platform::SearchVectorForPlatforms(vector, window, 0.0f, 0.0f, 0);
			//window.display();
			return(1);

		}

	}//not on platform

	if (positionY >= SCREENHEIGHT - 76)
	{
		//walk in right endzone, walks right
		////////////////////

		if ((currentCharacterPlacement >= rightEndzoneLine) && (positionY >= (SCREENHEIGHT)-(76)))
		{

			currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
			positionX = positionX + VELOCITYX;
			//currentLeftEdge = currentLeftEdge + VELOCITYX;
			//isLeft = 0;


			marioSpriteL.setPosition(positionX, (SCREENHEIGHT)-(76));
			marioSpriteR.setPosition(positionX, (SCREENHEIGHT)-(76));
			//window.clear();
			//window.draw(marioSpriteL);
			//platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
			//window.display();
			return(1);


		}
	}
	else //josh, look at this, there are four
	{
		return(-1);
		///////

		///////

	}


	return(1);
}
////////////
//enemies first,
//for player, don't clear and do draw and do display.  Keep platforms!
//in between both endzones or in left endzone
int Character::movesRightInEndZoneToo(int facingLeft, const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow & window, int& goingDown, int& characterLeft, int& characterY, std::vector<platform> & vector, sf::Sprite & marioSpriteL, sf::Sprite & marioSpriteR, Character & character, int& isLeft, float& positionY, float& positionX)
{
	//EnemyObject->moveEnemies(window, 2, -1, 0);

	int goingDownBypass = 1;
	//not in this section
	if (currentCharacterPlacement >= rightEndzoneLine)
	{
		//calls while to drop
		int val = movesRightInRightEndZoneToo(facingLeft, SCREENHEIGHT, SCREENWIDTH, window, goingDown, characterLeft, characterY, vector, marioSpriteL, marioSpriteR, character, isLeft, positionY, positionX);
		{
			if (val == -1)
			{
				return(-1);
			}
			return(1);
		}
	}
	//not used anymore
	sf::Vector2f  position = marioSpriteR.getPosition();
	int temp1 = position.x;
	int temp2 = position.y;


	//int notNeeded1, notNeeded2 = 0;
	int answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, characterLeft, characterY, positionY, positionX);
	//on platform
	if (answer == 1)
	{

		//moving right in left hand endzone - on platform
		if (currentCharacterPlacement < leftEndzoneLine)
		{
			//character.isMoving == "none";
			//move platforms
			//platform::SearchVectorForPlatforms(vector, window, 0.0f, 0.0f, 0);
			currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
			positionX = positionX + VELOCITYX;



			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);


			if (currentCharacterPlacement >= leftEndzoneLine)
			{
				marioSpriteL.setPosition(POSXCENTER, positionY);
				marioSpriteR.setPosition(POSXCENTER, positionY);


				return(1);
			}

			////window.clear();
			//window.draw(marioSpriteL);
			//platform::SearchVectorForPlatforms(vector, window, 0.0f, 0.0f, 0);
			//window.display();
			return(1);
			////currentLeftEdge = currentLeftEdge + VELOCITYX;
		}
		//moving right midzone - om platform
		else
		{

			//platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0.0f, 0);
			currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;

			if (currentCharacterPlacement >= rightEndzoneLine)
			{
				return(1);
			}

			marioSpriteL.setPosition(POSXCENTER, positionY);
			marioSpriteR.setPosition(POSXCENTER, positionY);
			//window.clear();
			isMoving = "right";
			//window.draw(marioSpriteL);
			//platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0.0f, 0);
			//window.display();
			return(1);


			//currentLeftEdge = currentLeftEdge + VELOCITYX;
		}



		//is still on platform?
		answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDownBypass, vector, SCREENWIDTH, characterLeft, characterY, positionY, positionX);
		//was on, moved off
		if (answer == 0)
		{
			//drop - off platform
			//remove these:
			int no = 0;
			int no1 = 0;
			int goingDown2 = 0;
			//calls fall
			return(-1);
			//whileFunction(facingLeft, character, clock, window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, no, no1, goingDown2, positionY, positionX);
		}

		//still on platform after move
		else
		{
			//in mid zone
			if (currentCharacterPlacement >= leftEndzoneLine)
			{

				//platform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);
				currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;

				if (currentCharacterPlacement >= rightEndzoneLine)
				{
					return(1);
				}

				isMoving = "right";
				//currentLeftEdge = currentLeftEdge - VELOCITYX;
				//positionX = positionX + VELOCITYX;
				marioSpriteL.setPosition(POSXCENTER, positionY);
				marioSpriteR.setPosition(POSXCENTER, positionY);
				//window.clear();

				//window.draw(marioSpriteL);
				//platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0.0f, 0);
				//window.display();
				return(1);

			}
			//in leftzone
			else
			{
				//character.isMoving == "none";
				currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
				positionX = positionX + VELOCITYX;


				if (currentCharacterPlacement >= rightEndzoneLine)
				{
					marioSpriteL.setPosition(POSXCENTER, positionY);
					marioSpriteR.setPosition(POSXCENTER, positionY);
					return(1);
				}
				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);
				//window.clear();
				//window.draw(marioSpriteL);
				//platform::SearchVectorForPlatforms(vector, window,0, 0.0f, 0);


				//window.display();
				return(1);
			}
		}

	}
	//not on platform
	else
	{
		//not on platform
		if (positionY >= SCREENHEIGHT - 76)
		{
			//not on platform
			//left endzone
			if (currentCharacterPlacement < leftEndzoneLine)
			{
				//platform::SearchVectorForPlatforms(vector, window, -2.0f, 0.0f, 0);
				currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
				positionX = positionX + VELOCITYX;

				if (currentCharacterPlacement >= leftEndzoneLine)
				{
					positionX = 362;
					marioSpriteL.setPosition(POSXCENTER, positionY);
					marioSpriteR.setPosition(POSXCENTER, positionY);
					return(1);
				}

				//currentLeftEdge = currentLeftEdge + VELOCITYX;
				//isLeft = 0;

				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);

				//if (currentCharacterPlacement >= leftEndzoneLine)
				//{
				//	positionX = 362;
				//	marioSpriteL.setPosition(positionX, positionY);
				//	marioSpriteR.setPosition(positionX, positionY);
				//
				//
				//}


				//window.clear();

				//runs on every press of 'S'

				//window.draw(marioSpriteL);

				//platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
				//character.isMoving = "none";


				//EnemyObject->moveEnemies(window, 2, 0, 0);
				//window.display();
				return(1);

			}
			//in middle - moving right -  not on platform
			else
			{


				currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;

				if (currentCharacterPlacement >= rightEndzoneLine)
				{
					return(1);
				}

				//currentLeftEdge = currentLeftEdge + VELOCITYX;
				marioSpriteL.setPosition(POSXCENTER, positionY);
				marioSpriteR.setPosition(POSXCENTER, positionY);
				//josh, look at this
				//window.clear();
				//window.draw(marioSpriteL);

				isMoving = "right";
				//platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0.0f, 0);
				//EnemyObject->changePlatformEdgesForEnemy(window, -5);

				//window.display();
				return(1);
			}

		}//is not on ground -- josh, look at this, there are four
		else
		{
			int no = 0;
			int goingDown2 = 0;
			//whileFunction(facingLeft, character, clock, window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, no, no, goingDown2, positionY, positionX);
			return(-1);
		}



	}

	return(1);
}
////////////

//



//

///////





//moves character up and down  and moves platforms too (left and right)
int Character::JumpInEndZone(int& line, const int SCREENWIDTH, const int SCREENHEIGHT, Character & character, std::vector<platform> & vector, float& positionX, float& positionY, float& velocityY, float& velocityX,
	float& gravity, int facingLeft, sf::RenderWindow & window, sf::Sprite & marioSpriteR, sf::Sprite & marioSpriteL, int& goingDown, int& characterOnBar)
{
	//josh, for now
	//goingDown = 1;
	//highestPlatform = 1;

	//do {

	clock1.restart();
	sf::Time elapsed1 = clock1.getElapsedTime();
	while (elapsed1.asMilliseconds() <= 40)
	{
		elapsed1 = clock1.getElapsedTime();

	}
	clock1.restart();


	//sets horizontal velocity to right or left
	if (facingLeft == 1)
	{

		//character.EnemyObject->changePlatformEdgesForEnemy(window, -11);
		velocityX = -VELOCITYX;
		currentCharacterPlacement = currentCharacterPlacement - VELOCITYX;
		if ((positionX > leftEndzoneLine) && (positionX < rightEndzoneLine))
		{
			//character.gPlatformsMoved == "left";
			//character.EnemyObject->changePlatformEdgesForEnemy(window, 20);
			//character.EnemyObject->moveEnemies(window, 10, -0, 0);
		}

	}
	else
	{
		//character.EnemyObject->changePlatformEdgesForEnemy(window, -11);

		velocityX = VELOCITYX;
		currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
		if ((positionX > leftEndzoneLine) && (positionX < rightEndzoneLine))
		{
			//character.gPlatformsMoved == "right";
			//character.EnemyObject->changePlatformEdgesForEnemy(window, -20);
			//character.EnemyObject->moveEnemies(window, -10, 0, 0);
		}
	}


	int firstPositionX = positionX;
	int firstPositionY = positionY;
	//runs each time and updates postionx and positiony
	positionY += velocityY;
	positionX += velocityX;
	velocityY += gravity;
	int secondPositionY = positionY;
	int secondPositionX = positionX;
	//if positive going down - not working yet
	int horizontalChange = secondPositionX - firstPositionX;

	//for dropping
	if (firstPositionY > secondPositionY)
	{
		// //use this later
		goingDown = 0;
		//highestPlatform = 0;
	}
	if (firstPositionY <= secondPositionY)
	{
		//highestPlatform = 1; 
		goingDown = 1;
	}

	//if landing with jump
	if (positionY > (600 - 76))
	{

		positionY = (600 - 76);


		//in right endzone
		if (currentCharacterPlacement >= rightEndzoneLine)
		{
			gPlatformsMoved = "none";
			marioSpriteL.setPosition(positionX, 600 - 76);
			marioSpriteR.setPosition(positionX, 600 - 76);
			//window.clear();
			//window.draw(marioSpriteR);
			//miscObject->moveEnemies(window, 10, 0, 0);
			//platform::SearchVectorForPlatforms(vector, window, 0, 0, 0);
			//character.EnemyObject->moveEnemies(window, 20, 0, 0);
			//window.display();
			//Sleep(40);
			return(1);
			//continue;

		}//in mid zone
		//this was positionX instead
		else if (currentCharacterPlacement >= leftEndzoneLine)
		{
			if (facingLeft == 1)
			{

				gPlatformsMoved = "left";
			}
			else
			{
				gPlatformsMoved = "right";
			}

			//marioSpriteL.setPosition((SCREENWIDTH / 2) - (76 / 2), 600 - 76);
			//marioSpriteR.setPosition((SCREENWIDTH / 2) - (76 / 2), 600 - 76);
			positionX = POSXCENTER;
			marioSpriteL.setPosition(positionX, 600 - 76);
			marioSpriteR.setPosition(positionX, 600 - 76);

			//platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0, 1);
			//window.clear();
			//window.draw(marioSpriteR);
			//miscObject->moveEnemies(window, 10, 0, 0);
			////sjcharacter.EnemyObject->changePlatformEdgesForEnemy(window, 10);
			//platform::SearchVectorForPlatforms(vector, window, -velocityX, 0, 1);
			//character.EnemyObject->moveEnemies(window, 20, 0, 0);
			//window.display();

			//if (facingLeft == 1)
			//{
			//
			//	character.gPlatformsMoved = "left";
			//}
			//else
			//{
				//character.gPlatformsMoved = "right";
			//}


			return(1);
			//continue;
		}
		else
		{	//left endzone
			gPlatformsMoved = "none";
			marioSpriteL.setPosition(positionX, 600 - 76);
			marioSpriteR.setPosition(positionX, 600 - 76);

			//window.clear();
			//window.draw(marioSpriteR);
			//miscObject->moveEnemies(window, 10, 0, 0);
			//platform::SearchVectorForPlatforms(vector, window, 0, 0, 0);
			//character.EnemyObject->moveEnemies(window, 20, 0, 0);
			//window.display();

			return(1);


		}

	}


	if (facingLeft == 1)
	{

		//not used anymore
		sf::Vector2f  position = marioSpriteL.getPosition();
		int temp1 = position.x;
		int temp2 = position.y;
		///////////////////////


		//is mario on a platforms
		//int answer1 = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, highestPlatform, vector, SCREENWIDTH, temp1, temp2, positionY, positionX);
		//josh, fix this hack
		int answer1 = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, temp1, temp2, positionY, positionX);

		//not on platform  - jump is left
		if (answer1 == 0)
		{

			//jumping left in right end zone
			if (currentCharacterPlacement >= ((SCREENWIDTH / 2) - (76 / 2) + 800))
			{
				gPlatformsMoved = "none";
				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);
				window.clear();
				window.draw(marioSpriteR);
				miscObject->moveEnemies(window, 10, 0, 0);
				//josh, a bit hackish
				//character.EnemyObject->changePlatformEdgesForEnemy(window, -11);

				platform::SearchVectorForPlatforms(vector, window, 0, 0, 0);
				character.EnemyObject->moveEnemies(window, 10, 0, 0);
				window.display();
				return(2);
				//continue;

			}
			//in midsection - jumping left
			else if (currentCharacterPlacement > ((SCREENWIDTH / 2) - (76 / 2)))
			{
				gPlatformsMoved = "left";
				positionX = POSXCENTER;
				marioSpriteL.setPosition(SCREENWIDTH / 2 - (76 / 2), positionY);
				marioSpriteR.setPosition(SCREENWIDTH / 2 - (76 / 2), positionY);

				window.clear();
				window.draw(marioSpriteR);
				character.EnemyObject->changePlatformEdgesForEnemy(window, 5);
				miscObject->moveEnemies(window, 10, 0, 0);
				platform::SearchVectorForPlatforms(vector, window, 5, 0, 1);
				character.EnemyObject->moveEnemies(window, 10, 0, 0);
				window.display();
				return(2);
				//continue;
			}

			//jumping left in left endzone
			else
			{
				//redundant
				//if (facingLeft)
				//{

					//AGAINST LEFT WALL IN AIR - drops down
				if (currentCharacterPlacement <= 0)
				{

					currentCharacterPlacement = 0;

					positionX = 0;

					//drops down from above
					//while (1)
					{
						clock.restart();
						sf::Time elapsed2 = clock.getElapsedTime();
						while (elapsed2.asMilliseconds() <= TIME)
						{
							elapsed2 = clock.getElapsedTime();

						}
						clock.restart();




						positionY = positionY + 2;
						positionX = (0);
						gPlatformsMoved = "none";
						marioSpriteR.setPosition(positionX, positionY);
						marioSpriteL.setPosition(positionX, positionY);
						window.clear();
						window.draw(marioSpriteR);
						miscObject->moveEnemies(window, 10, 0, 0);
						platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
						character.EnemyObject->moveEnemies(window, 10, 0, 0);
						window.display();
						if (positionY >= (SCREENHEIGHT - 76))
						{
							positionY = SCREENHEIGHT - 76;

							return(1);
						}


						//JOSH, DOESN'T APPLY YET, UNLESS TYPE OF VARIABLE JUMPING
						int answer3 = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, temp1, temp2, positionY, positionX);

						//lands on a platform?
						//otherwise if on platform caught above 
						if (answer3 == 0)
						{
							//gPlatformsMoved = "none";
							//marioSpriteR.setPosition(positionX, positionY);
							//marioSpriteL.setPosition(positionX, positionY);
							//window.clear();
							//window.draw(marioSpriteR);
							//miscObject->moveEnemies(window, 10, 0, 0);
							//platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
							//character.EnemyObject->moveEnemies(window, 10, 0, 0);
							//window.display();
							////josh, this?
							return(2);
							////continue;

						}


					}
				}


				//jumping left endzone, not against wall
				gPlatformsMoved = "none";
				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);

				window.clear();

				window.draw(marioSpriteR);
				miscObject->moveEnemies(window, 10, 0, 0);
				platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
				character.EnemyObject->moveEnemies(window, 10, 0, 0);
				window.display();
				return(2);
				//continue;
				//} 

			}



		}


		//on platform (all 3 sections)
		//left endzone
		else if (currentCharacterPlacement <= leftEndzoneLine)
		{

			gPlatformsMoved = "none";
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			//window.clear();
			//window.draw(marioSpriteL);
			//miscObject->moveEnemies(window, 10, 0, 0);
			//platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
			//character.EnemyObject->moveEnemies(window, 10, 0, 0);
			//window.display();
			return(-1);// continue;

		}
		//right endzone
		else if (currentCharacterPlacement >= (rightEndzoneLine))
		{
			///////////
			gPlatformsMoved = "none";
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			//window.clear();
			//window.draw(marioSpriteL);
			//miscObject->moveEnemies(window, 10, 0, 0);
			//platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
			//character.EnemyObject->moveEnemies(window, 10, 0, 0);
			//window.display();
			return(-1);
			//continue;
		}
		else
		{
			//midzone
			gPlatformsMoved = "left";
			marioSpriteL.setPosition(leftEndzoneLine, positionY);
			marioSpriteR.setPosition(leftEndzoneLine, positionY);
			positionX = POSXCENTER;
			//window.clear();
			//window.draw(marioSpriteL);
			//character.EnemyObject->changePlatformEdgesForEnemy(window, 5);
			//miscObject->moveEnemies(window, 10, 0, 0);
			//platform::SearchVectorForPlatforms(vector, window, 5, 0, 1);
			//character.EnemyObject->moveEnemies(window, 10, 0, 0);
			//window.display();
			//continue;
			return(-1);
		}




		window.display();

	}

	////////////////////////////jump in right hand direction////////////////////////
	else
	{




		//not needed any more
		int temp1 = 0;
		int	temp2 = 0;
		sf::Vector2f  position = marioSpriteL.getPosition();
		temp1 = position.x;
		temp2 = position.y;
		//////////////////


		//int answer1 = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, highestPlatform, vector, SCREENWIDTH, temp1, temp2, positionY, positionX);
		//josh, fix this hack
		int answer1 = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, 800, temp1, temp2, positionY, positionX);

		//not on platform - jumping right
		if (answer1 == 0)
		{
			//jumping right, in leftendzone
			if (currentCharacterPlacement <= leftEndzoneLine)
			{

				gPlatformsMoved = "none";
				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);
				window.clear();
				window.draw(marioSpriteL);

				miscObject->moveEnemies(window, 10, 0, 0);
				platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
				character.EnemyObject->moveEnemies(window, 10, 0, 0);
				window.display();
				return(2);
				//continue;

			}


			//jumping right in right endzone
			else if (currentCharacterPlacement >= (rightEndzoneLine))
			{


				//AGAINST RIGHT WALL IN AIR - falls straight down
				if (currentCharacterPlacement >= ((SCREENWIDTH / 2) + 800 + (SCREENWIDTH / 2) - 36))
				{
					currentCharacterPlacement = ((SCREENWIDTH / 2) + 800 + (SCREENWIDTH / 2) - 36);
					int temp1 = ((SCREENWIDTH / 2) + (800 + SCREENWIDTH / 2) - 76 - 36 - 100);


					//josh, possibly redundant
					//sf::Vector2f  position = marioSpriteR.getPosition();

					//not used anymore
					//sf::Vector2f vect;
					//vect.x = position.x;
					//vect.y = position.y;
					/////////////

					marioSpriteR.setPosition(positionX, positionY);
					marioSpriteL.setPosition(positionX, positionY);
					//fall down
					//while (1)
					{
						/*clock.restart();
						sf::Time elapsed3 = clock.getElapsedTime();
						while (elapsed3.asMilliseconds() <= TIME)
						{
							elapsed3 = clock.getElapsedTime();

						}
						clock.restart();

						*/
						positionY = positionY + 2;
						positionX = ((SCREENWIDTH)-76);

						gPlatformsMoved = "none";
						marioSpriteR.setPosition(positionX, positionY);
						marioSpriteL.setPosition(positionX, positionY);
						window.clear();
						window.draw(marioSpriteL);
						miscObject->moveEnemies(window, 10, 0, 0);
						platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
						character.EnemyObject->moveEnemies(window, 10, 0, 0);
						window.display();
						if (positionY >= (SCREENHEIGHT - 76))
						{
							positionY = SCREENHEIGHT - 76;

							return(1);
						}

						//(landing on a platform falling - right side)
						int answer3 = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, temp1, temp2, positionY, positionX);
						//if on platform catches it above.
						if (answer3 == 0)
						{

							//gPlatformsMoved = "none";
							//marioSpriteR.setPosition(positionX, positionY);
							//marioSpriteL.setPosition(positionX, positionY);
							//window.clear();
							//window.draw(marioSpriteL);
							//miscObject->moveEnemies(window, 10, 0, 0);
							//platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
							//character.EnemyObject->moveEnemies(window, 10, 0, 0);
							//window.display();
							return(2);
						}
						//not used - caught above
						else
						{

							int testline = 9;
						}



					}

				}
				//jump right in right endzone 
				else
				{
					gPlatformsMoved = "none";
					marioSpriteL.setPosition(positionX, positionY);
					marioSpriteR.setPosition(positionX, positionY);
					window.clear();
					window.draw(marioSpriteL);
					miscObject->moveEnemies(window, 10, 0, 0);
					platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
					character.EnemyObject->moveEnemies(window, 10, 0, 0);
					window.display();
					return(2);
					//continue;
				}
			}
			//in middle section, right jump
			else
			{

				marioSpriteL.setPosition(POSXCENTER, positionY);
				marioSpriteR.setPosition(POSXCENTER, positionY);
				positionX = POSXCENTER;
				gPlatformsMoved = "right";
				window.clear();
				window.draw(marioSpriteL);
				character.EnemyObject->changePlatformEdgesForEnemy(window, -5);
				miscObject->moveEnemies(window, 10, 0, 0);
				platform::SearchVectorForPlatforms(vector, window, -5, 0, 1);
				character.EnemyObject->moveEnemies(window, 10, 0, 0);
				window.display();
				return(2);


			}


		}

		//lands on platform - all three sections
		//left endzone
		else if (currentCharacterPlacement <= leftEndzoneLine)
		{

			gPlatformsMoved = "none";
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			//window.clear();
			//window.draw(marioSpriteL);
			//miscObject->moveEnemies(window, 10, 0, 0);
			//platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
			//character.EnemyObject->moveEnemies(window, 10, 0, 0);
			//window.display();
			return(-1);// continue;

		}
		//right endzone
		else if (currentCharacterPlacement >= (rightEndzoneLine))
		{
			///////////
			gPlatformsMoved = "none";
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			//window.clear();
			//window.draw(marioSpriteL);
			//miscObject->moveEnemies(window, 10, 0, 0);
			//platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
			//character.EnemyObject->moveEnemies(window, 10, 0, 0);
			//window.display();
			return(-1);
			//continue;
		}
		//middle zonr
		else
		{
			gPlatformsMoved = "right";
			marioSpriteL.setPosition(POSXCENTER, positionY);
			marioSpriteR.setPosition(POSXCENTER, positionY);
			positionX = POSXCENTER;
			//window.clear();
			//window.draw(marioSpriteL);
			//character.EnemyObject->changePlatformEdgesForEnemy(window, -5);
			//miscObject->moveEnemies(window, 10, 0, 0);
			//platform::SearchVectorForPlatforms(vector, window, -5, 0, 1);
			//character.EnemyObject->moveEnemies(window, 10, 0, 0);
			//window.display();
			//continue;
			return(-1);
		}

		window.display();


	}

	//} while (1);
	return(1);

}

//off platform falls
int Character::whileFunction(int facingLeft, Character & character, sf::Clock & clock, sf::RenderWindow & window, sf::Sprite & marioSpriteR, sf::Sprite & marioSpriteL, const int SCREENHEIGHT, int& goingDown, std::vector<platform> & vector, const int SCREENWIDTH, int no, int no1, int goingDown2, float& positionY, float& positionX)
{
	//while (1)
	{
		/*clock.restart();
		sf::Time elapsed3 = clock.getElapsedTime();
		while (elapsed3.asMilliseconds() <= TIME)
		{
			elapsed3 = clock.getElapsedTime();

		}
		clock.restart();*/

		//temp2 = temp2 + 2.0f;
		positionY = positionY + 6;

		//window.clear();
		//platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
		marioSpriteR.setPosition(positionX, positionY);
		marioSpriteL.setPosition(positionX, positionY);
		//window.clear();


		//window.draw(marioSpriteL);

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
			//int yValue = (temp2);
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			//window.clear();
			//marioSpriteL.setPosition(positionX, positionY);
			//marioSpriteR.setPosition(positionX, positionY);

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

		//window.clear();

		////

		if (facingLeft == 1)
		{
			window.draw(marioSpriteR);
		}
		else
		{
			window.draw(marioSpriteL);
		}
		////
		platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);


		//window.draw(marioSpriteR);



		window.display();


	}//returns to walk left, etc.
	return(1);
}

////////right in left endzone and middle for enemies
//in between both endzones or in left endzone
//is before player blit so keep clear, draw, and not display
//therefore in similar function for player don't clear and do draw and do display.
//don't display platforms in this function
int Character::movesEnemyRightInLeftAndMidZone(int facingLeft, const int SCREENHEIGHT, const int SCREENWIDTH, sf::RenderWindow & window, int& goingDown, int& characterLeft, int& characterY, std::vector<platform> & vector, sf::Sprite & marioSpriteL, sf::Sprite & marioSpriteR, Character & character, int& isLeft, float& positionY, float& positionX)
{
	goingDown = 1;
	//not in this section
	if (currentCharacterPlacement >= rightEndzoneLine)
	{
		//calls while to drop
		int val = movesRightInRightEndZoneToo(facingLeft, SCREENHEIGHT, SCREENWIDTH, window, goingDown, characterLeft, characterY, vector, marioSpriteL, marioSpriteR, character, isLeft, positionY, positionX);
		{
			if (val == -1)
			{
				return(-1);
			}
			return(1);
		}
	}
	//not used anymore
	sf::Vector2f  position = marioSpriteR.getPosition();
	int temp1 = position.x;
	int temp2 = position.y;


	//int notNeeded1, notNeeded2 = 0;
	int answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, characterLeft, characterY, positionY, positionX);
	//on platform
	if (answer == 1)
	{

		//moving right in left hand endzone - on platform
		if (currentCharacterPlacement <= leftEndzoneLine)
		{
			//move platforms
			//platform::SearchVectorForPlatforms(vector, window, 0.0f, 0.0f, 0);
			currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
			positionX = positionX + VELOCITYX;
			marioSpriteL.setPosition(positionX, positionY);
			marioSpriteR.setPosition(positionX, positionY);
			window.clear();
			window.draw(marioSpriteL);
			////platform::SearchVectorForPlatforms(vector, window, 0.0f, 0.0f, 0);
			////window.display();
			//return(1);
			//currentLeftEdge = currentLeftEdge + VELOCITYX;
		}
		//moving right midzone - om platform
		else
		{
			//platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0.0f, 0);
			currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
			marioSpriteL.setPosition(POSXCENTER, positionY);
			marioSpriteR.setPosition(POSXCENTER, positionY);
			window.clear();

			window.draw(marioSpriteL);
			////platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0.0f, 0);
			////window.display();
			//return(1);


			//currentLeftEdge = currentLeftEdge + VELOCITYX;
		}



		//is still on platform?
		answer = character.isOnPlatform(window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, characterLeft, characterY, positionY, positionX);
		//was on, moved off
		if (answer == 0)
		{
			//drop - off platform
			//remove these:
			int no = 0;
			int no1 = 0;
			int goingDown2 = 0;
			//calls fall
			return(-1);
			//whileFunction(facingLeft, character, clock, window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, no, no1, goingDown2, positionY, positionX);
		}

		//still on platform after move
		else
		{
			//in mid zone
			if (currentCharacterPlacement >= leftEndzoneLine)
			{
				//platform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);
				currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
				//currentLeftEdge = currentLeftEdge - VELOCITYX;
				//positionX = positionX + VELOCITYX;
				marioSpriteL.setPosition(POSXCENTER, positionY);
				marioSpriteR.setPosition(POSXCENTER, positionY);
				window.clear();

				window.draw(marioSpriteL);
				////platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0.0f, 0);
				////window.display();
				return(1);

			}
			//in leftzone
			else
			{

				currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
				positionX = positionX + VELOCITYX;
				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);
				window.clear();
				window.draw(marioSpriteL);
				////platform::SearchVectorForPlatforms(vector, window, 0, 0.0f, 0);


				////window.display();
				return(1);
			}
		}

	}
	//not on platform
	else
	{
		//not on platform
		if (positionY >= SCREENHEIGHT - 76)
		{
			//not on platform
			//left endzone
			if (currentCharacterPlacement <= leftEndzoneLine)
			{
				//platform::SearchVectorForPlatforms(vector, window, -2.0f, 0.0f, 0);
				currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
				positionX = positionX + VELOCITYX;
				//currentLeftEdge = currentLeftEdge + VELOCITYX;
				//isLeft = 0;

				//josh, enemy displays on screen okay here with delete of platform below - getting ready for new function without platforms
				marioSpriteL.setPosition(positionX, positionY);
				marioSpriteR.setPosition(positionX, positionY);
				window.clear();

				window.draw(marioSpriteL);
				////platform::SearchVectorForPlatforms(vector, window, 0, 0, 1);
				//window.display();
				return(1);

			}
			//in middle - moving right -  not on platform
			else
			{


				currentCharacterPlacement = currentCharacterPlacement + VELOCITYX;
				//currentLeftEdge = currentLeftEdge + VELOCITYX;
				marioSpriteL.setPosition(POSXCENTER, positionY);
				marioSpriteR.setPosition(POSXCENTER, positionY);
				window.clear();
				window.draw(marioSpriteL);
				////platform::SearchVectorForPlatforms(vector, window, -VELOCITYX, 0.0f, 0);

				////window.display();
				return(1);
			}

		}//is not on ground
		else
		{
			int no = 0;
			int goingDown2 = 0;
			//whileFunction(facingLeft, character, clock, window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vector, SCREENWIDTH, no, no, goingDown2, positionY, positionX);
			return(-1);
		}



	}

	return(1);
}


////////