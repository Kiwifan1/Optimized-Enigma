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
        switchStream.flush();
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

    vector<char> keysVector(keys.begin(), keys.end());
    vector<char> valsVector(values.begin(), values.end());

    if (keysVector.size() != valsVector.size())
    {
        cout << "Different size of key-value vectors!";
        return;
    }
    else
    {
        for (int i = 0; i < keysVector.size(); i++)
        {
            letters[keysVector[i]] = valsVector[i];
        }
        showMap();
    }
    switchStream.seekg(0, switchStream.beg); //resets the stream to the beginning of the file
}

void SwitchBoard::showMap()
{
    vector<char> values;
    if (!letters.empty())
    {
        for (auto [k, v] : letters)
        {
            cout << k << " ";
            values.push_back(v);
        }
        cout << endl;
        for (char val : values)
        {
            cout << val << " ";
        }
        cout << "\n--------------------" << endl;
    }
    else
    {
        cout << "Switchboard empty, something wrong!";
    }
}


bool SwitchBoard::switchLetters(char let1, char let2)
{
    try
    {
        if (isLetter(let1) && isLetter(let2))
        {
            char temp = letters.at(let1);
            letters[let1] = letters[let2];
            letters[let2] = temp;
        }
        showMap();
        return true;
    }
    catch (const out_of_range&)
    {
        return false;
    }
}

bool SwitchBoard::isLetter(char& letter)
{
    if (letter >= 65 && letter <= 90)
    {
        return true;
    }
    else if (letter >= 97 && letter <= 122)
    {
        letter -= 32;
        cout << letter;
        return true;
    }
    return false;
}

void SwitchBoard::resetMap()
{
}
