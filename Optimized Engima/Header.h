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
    map<char, char> letters;
    fstream switchStream;
    void populateMap();
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