#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
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

    void populateMap();
    bool isLetter(char& letter);
public:
    SwitchBoard(string filePath);
    ~SwitchBoard();
    void showMap();
    bool switchLetters(char let1, char let2);
    void resetMap();
};

//COG CLASS

class Cog
{
private:
    /* data */
public:
    Cog();
    ~Cog();
};

// WHEEL CLASS

class Wheel
{
private:
    /* data */
public:
    Wheel();
    ~Wheel();
};

bool openFile(fstream& stream, string filePath);

#endif