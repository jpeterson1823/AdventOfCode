#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

vector<int> getPuzzleInput();
int getFinalVal(vector<int> intcode);

int main()
{
    vector<int> puzzleInput = getPuzzleInput();
    for (int i : puzzleInput)
        cout << i << " ";
    cout << endl;
    printf("Value at pos0: %i\n", getFinalVal(puzzleInput));
}

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