#include <string>
#include <vector>
using namespace std;

struct coord {
    int x, y;
};

vector<string> getPuzzleInput();
vector<vector<string>> getInstructions(vector<string> puzzleInput);
vector<coord> convertInstructionsToCoords(vector<string> instructions);
int getManhattanDistance(coord c);