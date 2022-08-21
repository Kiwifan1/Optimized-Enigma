#include "Header.h"


int main(void)
{
    string wheelFilePath = "..\\Optimized Engima\\WheelText.txt";
    string reflectorFilePath = "..\\Optimized Engima\\ReflectorText.txt";
    string switchBoardFilePath = "..\\Optimized Engima\\SwitchboardSetup.txt";

    fstream wheelStream;
    fstream reflectorStream;

    string temp;
    if (openFile(wheelStream, wheelFilePath) && openFile(reflectorStream, reflectorFilePath))
    {
        string userResponse;
        cout << "Welcome to the Engima Machine!\n----------------------------------------\n" <<
            "Would you like to switch any letters? [Y] [N]:  ";
        cin >> userResponse;

        if (userResponse == "Y" )
        {
            cout << endl;
            //SwitchBoard* switchBoardPtr = new SwitchBoard(switchBoardFilePath);
            vector<Disk> disks = getWheelSetups(wheelStream);
            Rotor rotors[3] = { Rotor(disks[0]), Rotor(disks[1]), Rotor(disks[2]) };
            getline(reflectorStream, temp, '\n');
            Cog cog(rotors, temp);
            cog.rotateCog();
        }
        else
        {
            cout << "Goodbye!";
        }
    }

    else
    {
        cout << "Files unable to be opened!";
    }
	return 0;
}