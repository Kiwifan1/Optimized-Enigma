#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//SWITCHBOARD CLASS

class SwitchBoard
{
private:
    map<char, char> letters; //A map containing the mapping of the switchboard
    fstream switchStream; //fstream for reading and writing to the file for saving the state of the switchboard

    void showMap();
    bool isLetter(char& letter);

public:
    SwitchBoard(string filePath);
    ~SwitchBoard();
    
    bool switchLetters(char let1, char let2);
    void resetMap();
    void populateMap();
};

//WHEEL TEXT STRUCTURE

struct Disk
{
    string innerText;
    string outerText;
};

// ROTOR CLASS

class Rotor
{
private:
    Disk disk;
    int pos = 0;

    //given a position on the outer wheel, find the letter that matches on the inner wheel
    char getCharSamePos(int pos) { return disk.innerText[pos]; }
public:
    Rotor();
    Rotor(Disk disk);
    ~Rotor();
    Disk getDisk() { return disk; }
    int getPos() { return pos; }
    void rotateWheelC();
    void rotateWheelCC();

    //given a letter on the inner wheel, find the position that matches on the other wheel
    int getPosSameChar(Rotor otherRotor, char letter) { return otherRotor.getDisk().outerText.find(letter); }

};

//COG CLASS

class Cog
{
private:
    Rotor leftRotor;
    Rotor middleRotor;
    Rotor rightRotor;
    string reflector;
public:
    void rotateCog();
    Cog(Rotor chosenRotors[], string chosenReflector);
    ~Cog();
};


//GLOBAL 
const static int WHEEL_NUM = 4;

bool openFile(fstream& stream, string filePath);
vector<Disk> getWheelSetups(fstream& stream);
void showWheelSetup(Disk disk);
void showPossibleWheels(vector<Disk> disks);
void startEnigma();

#endif