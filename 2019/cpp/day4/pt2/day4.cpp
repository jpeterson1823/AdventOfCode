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
#include <iostream>
using namespace std;

bool isViablePswd(string pswd);
bool adjNums(string pswd);


int main()
{
    string max = "820401";
    //string max = "359282";
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

    // Are two adjacent digits the same?
    viable = adjNums(pswd);
    
    // Do digits decrease when going from left to right?
    int num = stoi(pswd);
    while (num >= 10)
    {
        if (num%10 < (num/10)%10)
            return false;
        else
            num /= 10;
    }

    return viable;
}

bool adjNums(string pswd)
{
    //316 is the correct answer
    vector<string> parts = {};
    int count = 0;
    for(char c : pswd)
    {
        for (int i = 0; i < pswd.length(); i++)
        {
            if (c != '-')
            {
                if (pswd[i] == c)
                {
                    pswd[i] = '-';
                    count++;
                }
            }
        }
        string part = "";
        for (int i = 0; i < count; i++)
            part += c;
        count = 0;
        parts.push_back(part);
    }


    for (string part : parts)
        if (part.length() == 2)
            return true;
    return false;
}