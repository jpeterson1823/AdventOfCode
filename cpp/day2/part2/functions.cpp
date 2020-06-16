#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "day2.h"

using namespace std;

vector<int> getPuzzleInput() 
{
    vector<int> puzzleInput = { };

    ifstream puzzleInputFile ("puzzleInput.txt");
    string input;

    if (puzzleInputFile.is_open())
    {
        getline(puzzleInputFile, input);

        int lastIndex = 0;
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == ',')
            {
                puzzleInput.push_back(stoi(input.substr(lastIndex, i)));
                lastIndex = i+1;
            }
        }
        puzzleInput.push_back(stoi(input.substr(lastIndex, input.length())));
    }
    else printf("Failed to open puzzle input file.\n");

    return puzzleInput;
}

int getFinalVal(vector<int> intcode)
{
    int step = 4;
    int index = 0;
    while (index < intcode.size()-step)
    {
        int opcode = intcode.at(index);
        int val1 = intcode.at(intcode.at(index+1));
        int val2 = intcode.at(intcode.at(index+2));
        int storePos = intcode.at(index+3);

        switch (opcode) {
            case 1:
                intcode[storePos] = val1 + val2;
                break;
            case 2:
                intcode[storePos] = val1 * val2;
                break;
            case 99:
                index = intcode.size();
                break;
        }
        
        index += step;
    }

    return intcode[0];
}

int * getNounAndVerb(vector<int> intcode)
{
    for (int noun = 0; noun < 100; noun++)
    {
        vector<int> tempIntcode = intcode;
        for (int verb = 0; verb < 100; verb++)
        {
            tempIntcode[1] = noun;
            tempIntcode[2] = verb;
            if (getFinalVal(tempIntcode) == 19690720)
                return new int[2] { noun, verb };
        }
    }

    return new int[2] {-1, -1};
}