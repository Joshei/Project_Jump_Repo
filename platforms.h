#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class platform
{
public:
	platform();


	static int advanceAllPlatforms(std::vector<platform>& vector, int changeX);
	static int drawAllPlatforms(std::vector<platform>& vector, sf::RenderWindow& inWindow);

	static int SearchVectorForPlatforms( std::vector<platform> &vector,sf::RenderWindow& inWindow, float changeX, float changeY, int isLeft1);
	sf::Sprite * platformSprite;
	platform(int width, int height,std::string string1, sf::Sprite * sprite);
	sf::Sprite * getSprite();
	int x;
	int y;
	int width;
	int height;
	std::string type;
	



protected:
	
};

