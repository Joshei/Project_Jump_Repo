#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include "platforms.h"
#include "Character.h"
#include "Parser.h"
#include <string>
#include "Enemy.h"
#include "Misc.h"
#include "EnemyOnPlatform.h"
#include <iostream>

//problems with project

// mario sprites are reversed
// some functions should be renamed
// some functions have unused arguments in signature



//some repeated in character.cpp
#define VELOCITYX 10/2
#define VELOCITYY -20
#define POSXCENTER 362
#define GRAVITY 3
#define TIME 80

int inJump = 0;
bool aOrS = false;

bool wentStaightThru = true;

int const SCREENWIDTH = 800;
int const SCREENHEIGHT = 600;



bool gKeypressDisabled = false;
bool gCallDrop = false;



Parser parser;

sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");

std::vector<platform> vectorPlatforms;
std::vector<Misc> vecEnemys;
std::vector<EnemyOnPlatform> vecPlatformEnemys;



int checkForCollisions(std::vector<platform> vector, int positionX, int positionY);

void SearchVectorForPlatforms(sf::RenderWindow & inWindow, float deltaX, float deltaY, int isLeft);


int virtualJump(Character & character, std::vector<platform>& vector, float& platPositionX, float& platPositionY, float& platVelocityY, float& platVelocityX,
	float& platGravity, int& isLeft, sf::RenderWindow& window, sf::Sprite & marioSpriteR, sf::Sprite &marioSpriteL, int& GoingDown, int& characterOnBar
	);

int movesLeft(sf::RenderWindow& window, int& goingDown, int& characterLeft, int& characterRight, int SCREENWIDTH, std::vector<platform> vector, sf::Sprite& marioSpriteL, sf::Sprite& marioSpriteR, Character& character, int& isLeft, int& characterOnBar, float positionY);
//void resetJumpingVariables(/*float &velocityX,*/ float& velocityY, float gravity = 0.5f, float& positionX = SCREENWIDTH / 2 - 76 / 2, float& positionY = 600 - 76, int isLeft = 1);

int moveEnemies(sf::RenderWindow& inWindow, float changeX, float changeY, int isLeft1);


sf::Sprite* gottenSprite;
int characterOnBar = 0;
int answer = 0;
int answer1 = 0;
int goingDown = 0;
int gPlatformX = 0;
int gPlatformY = 0;

int line = 400 - (76 / 2);


sf::Color gColor(0, 0, 0, 255);

