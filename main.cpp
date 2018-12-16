// Jason Schilling
// Z23270204
// HW9
// WILL ONLY WORK FOR ASSEMBLYLINES = 2. PROCEED WITH CAUTION.

#include <algorithm> //for min
#include <iostream>

#define assemblyLines 2
#define stations 6

int Memo(int[][stations], int[][stations], int, int, int, int[][stations]);

int main() {

	// HARD CODE DATA ////////////////////
	// station data
	// FIRST ENTRIES ARE BOTH 0. THEY ARE THE PRETEND STARTING POINT.
	int s[assemblyLines][stations] =
	{ 
		{ 0, 2, 7, 1, 4, 3 },
		{ 0, 6, 9, 9, 1, 1 }
	};
	// transfer data
	int t[assemblyLines][stations] =
	{
		{ 1, 3, 3, 2, 6, 3 },
		{ 8, 6, 1, 1, 5, 2 }
	};
	// memoize data
	int f[assemblyLines][stations] =
	{
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1 }
	};
	///////////////////////////////////////

	int result = Memo(s, t, 0, 0, stations-1, f);
	std::cout << "shortest path: " << result << "\n";

	system("pause");

	return 0;
}

int Memo(int s[][stations], int t[][stations], int i, int j, int n, int f[][stations]) {
	// data already calculated, so take from memo array
	if (f[i][j] != -1) {
		return f[i][j];
	}

	// end of the line
	if (j == n) {
		f[i][j] = s[i][j] + t[i][j];
		return f[i][j];
	}

	// at the beginning, so grab the correct transfer data.
	int startCost1 = 0;
	int startCost2 = 0;
	if (j == 0) {
		startCost1 = t[0][0];
		startCost2 = t[1][0];
	}

	// main recursive section
	int path1min = startCost1 + s[i][j] + Memo(s, t, i, j + 1, n, f);
	int path2min = startCost2 + s[i][j] + t[i][j] + Memo(s, t, 1 - i, j + 1, n, f);
	f[i][j] = std::min(path1min, path2min);
	return f[i][j];
}