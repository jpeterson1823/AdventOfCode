#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


vector<int> getIntcode();
void readIntcode(vector<int> intcode);

int main()
{
    vector<int> intcode = getIntcode();
    readIntcode(intcode);
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

        int param1, param2, param3;

        if (modec == 0) 
            param1 = intcode[intcode[index+1]];
        if (modec == 1) 
            param1 = intcode[index+1];

        if (modeb == 0)
            param2 = intcode[intcode[index+2]];
        if (modeb == 1)
            param2 = intcode[index+2];
        
        if (modea == 0)
            param3 = intcode[index+3];
        if (modea == 1)
            param3 = index+3;

        //printf("opcode: %i\nparam1: %i\nparam2: %i\nparam3: %i\n", opcode, param1, param2, param3);

        string input;
        switch (opcode)
        {
            case 99:
                index = intcode.size();
                break;

            case 1:
                intcode[param3] = param1 + param2;
                index += 4;
                break;

            case 2:
                intcode[param3] = param1 * param2;
                index += 4;
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
            
            case 5:
                if (param1 != 0)
                    index = param2;
                else index += 3;
                break;
            
            case 6:
                if (param1 == 0)
                    index = param2;
                else index += 3;
                break;
            
            case 7:
                if (param1 < param2)
                    intcode[param3] = 1;
                else intcode[param3] = 0;
                index += 4;
                break;
            
            case 8:
                if (param1 == param2)
                    intcode[param3] = 1;
                else intcode[param3] = 0;
                index += 4;
                break;
            default:
                cout << "Error has occured." << endl;
                printf("opcode: %i\nparam1: %i\nparam2: %i\nparam3: %i\n", opcode, param1, param2, param3);
                index = intcode.size();
                break;
        }
    }
}