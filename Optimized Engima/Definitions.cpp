#include "Header.h"


//GLOBAL


/**
 * This function opens a file and returns true if the file is open.
 * 
 * @param stream The file stream object to open the file with.
 * @param filePath The path to the file you want to open.
 * 
 * @return A boolean value.
 */
bool openFile(fstream& stream, string filePath)
{
	stream.open(filePath);
	return stream.is_open();
}

/**
 * It takes a file stream and returns a vector of Disk objects
 * 
 * @param stream the file stream
 * 
 * @return A vector of Disk objects.
 */
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

            /* Checking if the innerText and outerText are empty. */
            if (disk.innerText != "" && disk.outerText != "")
            {
                wheelTexts.push_back(disk);
                disk.innerText = "", disk.outerText = "";
            }
        }
    }
    return wheelTexts;
}

/**
 * It prints out the possible wheels for each disk
 * 
 * @param disks vector of Disk objects
 */
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

/**
 * It prints out the inner and outer text of the disk, showing the setup
 * 
 * @param disk The disk object that is being displayed.
 */
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

/**
 * It reads in a string of keys and a string of values from a file, converts them to vectors, and then
 * populates a map with the keys and values
 * 
 * @return a map of char to char.
 */
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

/**
 * It takes a map of char to char, and prints out the keys and values in two columns
 */
void SwitchBoard::showMap()
{
    vector<char> values;
    if (!letters.empty())
    {
        // Iterating through the map
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


/**
 * It takes two characters as arguments, checks if they are letters, and if they are, it switches their
 * positions in the map
 * 
 * @param let1 The first letter to switch
 * @param let2 the second letter to be switched with let1
 * 
 * @return a boolean value.
 */
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

/**
 * It checks if the character is a letter, converts it to uppercase if lowercase
 * 
 * @param letter The letter to be checked
 * 
 * @return a boolean value of successful letter checking
 */
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

/**
 * It loops through the map and sets the value of each key to the key itself *resetting* it
 */
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

/**
 * Rotates each disk to the right by one position (clockwise)
 * 
 */
void Rotor::rotateWheelC()
{
    
    // Inner Letters
    char temp = disk.innerText[disk.innerText.size() - 1];

    //Rotating the innerText of the disk.
    for (int i = disk.innerText.length() - 1; i > 0; i--)
    {
        disk.innerText[i] = disk.innerText[i - 1];
    }
    disk.innerText[0] = temp;

    // Outer Letters

    temp = disk.outerText[disk.outerText.size() - 1];
    //Rotating the outerText of the disk.
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

/**
 * Rotates each disk to the left by one position (counter clockwise)
 * 
 */
void Rotor::rotateWheelCC()
{
    // Inner Letters
    char temp = disk.innerText[0];

    //Rotating the innerText of the disk.
    for (int i = 0; i < disk.innerText.size() - 1; i++)
    {
        disk.innerText[i] = disk.innerText[i + 1];
    }
    disk.innerText[disk.innerText.size() - 1] = temp;

    // Outer Letters

    temp = disk.outerText[0];
    //Rotating the outerText of the disk.
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

/**
 * The function rotates the left rotor, and if the left rotor's position is 25 (rotated fully), it rotates the middle
 * rotor, and if the middle rotor's position is 25 (rotated fully), it rotates the right rotor
 */
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
