/*
* Copyright (c) 2012-2022 Scott Chacon and others

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // sort
#include <fstream>
#include "../../Headers/Console.h"

// MENU ENUM
enum 
{
	SELECT = 1,
	ADD,
	REMOVE,
	SORT,	
	CLEAR,
	RESET,
	SAVE, 
	LOAD,
	EXIT
};



// GLOBALS
std::vector<std::string> original; // constant
std::vector<std::string> types;

// FORWARD DECLARATIONS
int NumPrompt(const char *_msg, int _min, int _max);
void TextPrompt(const char *_msg, char *&_text);
std::string PickFood(); // returns the contents of a random vector index
void MainMenu();
void DisplayList();
void AddCategory();
void RemoveCategory();
void GetFoodRNG();
bool Compare(std::string _a, std::string _b);
void SortCategories();
void ClearList();
void ResetList();
void SaveList();
void LoadList(std::string& _filepath);

int main() 
{
	// LEAK DETECTION
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(156);
	_CrtDumpMemoryLeaks();

	system("color 05");

	// Push food categories into container
	types.push_back("American");	// [0]
	types.push_back("Bar/Pub");
	types.push_back("Breakfast");
	types.push_back("BBQ");
	types.push_back("Cafe");
	types.push_back("Chinese");
	types.push_back("Diner");
	types.push_back("Fast Food");
	types.push_back("Healthy");
	types.push_back("Indian");
	types.push_back("Italian");
	types.push_back("Japanese");
	types.push_back("Korean");
	types.push_back("Mexican");	
	types.push_back("Pizza");
	types.push_back("Seafood");
	types.push_back("Steakhouse");
	types.push_back("Sushi");
	types.push_back("Tex-Mex");

	for (int i = 0; i < types.size(); i++)
		original.push_back(types[i]);

	// "Game" loop
	while (true) 
	{
		MainMenu();
		break;
	}

	std::cout << "\nGoodbye!\n\t\t";
	std::cin.get();
	return 0;
}

std::string PickFood() 
{
	srand(time(NULL));
	int rng = rand() % types.size();

	return types[rng];
}

void MainMenu() 
{
	int menuChoice = 0;

//#ifndef NDEBUG
	std::string filepath = "foodcategories.txt";
//#endif
	//std::string filepath = "../SaveData/foodcategories.txt";

	// Resize window
	RECT rect; // stores console's current dimensions
	HWND win = GetConsoleWindow();
	GetWindowRect(win, &rect);
	MoveWindow(win, rect.left, rect.top, 600, 800, TRUE);

	system("cls");
	DisplayList();
	std::cout	<< "1) Tell me my food fortune"		<< std::endl
				<< "2) Add Category"				<< std::endl
				<< "3) Remove Category"				<< std::endl
				<< "4) Sort List"					<< std::endl
				<< "5) Clear List"					<< std::endl
				<< "6) Reset List"					<< std::endl
				<< "7) Save List"					<< std::endl
				<< "8) Load List"					<< std::endl
				<< "9) Exit"						<< std::endl;

	while (true) 
	{
		menuChoice = NumPrompt("\nWhat would you like to do (Enter a number)?", 1 , 9);
		switch (menuChoice)
		{
			case SELECT:
			{
				if (types.size() == 0)
				{
					std::cout << "\nCannot select from an empty list!" << std::endl;
					continue;
				}
				else
				{
					GetFoodRNG();
				}
				break;
			}
			case ADD:
			{
				AddCategory();
				break;
			}
			case REMOVE:
			{
				if (types.size() == 0) 
				{
					std::cout << "\nCannot remove from an empty list!" << std::endl;
					continue;
				}
				else
				{
					RemoveCategory();
				}
				break;
			}
			case SORT:			
			{
				SortCategories();
				std::cout << "List sorted!" << std::endl;
				break;
			}
			case CLEAR:
			{
				ClearList();
				break;
			}
			case RESET:
			{
				ResetList();
				break;
			}
			case SAVE:
			{
				SaveList();
				break;
			}
			case LOAD:
			{
				LoadList(filepath);
				break;
			}
			case EXIT:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void DisplayList() 
{
	std::cout << ":::: Don't know what to eat? ::::" << std::endl;
	printf("Food categories (%d total):\n\n", types.size());		// I like this!

	for (int i = 0; i < types.size(); i++)
		std::cout << i + 1 << ": " << types[i] << std::endl;

	if (types.empty())
		std::cout << "[...List is empty...]" << std::endl;

	std::cout << "\n:::::::::::::::::::::::::::::::::\n\n";
}

void AddCategory() 
{
	char *input = nullptr;

	system("cls");
	DisplayList();
	TextPrompt("Enter the NAME of your new category: ", input);

	types.push_back(input);

	delete[] input;
	MainMenu();
}

void RemoveCategory() 
{
	bool isRemoved = false;
	while (!isRemoved) 
	{
		system("cls");
		DisplayList();

		int choice = NumPrompt("Enter the NUMBER to remove: ", 0, types.size());

		types.erase(types.begin() + choice - 1); // - 1 for the menu offset displayed to the user
		isRemoved = true;
	}
	MainMenu();
}

void GetFoodRNG() 
{
	char input = ' ';
	bool exit = false;
	while (!exit) 
	{
		system("cls");
		DisplayList();

		std::cout << "('B' to back)"						<< std::endl;
		std::cout << "\nspo0pbae thinks you should eat "	<< std::endl;
		std::cout << '\t' << PickFood() << '\n'				<< std::endl;

		std::cout << "Do you want to eat something else? (Y/N)\n";
		std::cin  >> input;
#if 0
		while (true) 
		{
			cin >> input;
			if (input == 'Y' || input == 'y') {
				system("cls");
				DisplayList();
				continue;
			}
			else if (input == 'N' || input == 'n' || input == 'B' || input == 'b') {
				exit = true;								// exit condition
			}
			else {
				cout << "Invalid input. (Y/N)";
				continue;
				// loop back around to input
				//exit = true; // just leaving this here until i add in the third option
			}
			break;
		}
#endif
#if 1
		if (input == 'Y' || input == 'y') 
		{
			system("cls");
			DisplayList();
			continue;
		}
		else if (input == 'N' || input == 'n') 
		{
			exit = true;								// exit condition
		}
		else 
		{
			//cout << "Invalid input. (Y/N)";
			// loop back around to input
			exit = true; // just leaving this here until i add in the third option
		}	
#endif
	}
	MainMenu();
}

void ClearList() 
{
	types.clear();
	types.resize(types.size());
	MainMenu();
}

void ResetList() 
{
	types.clear();
	types.resize(types.size());

	for (int i = 0; i < original.size(); i++)
		types.push_back(original[i]);	// Set list back to the original list

	MainMenu();
}

// Helper function for sorting a string vector
bool Compare(std::string _a, std::string _b)
{
	return _a < _b;
}

void SortCategories()
{
	std::sort(types.begin(), types.end(), Compare);
	MainMenu();
}

// HELPER FUNCTIONS
int NumPrompt(const char *_msg, int _min, int _max) 
{
	int input;
	std::cout << _msg << std::endl;

	while (true) 
	{
		std::cin >> input;
		if (std::cin.fail() || input < _min || input > _max)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid input. Enter a valid number." << std::endl;
			continue;
		}
		std::cin.ignore(INT_MAX, '\n');
		break;
	}
	return input;
}

void TextPrompt(const char *_msg, char *&_text) 
{
	int len = 0;
	char buffer[500];

	std::cout << _msg << std::endl;
	std::cin.getline(buffer, 500, '\n');
	len = strlen(buffer) + 1;

	delete[] _text;

	_text = new char[len];
	strcpy_s(_text, len, buffer);
}

// Save categories to a new text file
void SaveList()
{
//#ifndef NDEBUG
	std::string fileName("foodcategories.txt");
//#endif
	//std::string fileName("../SaveData/foodcategories.txt");
	std::string line;
	std::ofstream file;

	// open file
	file.open(fileName, std::ios_base::trunc);		// trunc deletes previous contents

	// write to file
	if (!file.is_open())
	{
		printf("Failed to open file!\n");
	}
	else
	{
		// check if file is empty so we can write a header
		file.seekp(0, std::ios::end);
		int size = file.tellp();
		if (size == 0)
			file << "-- FOOD CATEGORIES --" << std::endl;

		for (size_t i = 0; i < types.size(); ++i)
		{
			file << types[i] << std::endl;
		}
	}

	// close file
	file.close();

	// Back to main menu
	MainMenu();
}

void LoadList(std::string& _filepath)
{
	std::string line;
	int16_t ndx = 0;

	// Clear and resize vector
	types.clear();
	types.resize(types.size());

	std::ifstream file{_filepath, std::ios::in};

	if (!file.is_open())
	{
		std::cout << "Failed to open file!\nPath: " << _filepath << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			// Skip first line?
			std::getline(file, line);

			if (line != "-- FOOD CATEGORIES --")
				types.push_back(line);
		}
	}

	// All done!
	file.close();

	// Remove the empty string at the end
	if (types.back() == "")
	{
		types.pop_back();
		types.shrink_to_fit();
	}

	MainMenu();
}