#include "Header.h"


//GLOBAL


bool openFile(fstream& stream, string filePath)
{
	stream.open(filePath);
	return stream.is_open();
}

vector<Disk> getWheelSetups(fstream& stream)
{
    vector<Disk> wheelTexts;
    Disk disk;
    string temp;

    //parses through file
    while (getline(stream, temp, '\n'))
    {
        //separates by space
        stringstream ss(temp);
        while (getline(ss, temp, ' '))
        {
            if (disk.innerText == "") disk.innerText = temp;
            else if (disk.outerText == "") disk.outerText = temp;

            if (disk.innerText != "" && disk.outerText != "")
            {
                wheelTexts.push_back(disk);
                disk.innerText = "", disk.outerText = "";
            }
        }
    }
    return wheelTexts;
}

void showPossibleWheels(vector<Disk> disks)
{
    for (int i = 0; i < disks.size(); i++)
    {
        cout << "DISK " << (i + 1) << " ";
        for (int i = 0; i < 19; i++)
        {
            cout << "-";
        }
        cout << endl;
        showWheelSetup(disks[i]);
        cout << endl;
    }
}

void showWheelSetup(Disk disk)
{
    cout << disk.innerText << endl;
    cout << disk.outerText << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << "-";
    }
    cout << endl;
}

void startEnigma()
{

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
        for (auto& [k, v] : letters)
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
        return true;
    }
    return false;
}

void SwitchBoard::resetMap()
{
    for (auto& [k, v] : letters)
    {
        v = k;
    }
    showMap();
}

// ROTOR CLASS

Rotor::Rotor()
{
    this->disk = Disk();
}

Rotor::Rotor(Disk disk)
{
    this->disk = disk;
}

Rotor::~Rotor()
{
    
}

void Rotor::rotateWheelC()
{
    
    // Inner Letters
    char temp = disk.innerText[disk.innerText.size() - 1];

    for (int i = disk.innerText.length() - 1; i > 0; i--)
    {
        disk.innerText[i] = disk.innerText[i - 1];
    }
    disk.innerText[0] = temp;

    // Outer Letters

    temp = disk.outerText[disk.outerText.size() - 1];
    for (int i = disk.outerText.length() - 1; i > 0; i--)
    {
        disk.outerText[i] = disk.outerText[i - 1];
    }
    disk.outerText[0] = temp;

    if (pos == 25)
    {
        pos = 0;
    }
    else
    {
        pos++;
    }
}

void Rotor::rotateWheelCC()
{
    // Inner Letters
    char temp = disk.innerText[0];

    for (int i = 0; i < disk.innerText.size() - 1; i++)
    {
        disk.innerText[i] = disk.innerText[i + 1];
    }
    disk.innerText[disk.innerText.size() - 1] = temp;

    // Outer Letters

    temp = disk.outerText[0];
    for (int i = 0; i < disk.outerText.size() - 1; i++) 
    {
        disk.outerText[i] = disk.outerText[i + 1];
    }
    disk.outerText[disk.outerText.size() - 1] = temp;

    if (pos == -25)
    {
        pos = 0;
    }
    else
    {
        pos--;
    }
}

// COG CLASS

Cog::Cog(Rotor chosenRotors[], string chosenReflector)
{
    leftRotor = chosenRotors[0];
    middleRotor = chosenRotors[1];
    rightRotor = chosenRotors[2];
    this->reflector = chosenReflector;
}

Cog::~Cog()
{
    delete& leftRotor;
    delete& middleRotor;
    delete& rightRotor;
    delete& reflector;
}

void Cog::rotateCog()
{
    leftRotor.rotateWheelC();
    if (leftRotor.getPos() == 25)
    {
        middleRotor.rotateWheelC();
        if (middleRotor.getPos() == 25)
        {
            rightRotor.rotateWheelC();
        }
    }
}
