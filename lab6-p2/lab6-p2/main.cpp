#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 1, 2 = 6
// 3, 4 2x wieksze prawd niz 6
// 5 3x wieksze prawd niz 6

typedef vector<int> vecInt;
typedef vector<double> vecDouble;
typedef multiset<int> multiInt;

int generator() {
	int arr[] = { 1,2,3,4,5,6 };
	int freq[] = { 1,1,2,2,3,1 };
	int x = rand() % 100;
	if(x >= 0  && x <= 30) {
		int y = rand() % 3 + 1;
		if (y == 1)
			return 1;
		if (y == 2)
			return 2;
		if (y == 3)
			return 6;
	} else if (x > 30 && x <= 70) {
		int y = rand() % 2 + 1;
		if (y == 1) 
			return 3;
		if (y == 2)
			return 4;
	} else {
		return 5;
	}
}

int zliczAll(int i, multiInt& v) {
	int zl = 0;
	pair<multiInt::iterator, multiInt::iterator> mult;
	mult = v.equal_range(i);
	zl = distance(mult.first, mult.second);
	return zl;
}

int main() {
	srand(unsigned(time(NULL)));
	multiInt kostka;
	for(int i = 0; i < 100; i++) {
		kostka.insert(generator());
	}

	vecInt v(6);
	int i = 1;
	int iter = 0;
	for_each(v.begin(), v.end(), [&](int& x) { v[iter] = zliczAll(i, kostka); i++; iter++; });
	int licznik = 1;
	cout << "Rozklad Empiryczny: " << endl;
	for_each(v.begin(), v.end(), [&](int& x) { cout << licznik++ << ": " << x << "   "; });
	cout << endl;
	licznik = 1;

	vecDouble fin(6);
	partial_sum(v.begin(), v.end(), fin.begin());
	cout << "po Partial Sum: " << endl;
	for_each(fin.begin(), fin.end(), [&](double& x) { cout << licznik++ << ": " << x << "   "; });
	licznik = 1;
	cout << endl;
	double divider = 100;
	transform(fin.begin(), fin.end(), fin.begin(), [&](double& i) { return i / divider; });
	cout << "Koncowo (dystrybuanta): " << endl;
	for_each(fin.begin(), fin.end(), [&](double& x) { cout << licznik++ << ": " << x << "   "; });
	cout << endl;

	return 0;
}