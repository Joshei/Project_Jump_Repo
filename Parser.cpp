#include "Parser.h"
#include <iostream>
#include <string>
//L30-R30+

Parser::Parser()
{
	string1 = "";
	currentLetter = '0';
	currentPositionIndex = 0;
	builtString = "";
	stringToParse = "R40=";
	gCounter = 0;
	gCounter1 = 0;
	gLength = 0;
}
std::string Parser::parseString(std::string s)
{
	
	//int length = s.length();
	//stringToParse = s;


	//parse
	//for (int i = 0; i < 1000; i++)
	
	{
		//if (stringToParse[currentPositionIndex] == '-')
		//{
		//	currentPositionIndex++;
		//}

		//if (stringToParse[currentPositionIndex] == '+')
		//{
		//	currentPositionIndex++;
		//}
		////done
		
		//
		

		//Finds Read symbol
		if (stringToParse[currentPositionIndex] == 'R')
		{
			int tempValue = currentPositionIndex + 1;
			currentLetter = 'R';
			currentPositionIndex++;
			while (isdigit(stringToParse[currentPositionIndex]))
			{
				gLength++;

				string1 = string1 + stringToParse[currentPositionIndex];
				currentPositionIndex++;
			}

			currentPositionIndex = tempValue;
			
		}
		////////
		else if (stringToParse[currentPositionIndex] == 'L')
		{
			int tempValue = currentPositionIndex + 1;
			currentLetter = 'L';
			currentPositionIndex++;
			while (isdigit(stringToParse[currentPositionIndex]))
			{
				gLength++;

				string1 = string1 + stringToParse[currentPositionIndex];
				currentPositionIndex++;
			}

			currentPositionIndex = tempValue;

		}

		////////

		if (currentLetter == "R")
		{

			int var = std::stoi(string1);

			for (int i = gCounter; i < var; i++)
			{
				gCounter++;
				//currentPositionIndex++;
				return("right");
			}
			int len = string1.length();
			for (int i = 0; i < len; i++)
			{
				currentPositionIndex++;
			}
			currentLetter = "!";
			string1 = "";
			
		}
		//////////

		else if (currentLetter == "L")
		{

			int var = std::stoi(string1);

			for (int i = gCounter1; i < var; i++)
			{
				gCounter1++;
				//currentPositionIndex++;
				return("left");
			}
			int len = string1.length();
			for (int i = 0; i < len; i++)
			{
				currentPositionIndex++;
			}
			
			

			currentLetter = "!";

			string1 = "";

		}

		if (stringToParse[currentPositionIndex] == '=')
		{
			currentPositionIndex = 0;
			currentLetter = ".";
			gLength = 0;
			gCounter = 0;
			gCounter1 = 0;
			string1 = "";
			//instead of done, repeats!
			return("done");

			
		}

		return(currentLetter);

		//////////

			////for (int i = currentPositionIndex;; i++)
			//{
			//	currentPositionIndex++;
			//	if (stringToParse[currentPositionIndex] == '1')
			//	{
			//		currentPositionIndex++;
			//		return("right");

			//	}
			//	
			//}
		///////}

		////walk left
		//else if (stringToParse[currentPositionIndex] == 'L')
		//{
		//	currentPositionIndex++;
		//	currentLetter = 'L';
		//	//for (int i = currentPositionIndex;; i++)
		//	{
		//		if (stringToParse[currentPositionIndex] == '1')
		//		{
		//			currentPositionIndex++;
		//			return("left");
		//		}
		//	}
		//}
		//
		//
		
		//checked for all letters, is not so in the process of sending command
		//else
		//{
		//	//for (int i = currentPositionIndex; ; i++)
		//	{
		//		
		//		if ((stringToParse[currentPositionIndex] == '1') && (currentLetter == "R"))
		//		{
		//			currentPositionIndex++;
		//			return("right");
		//		}
		//		if ((stringToParse[currentPositionIndex] == '1') && (currentLetter == "L"))
		//		{
		//			currentPositionIndex++;
		//			return("left");
		//		}
		//		
		//	}

		//}



	}


}
