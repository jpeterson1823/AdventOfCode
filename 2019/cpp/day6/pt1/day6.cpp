#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct planet{
    string name;
    vector<string> children;
    planet(string pname)
        : name(pname) {}
};

vector<string> getOrbitInstructions();
vector<planet> getPlanetList(vector<string> orbitalInstructions);



int main()
{
    vector<string> orbitInstructions = getOrbitInstructions();
    vector<planet> pList = getPlanetList(orbitInstructions);
    
    int totalOrbits = getOrbits("COM", pList, 0);

    printf("Total Orbits: %i\n", totalOrbits);
}




vector<string> getOrbitInstructions()
{
    vector<string> orbitInstructions = {};

    ifstream puzzleInput ("test.txt");
    if (puzzleInput.is_open())
    {
        string line;
        while(getline(puzzleInput, line))
            orbitInstructions.push_back(line);
    }
    else cout << "Failed to find input file..." << endl;
    puzzleInput.close();

    return orbitInstructions;
}

vector<planet> getPlanetList(vector<string> orbitalInstructions)
{
    vector<planet> orbitalList = { };

    for(string instruct : orbitalInstructions)
    {
        string parent = instruct.substr(0,instruct.find(")"));
        string child = instruct.substr(instruct.find(")"));

        bool found = false;
        for (planet p : orbitalList)
        {
            if (p.name == parent)
            {
                p.children.push_back(child);
                found = true;
            }
        }

        if (!found)
        {
            planet p(parent);
            p.children.push_back(child);
            orbitalList.push_back(p);
        }
    }

    return orbitalList;
}

int getOrbits(string pName, vector<planet> pList, int count)
{
    
}