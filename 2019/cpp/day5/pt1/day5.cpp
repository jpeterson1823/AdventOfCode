#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


vector<int> getIntcode();
void readIntcode(vector<int> intcode);

int main()
{
    readIntcode(getIntcode());
}





vector<int> getIntcode() 
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


void readIntcode(vector<int> intcode)
{
    int index = 0;
    while (index < intcode.size())
    {
        int opcode = intcode[index]%100;
        int modec = intcode[index]/100%10;
        int modeb = intcode[index]/1000%10;
        int modea = intcode[index]/10000%10;

        //printf("Opcode: %i\nmodea: %i\nmodeb: %i\nmodec: %i\n", opcode, modea, modeb, modec);

        int val1, val2, storepos;

        if (modec == 0) 
            val1 = intcode[intcode[index+1]];
        if (modec == 1) 
            val1 = intcode[index+1];

        if (modeb == 0)
            val2 = intcode[intcode[index+2]];
        if (modeb == 1)
            val2 = intcode[index+2];
        
        if (modea == 0)
            storepos = intcode[index+3];
        if (modea == 1)
            storepos = index+3;

        //printf("val1: %i\nval2: %i\nstorepos: %i\n", val1, val2, storepos);

        string input;
        switch (opcode)
        {
            case 99:
                index = intcode.size();
                break;
            case 3:
                cout << "Input a value: ";
                cin >> input;
                intcode[intcode[index+1]] = stoi(input);
                index += 2;
                break;
            case 4:
                cout << "Value: " << intcode[intcode[index+1]] << endl;
                index += 2;
                break;
            case 1:
                intcode[storepos] = val1 + val2;
                index += 4;
                break;
            case 2:
                intcode[storepos] = val1 * val2;
                index += 4;
                break;
        }
    }
}