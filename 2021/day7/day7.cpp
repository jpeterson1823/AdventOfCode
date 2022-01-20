#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getCost(vector<int> positions, int final_pos);

int main(int argc, char* argv[]) {
	// get input
	string input;
	cin >> input;

	// convert input into vector<int>
	vector<int> positions;
	string s = "";
	for (char c : input) {
		if (c != ',')
			s += c;
		else {
			positions.push_back(stoi(s));
			s = "";
		}
	}
	positions.push_back(stoi(s));

	// calculate fuel cost for positions
	int best = getCost(positions, 0);
	int cost;
	for (int i = 1; i < 1500; i++) {
		cost = getCost(positions, i);
		if (cost < best)
			best = cost;
	}

	// display total cost
	cout << "Best Cost: " << best << endl;

	return 0;
}


int getCost(vector<int> positions, int final_pos) {
	int cost = 0;
	for (int pos : positions) {
		int distance = abs(pos - final_pos);
		for (int i = 1; i <= distance; i++)
			cost += i;
	}
	return cost;
}