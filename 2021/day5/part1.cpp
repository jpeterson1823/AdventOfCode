#include <iostream>
#include <string>

using namespace std;

// GLOBAL VARS
const int width = 1000;

string getInput();
void mapLine(int map[width][width], string line);


int main(int argc, char* argv[]) {
	string input = getInput();

	// create intersection map and init with all 0's
	int map[width][width];
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++)
			map[i][j] = 0;


	// go through each line and map its location
	bool flag = false;
	string linestr = "";
	for (char c : input) {
		if (c == ';') {
			mapLine(map, linestr);
			linestr = "";
			flag = true;
		} else {
			if (flag)
				flag = false;
			else
				linestr += c;
		}
	}


	// count all points where there are at least 2 lines overlap
	int intersections = 0;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++)
			if (map[i][j] >= 2)
				intersections++;

	cout << "Intersection Points: " << intersections << endl;

	return 0;
}




string getInput() {
	string input = "";
	string s;
	while (cin >> s)
		input += s + ' ';
	return input;
}

void mapLine(int map[width][width], string line) {
	// get the points from the string
	int spaceIndex = line.find(' ');
	int firstComma = line.find(',');
	int x1, y1, x2, y2;
	x1 = stoi(line.substr(0, firstComma));
	y1 = stoi(line.substr(firstComma+1, spaceIndex-2));

	string secondHalf = line.substr(spaceIndex+1);
	firstComma = secondHalf.find(',');
	x2 = stoi(secondHalf.substr(0, firstComma));
	y2 = stoi(secondHalf.substr(firstComma+1));


	// mark the line on the map
	if (x1 == x2) {
		for (int y = min(y1, y2); y <= max(y1, y2); y++)
			map[y][x1]++;
	}
	else if (y1 == y2) {
		for (int x = min(x1, x2); x <= max(x1, x2); x++)
			map[y1][x]++;
	}
}