int main()
{
	

	sf::Clock clock;

	const int ELAPSED = 20;


	sf::Clock clock3;

	sf::Time gElapsed3;


	
	

	//sstraightthru
	sf::Clock clock2;
	
	sf::Time gElapsed2;
	sf::Time elapsed4;
	

	//a or s
	sf::Clock clock4;
	//sf::Time gElapsed4;

	
	sf::Clock clock5;
	
	
	sf::Sprite marioSpriteL;
	sf::Sprite marioSpriteR;
	sf::Sprite structure1Sprite;
	sf::Sprite structure2Sprite;
	sf::Sprite structure3Sprite;
	sf::Sprite structure4Sprite;



	sf::Sprite structure5Sprite;
	sf::Sprite structure6Sprite;



	sf::Sprite enemy2;
	
	sf::Sprite platformSprite1a;
	sf::Sprite platformSprite2;



	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;
	sf::Texture texture5;
	

	
	
	float positionX = 100;
	float positionY = (SCREENHEIGHT - 76);
	float x = positionX;
	float y = positionY;
	float velocityY = VELOCITYY;
	float velocityX = VELOCITYX;
	float gravity = GRAVITY;
	bool keyboardDisabled = 0;
	bool parserDisabled = 0;
	bool enemiesAreFalling = false;
	int gParseFlag = 1;
	
	//sets x and y of enemy on ground walking by is in a vector that is used below in the misc file
	Misc enemy_1(vecEnemys, window, 0, &enemy2 );
	Misc enemy_2(vecEnemys, window, 1600 * .33, &enemy2);
	Misc enemy_3(vecEnemys, window, 1600 * .66, &enemy2);

	
	vecEnemys.push_back(enemy_1);
	vecEnemys.push_back(enemy_2);
	vecEnemys.push_back(enemy_3);

	
	if (!texture1.loadFromFile("mario_L.png"))
	{
		// error...
	}
	if (!texture2.loadFromFile("mario_R.png"))
	{
		// error...
	}
	if (!texture3.loadFromFile("structure2.png"))
	{
		// error...
	}
	if (!texture4.loadFromFile("enemyL.png"))
	{
		// error...
	}
	if (!texture5.loadFromFile("enemyR.png"))
	{
		// error...
	}
	
	
	
    marioSpriteL.setTexture(texture2);
	marioSpriteR.setTexture(texture1);
	
	
	structure1Sprite.setTexture(texture3);
	structure1Sprite.setPosition(200,300);
	
	//
	structure2Sprite.setTexture(texture3);
	structure2Sprite.setPosition(600, 450);
	//
	structure3Sprite.setTexture(texture3);
	structure3Sprite.setPosition(800, 300);


	structure4Sprite.setTexture(texture3);
	structure4Sprite.setPosition(1300, 300);

	structure5Sprite.setTexture(texture3);
	structure5Sprite.setPosition(900, 400);
	structure6Sprite.setTexture(texture3);
	structure6Sprite.setPosition(0, 400);



	//for line of three enemies
	enemy2.setTexture(texture5);
	enemy2.setPosition(600, 450 - 76);
	
	//coordinates for start x and y of enemy on platform
	int x1 = 600;
	int y1 = 450 - 76;


	//left and right edges of platform
	int lPlatform = 600;
	int rPlatform = 900;
	//EnemyOnPlatform enemyP1(300, 450, 600, 750, &platformSprite1, &platformSprite1);
	
	//to change platform legth
	//change set position (above)?
	//change platform lPlatform and rPlatform in above call
	//change searcvector "on the screen check"
	//change onplatform, length of platform

	//inside here for textures of enemy on platform sets initial x and y
	EnemyOnPlatform enemyP1(x1, y1, lPlatform, rPlatform, &platformSprite1a, &platformSprite2);
	vecPlatformEnemys.push_back(enemyP1);


	
	Enemy enemyObject(vecPlatformEnemys);
	
	Misc miscObject(vecEnemys, window, 100, &enemy2);

	Character character(enemyObject, miscObject, -1, -1, vecEnemys, window);
	

	
	platform platformObject(150,50,"platform", &structure1Sprite);
	platform platformObject1(300, 50,"platform", &structure2Sprite);
	platform platformObject2(150, 50, "platform", &structure3Sprite);
	platform platformObject3(150, 50, "platform", &structure4Sprite);
	platform platformObject4(150, 50, "platform", &structure5Sprite);
	platform platformObject5(150, 50, "platform", &structure6Sprite);


	

	vectorPlatforms.push_back(platformObject);
	vectorPlatforms.push_back(platformObject1);  
	//vectorPlatforms.push_back(platformObject2);  
	vectorPlatforms.push_back(platformObject3);
	//vectorPlatforms.push_back(platformObject4);
	//vectorPlatforms.push_back(platformObject5);
	

	

	
	
		//josh
	int isLeft = 0;

	marioSpriteR.setPosition(100, (SCREENHEIGHT - 76));
	marioSpriteL.setPosition(100, (SCREENHEIGHT - 76));
	
	window.setKeyRepeatEnabled(false);
	
	
	
	while (window.isOpen())
	{
		
		clock2.restart();
		
		wentStaightThru = true;
		
		
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			

			
			if (event.type == sf::Event::Closed)
				window.close();

			
			
			
			
			
			
			else if (event.type == sf::Event::KeyPressed) {
				



				
			}
		}

		


		
		
		
		//not needed
		int no = 0;
		int goingDown2 = 0;

		if (gCallDrop == true)
		{
			goingDown = 1;
			gKeypressDisabled = true;
			
			int isntFinished = character.whileFunction(isLeft, character, clock, window, marioSpriteR, marioSpriteL, SCREENHEIGHT, goingDown, vectorPlatforms, SCREENWIDTH, no, no, goingDown2, positionY, positionX);
			//is done
			if (isntFinished == -1)
			{
				gKeypressDisabled = false;
				gCallDrop = false;
			}
		}
		
		////remove these:
		int characterLeft = 0;
		int characterRight = 0;
		///////

		int counter = 0;
		int counter1 = 0;
		int flag = 1;
		int counter2 = 0;

		
		float xDriftFactor = 0;

		
		//main jump starts here

		inJump = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			wentStaightThru = false;
			

			inJump = 1;
			
			gravity = GRAVITY;
			velocityY = VELOCITYY;
			velocityX = VELOCITYX;

			while (flag == 1)
			{
				clock5.restart();
				//left
				xDriftFactor = 0;
				bool check = (sf::Keyboard::isKeyPressed(sf::Keyboard::A));

				if (check == true)
				{
					xDriftFactor =  4;
				}
				
				check = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) );

				if (check == true)
				{
					xDriftFactor =  4;
				}
				
				bool pressed = (sf::Keyboard::isKeyPressed(sf::Keyboard::J));
					
				
				if (pressed)
					{
						
						velocityY =  velocityY - 2.5;

					}
				

				//returned : 2 : was continue
				//returned : -1 was break
				//returned : 1 done with jump

				//one update - jumps once and than tries all other update function and uses keyboard to move slightly left or right
				//Variable jump is the longer the button is held in the less gravity is
				
				//jumping left and right
				int retValue = 0;

				if (isLeft == 1)
				{
					sf::Time gElapsed5 = clock5.getElapsedTime();
					//clock3.restart();
					retValue = character.JumpLeftInEndZone(clock3, gElapsed5, miscObject, xDriftFactor, line, SCREENWIDTH, SCREENHEIGHT, character, vectorPlatforms, positionX, positionY, velocityY, velocityX,
						gravity, isLeft, window, marioSpriteR, marioSpriteL, goingDown, characterOnBar);
					xDriftFactor = 0;
				}
				else
				{
					sf::Time gElapsed5 = clock5.getElapsedTime();

					retValue = character.JumpRightInEndZone(clock3, gElapsed5, miscObject, xDriftFactor, line, SCREENWIDTH, SCREENHEIGHT, character, vectorPlatforms, positionX, positionY, velocityY, velocityX,
						gravity, isLeft, window, marioSpriteR, marioSpriteL, goingDown, characterOnBar);

					xDriftFactor = 0;

				}
				
				
				if (retValue == -1 || retValue == 1)
				{
					//set to make display expediated
					//JustleftJump = true;
					wentStaightThru = false;
					aOrS = false;

					velocityX = VELOCITYX;
					velocityY = VELOCITYY;
					gravity = GRAVITY;


					break;
				}
				
				if (retValue == 3)
				{
					continue;
				}
							
			
			
			}//while
			
			
		

		}//end jump

		//for second display (first in character.cpp for  jump function)
		wentStaightThru = true;
	
		
		//left - not in jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && gKeypressDisabled == false && inJump == 0)//  && JustleftJump == false)
			{
			clock4.restart();
			aOrS = true;
			
			wentStaightThru = false;
			//flag
			isLeft = 1;
			sf::Vector2f  position = marioSpriteL.getPosition();
			int temp1 = position.x;
			int temp2 = position.y;

			//sort these:
			int no = 0;
			int goingDown2 = 0;
			int notUsed = 0;
			int isntFinished1 = 1;
			int counter1 = 0;
			
			int answer = character.movesLeftInLeftEndZone(SCREENHEIGHT, SCREENWIDTH, window, vectorPlatforms, marioSpriteL, marioSpriteR, positionX, positionY);
			
			if (answer == -1)
			{
				
				{
					
					gCallDrop = true;
					continue;
					
											
				}
				
			}
		}
		


		//right - not jump
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && gKeypressDisabled == false && inJump == 0)
		{
			clock4.restart();
			aOrS = true;
			
			wentStaightThru = false;
			
			
			isLeft = 0;
			sf::Vector2f  position = marioSpriteL.getPosition();
			
			//sort these
			int temp1 = position.x;
			int temp2 = position.y;
			int isntFinished1 = 1;
			int no = 0;
			int goingDown2 = 0;
			int notUsed = 0;
			
			int counter1 = 0;
			
			answer = character.movesRightInLeftEndZone(SCREENHEIGHT, SCREENWIDTH, window, vectorPlatforms, marioSpriteL, marioSpriteR, positionX, positionY);
			
			///////dropping character
			if (answer == -1)
			{
				
				{

					gCallDrop = true;
					continue;

					


				}
				

			}
			
		}//end if s
	
		if (isLeft == 0)
		{

			window.clear(gColor);

			window.draw(marioSpriteL);

			//RIGHT
			
			{

				miscObject.moveEnemies(window, 5, 0, 1);

				//if character has value of POSXCENETER change by ten, otherwise 5
				
				platform::drawAllPlatforms(vectorPlatforms, window);
				//1 = yes, 0 = no
				int isCharacterInMidSection = character.IsCharacterInMidSection(positionX);
				if (isCharacterInMidSection == 1  && (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
				{
					character.EnemyObject->moveEnemies(window, 10, -10, 0);
				}
				else if (isCharacterInMidSection == 1 )
				{
					character.EnemyObject->moveEnemies(window, 5, -10, 0);
				}
				else
				{
					character.EnemyObject->moveEnemies(window, 5, -10, 0);
				}


			}

			}

			else
			{
			
			window.clear(gColor);

			window.draw(marioSpriteR);

			//LEFT 
			{

				miscObject.moveEnemies(window, 5, 0, 1);
				
				
				platform::drawAllPlatforms(vectorPlatforms, window);


				//1 = yes, 0 = no
				int isCharacterInMidSection = character.IsCharacterInMidSection(positionX);
				if (isCharacterInMidSection == 1 && (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
				{
					character.EnemyObject->moveEnemies(window, 10, -10, 0);
				}
				else if (isCharacterInMidSection == 1)
				{
					character.EnemyObject->moveEnemies(window, 5, -10, 0);
				}
				else
				{
					character.EnemyObject->moveEnemies(window, 5, -10, 0);
				}
				

				//character.aaaaaaaaaaaaaaaaaaEnemyObject->moveEnemies(window, 10, -10, 0);

				
			}
			
		}


		// a or s keypress
		if (aOrS == true)
		{
			
			sf::Time elapsed4 = clock4.getElapsedTime();
			while (elapsed4.asMilliseconds() <= ELAPSED)
			{
				elapsed4 = clock4.getElapsedTime();

			}

			aOrS = false;
		}
	
		 else if (wentStaightThru == true)
		{
			gElapsed2 = clock2.getElapsedTime();
			while (gElapsed2.asMilliseconds() <= ELAPSED)
			{
				gElapsed2 = clock2.getElapsedTime();
			}
			wentStaightThru = false;
		}

		window.display();
	

	}//end while
	
}

//loop through platforms and move them horizontally
void SearchVectorForPlatforms(sf::RenderWindow & inWindow, float changeX, float changeY, int isLeft1)
{
	
	window.clear(gColor);
	for (std::vector<platform>::iterator it = vectorPlatforms.begin(); it != vectorPlatforms.end(); ++it)
	{
		//sprite is platform
		gottenSprite = it->getSprite();
		
		//character faces left
		if (isLeft1 == 1)
		{
			it->x = it->x + changeX;

			gottenSprite->setPosition((it->x), it->y);
		}

		if (isLeft1 == 0)
		{
			it->x = it->x - changeX;
			gottenSprite->setPosition((it->x), it->y);
		}

		if (it->x > -150 && it->x < (800))
		{
			 
			inWindow.draw(*it->platformSprite);
		}
	}
	
}


int checkForCollisions(std::vector<platform> vector, int positionX, int positionY)
{
	for (auto i = vector.begin(); i < vector.end() ; ++i)
	{ 
		//check for player collision with enemy
		if (i->type == "enemy")
		{
			int enemyLeft = i->x;
			int enemyRight = i->x + (i->width);
			int enemyTop = i->y;
			int enemyBottom = i->y + (i->height);

			int playerLeft = positionX;
			int playerRight = positionX + 76;
			int playerTop = positionY;
			int playerBottom = positionY + 76;

			if (enemyLeft > playerRight) return(false);
			if (enemyRight < playerLeft) return(false);
			if (enemyTop > playerBottom) return(false);
			if (enemyBottom < playerTop) return(false);

			return(true);

		}
			
		
	}
}



