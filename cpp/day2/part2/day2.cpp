#include <vector>
#include <iostream>
#include "functions.h"

using namespace std;


int main()
{
    vector<int> puzzleInput = getPuzzleInput();
    int * nounAndVerb = getNounAndVerb(puzzleInput);
    if (nounAndVerb[0] == -1)
        cout << "Could not find the noun and verb.\n";
    else
    {
        cout << "100 * noun + verb = " << 100 * nounAndVerb[0] + nounAndVerb[1] << "\n";
    }
    
}