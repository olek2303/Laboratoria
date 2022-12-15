#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

using namespace std;

typedef multiset<int> multint;
typedef multint::iterator mulit;

void generate_series(multint& r, multint& s) {
	for (int i = 0; i < 1000; i++) {
		r.insert(rand() % 10); // dodaj wynik nowej obserwacji
	}
	for (int i = 0; i < 1000; i++) {
		s.insert(rand() % 10); // dodaj wynik nowej obserwacji
	}
}

int zliczAll(int i, multint& v) {
	int zl = 0;
	pair<mulit, mulit> mult;
	mult = v.equal_range(i);
	zl = distance(mult.first, mult.second);
	return zl;
}

double odejmij(double x, double y) {
	return x - y;
}
double dodaj(double x, double y) {
	return x + y;
}
double potega(double x) {
	return pow(x, 2.0);
}
double dzialanie(double x, double y) {
	if (x == 0 && y == 0)
		return 0;
	double pom = odejmij(x, y);
	pom = potega(pom);
	double pomm = dodaj(x,y);
	return pom / pomm;
}

int main() {
	srand(time(NULL));
	multint r, s; // bufor do zapisywania obserwacji
	//1.
	generate_series(r, s);
	vector<int> R(10),S(10);

	//2.
	int i = 0;
	for_each(R.begin(), R.end(), [&](int& x) { R[i] = zliczAll(i,r); i++; });
	i = 0;
	for_each(S.begin(), S.end(), [&](int& x) { S[i] = zliczAll(i,s); i++; });

	cout << "R: ";
	for_each(R.begin(), R.end(), [](int& i) { cout.width(4); cout << i << " "; });
	cout << endl;
	cout << "S: ";
	for_each(S.begin(), S.end(), [](int& i) { cout.width(4); cout << i << " "; });
	cout << endl;

	//3.
	double x = 0.0;
	x = inner_product(R.begin(), R.end(), S.begin(), 0.0, plus<double>(), dzialanie);
	cout << "X^2: " << x << endl;


	return 0;
}