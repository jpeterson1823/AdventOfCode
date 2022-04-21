#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main(int argc, char* argv[]) {
	// get input
	string input;
	cin >> input;

	// create fish vector
	vector<unsigned long> days = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// log initial fish
	for (char c : input) {
		if (c != ',')
			days[c - '0']++;
	}

	// loop for n days
	for (int day = 0; day < 256; day++) {
		// group each fish by it's day
		int today = day % 9;
		// push fish group by 7
		days[(today+7) % 9] += days[today];
	}

	// sum up all fish
	unsigned long numFish = 0;
	for (unsigned long day : days)
		numFish += day;

	cout << "Number of fish: " << numFish << endl;

	return 0;
}