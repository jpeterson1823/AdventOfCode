#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void part1(vector<int> input);
void part2(vector<int> input);


int main(int argc, char* argv[]) {
    ifstream fs ("input.txt");
    if (!fs.is_open()) {
        cout << "Failed to open input file: 'input.txt'" << endl;
        exit(1);
    }

    string temp;
    vector<int> input;
    while (fs >> temp)
        input.push_back(stoi(temp));

    cout << "[PART1] ";
    part1(input);

    cout << "[PART2] ";
    part2(input);

    return 0;
}


void part1(vector<int> input) {
    int increases = 0;

    int last = input[0];
    if (last == -1) {
        cout << "Failed to convert first of input to integer" << endl;
        exit(1);
    }
    
    for (int i = 1; i < input.size(); i++) {
        if (input[i] > last)
            increases++;
        last = input[i];
    }

    cout << "Increases: " << increases << endl;
}

void part2(vector<int> input) {
    int increases = 0;
    int lsum, csum;

    lsum = input[0] + input[1] + input[2];
    for (int i = 1; i < input.size() - 2; i++) {
        csum = input[i] + input[i+1] + input[i+2];
        if (csum > lsum)
            increases++;
        lsum = csum;
    }

    cout << "Increases: " << increases << endl;
}
