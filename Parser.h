#pragma once
#include<string>
//enum parsedLetter { right, left };

class Parser
{
public:
	//L30-R30+
	//R11111L11111;
	int gCounter1;
	int gCounter;
	int gLength;
	std::string string1;
	std::string currentLetter;
	//parsedLetter symbol = right;
	std::string builtString;
	int currentPositionIndex;
	Parser();
	std::string stringToParse;
	std::string parseString (std::string s);

};

