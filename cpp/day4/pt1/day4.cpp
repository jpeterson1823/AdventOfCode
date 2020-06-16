/*
--- Day 4: Secure Container ---

You arrive at the Venus fuel depot only to discover it's protected by a password. The Elves had written the password on a sticky note, but someone threw it out.

However, they do remember a few key facts about the password:

    It is a six-digit number.
    The value is within the range given in your puzzle input.
    Two adjacent digits are the same (like 22 in 122345).
    Going from left to right, the digits never decrease; they only ever increase or stay the same (like 111123 or 135679).

Other than the range rule, the following are true:

    111111 meets these criteria (double 11, never decreases).
    223450 does not meet these criteria (decreasing pair of digits 50).
    123789 does not meet these criteria (no double).

How many different passwords within the range given in your puzzle input meet these criteria?

Your puzzle input is 359282-820401
*/

#include <utility>
#include <string>
#include <vector>
using namespace std;

bool isViablePswd(string pswd);


int main()
{
    string max = "820401";
    string pswd = "359282";
    vector<string> viables = { };

    while(stoi(pswd) <= stoi(max))
    {
        if (isViablePswd(pswd))
            viables.push_back(pswd);

        int newVal = stoi(pswd)+1;
        for (int i = 0; i < 6; i++)
            pswd[i] = to_string(newVal)[i];
    }

    printf("Different pswds within range: %i\n", viables.size());
}


bool isViablePswd(string pswd)
{
    bool viable = true;

    // Is it a 6 digit number?
    if (stoi(pswd) > 999999)
        viable = false;

    // Is it bigger than the max?
    // This is covered by the while loop in main().

    // Are two adjacent digits the same?
    bool adj = false;
    for (int i = 1; i < pswd.length(); i++)
        if (pswd[i] == pswd[i-1])
            adj = true;
    if (!adj)
        viable = false;
    
    // Do digits decrease when going from left to right?
    for (int i = 1; i < pswd.length(); i++)
        if (pswd[i] - 48 < pswd[i-1] - 48)
            viable = false;

    return viable;
}