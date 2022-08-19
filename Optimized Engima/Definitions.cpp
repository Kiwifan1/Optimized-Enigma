#include "Header.h"


//GLOBAL


bool openFile(fstream& stream, string filePath)
{
	stream.open(filePath);
	return stream.is_open();
}

// SWITCHBOARD CLASS

SwitchBoard::SwitchBoard(string filePath)
{
    if (openFile(switchStream, filePath))
    {
        populateMap();
    }
    else
    {
        cout << "Unable to open Switchboard file!";
    }

}

SwitchBoard::~SwitchBoard()
{
    letters.clear();
}

void SwitchBoard::populateMap()
{
    string keys;
    string values;
    switchStream >> keys;
    switchStream >> values;
    cout << keys << endl << values;
}

void SwitchBoard::showMap()
{

}

bool SwitchBoard::switchLetters(char let1, char let2)
{
    return false;
}

void SwitchBoard::resetMap()
{
}
