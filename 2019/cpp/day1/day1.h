#include <math.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int getTotalFuel(vector<int> masses)
{
    int totalFuel = 0;
    for (int mass : masses) 
    {
        int extraFuel = floor(mass/3) - 2;      //Calculate the initial extra fuel needed.
        while (extraFuel > 0)                   //Make sure to loop until fuel for extra fuel is calculated.
        {
            //Add extraFuel to total, then calculate the fuel needed for extraFuel
            totalFuel += extraFuel;
            extraFuel = floor(extraFuel/3) - 2;
        }
    }
    
    return totalFuel;
}

vector<int> getPuzzleInput()
{
    //Open puzzleInput.txt and store values line by line
    
    vector<int> puzzleInput = { };      //set equal to a empty vector rather than null
    ifstream puzzleInputFile("puzzleInput.txt");
    string line;
    if (puzzleInputFile.is_open())
    {
        while(getline(puzzleInputFile, line))
        {
            puzzleInput.push_back(stoi(line));
        }
        puzzleInputFile.close();
    }
    else printf("Failed to open puzzle input file.\n");

    return puzzleInput;
}