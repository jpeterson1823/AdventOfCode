#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "func.h"

using namespace std;

vector<string> getPuzzleInput()
{
    cout << "Grabbing puzzle input...\n";
    vector<string> lines = { };

    ifstream puzzleFile ("puzzleInput.txt");
    if (puzzleFile.is_open())
    {
        string line;
        while(getline(puzzleFile,line))
            lines.push_back(line);
    }

    return lines;
}


vector<string> split(string str, char delimiter)
{
    vector<string> splitStr = { };

    istringstream iss(str);
    string token;
    while (getline(iss, token, delimiter))
    {
        splitStr.push_back(token);
    }

    return splitStr;
}


vector<vector<string>> getInstructions(vector<string> puzzleInput)
{
    cout << "Getting instructions...\n";
    vector<vector<string>> instructions = { };

    for (string input : puzzleInput)
    {
        instructions.push_back(split(input, ','));
    }
    return instructions;
}

vector<coord> convertInstructionsToCoords(vector<string> instructions)
{
    cout << "Converting instructions to vector of coords...\n";
    vector<coord> coords = { };

    int x, y = 0;
    for (string instruct : instructions)
    {
        char direction = instruct[0];
        int distance = stoi(instruct.substr(1));

        switch (direction){
            // Add every single coord possible via adding a struct coord for every step in 
            // distance.
            case 'R':
                for (int i = 0; i < distance; i++)
                {
                    x++;
                    coord c;
                    c.x = x;
                    c.y = y;
                    coords.push_back(c);
                }
                break;
            case 'L':
                for (int i = 0; i < distance; i++)
                {
                    x--;
                    coord c;
                    c.x = x;
                    c.y = y;
                    coords.push_back(c);
                }
                break;
            case 'U':
                for (int i = 0; i < distance; i++)
                {
                    y++;
                    coord c;
                    c.x = x;
                    c.y = y;
                    coords.push_back(c);
                }
                break;
            case 'D':
                for (int i = 0; i < distance; i++)
                {
                    y--;
                    coord c;
                    c.x = x;
                    c.y = y;
                    coords.push_back(c);
                }
                break;
        }
    }

    return coords;
}

int getManhattanDistance(coord c)
{
    return abs(c.x)+abs(c.y);
}