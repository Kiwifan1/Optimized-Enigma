#include "Header.h"


int main(void)
{
    string wheelFilePath = "..\\Optimized Engima\\ReflectorText.txt";
    string reflectorFilePath = "..\\Optimized Engima\\ReflectorText.txt";
    string switchBoardFilePath = "..\\Optimized Engima\\SwitchboardSetup.txt";

    fstream wheelStream;
    fstream reflectorStream;

    if (openFile(wheelStream, wheelFilePath) && openFile(reflectorStream, reflectorFilePath))
    {
        string userResponse;
        cout << "Welcome to the Engima Machine!\n----------------------------------------\n" <<
            "Would you like to switch any letters? [Y] [N]:  ";
        cin >> userResponse;

        if (userResponse.compare("Y"))
        {
            //SwitchBoard* switchBoardPtr = new SwitchBoard(switchBoardFilePath);
        }
        else
        {

        }
    }

    else
    {
        cout << "Files unable to be opened!";
    }
	return 0;
}