#include <stdio.h>
#include <vector>
#include "day1.h"

using namespace std;

int main()
{
    vector<int> puzzleInput = getPuzzleInput();
    printf("Total Fuel: %i\n", getTotalFuel(puzzleInput));
}