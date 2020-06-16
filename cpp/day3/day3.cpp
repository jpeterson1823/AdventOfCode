#include <iostream>
#include <algorithm>
#include "func.h"
using namespace std;

int main() 
{
    vector<vector<string>> bothInstructions = getInstructions(getPuzzleInput());

    vector<coord> coords1 = convertInstructionsToCoords(bothInstructions[0]);
    vector<coord> coords2 = convertInstructionsToCoords(bothInstructions[1]);
    vector<coord> intersections = { };

    printf("Total coords found: %i\nNow checking for intersections...\n", coords1.size()+coords2.size());

    // Compare every coord1 to coord2 via nested for loops;
    for (int i = 0; i < coords1.size(); i++)
    {
        for (int j = 0; j < coords2.size(); j++)
        {
            if (coords1[i].x == coords2[j].x && coords1[i].y == coords2[j].y)
            {
                printf("\tIntersection found at [%i,%i]\n", coords1[i].x, coords1[i].y);
                intersections.push_back(coords1[i]);
            }
        }
    }

    printf("Found %i intersections. Getting closest intersection to origin...\n", intersections.size());

    int shortestMD = getManhattanDistance(intersections[0]);
    coord intersect;
    for (int i = 1; i < intersections.size(); i++)
    {
        int md = getManhattanDistance(intersections[i]);
        if (md < shortestMD)
        {
            intersect = intersections[i];
            shortestMD = md;
        }
    }

    printf("Found closest intersect. Now finding steps to intersect...\n");

    int steps1 = 0;
    for (int i = 0; i < coords1.size(); i++)
    {
        steps1++;
        if (coords1[i].x == intersect.x && coords1[i].y == intersect.y)
            i = coords1.size(); steps1--;
    }

    int steps2 = 0;
    for (int i = 0; i < coords2.size(); i++)
    {
        steps2++;
        if (coords2[i].x == intersect.x && coords2[i].y == intersect.y)
            i = coords2.size(); steps1--;
    }

    printf("All processes complete.\n\n");


    printf("Shortest Manhattan Distance from Origin: %i\n", shortestMD);
    printf("Least steps needed to reach intersect:   %i\n", min(steps1, steps2));

    return 0;
}