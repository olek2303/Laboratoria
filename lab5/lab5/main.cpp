#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
struct sortPQ {
	bool operator() (const T& t1, const T& t2) const {
		return size(t1) < size(t2);
	}
};

typedef list<string> listString;
typedef priority_queue<listString, vector<listString>, sortPQ<listString>> PQListString;

class Mikser : public PQListString {
public:
	Mikser() { }
	Mikser(string fname) { open(fname); }
	~Mikser() { }
	void open(string fname);
	void write(string fname);
};

struct sortros {
	bool operator() (const string& t1, const string& t2) const {
		return t1 > t2;
	}
};

struct sortmal {
	bool operator() (const string& t1, const string& t2) const {
		return t1 < t2;
	}
};

ostream& operator<<(ostream& b, listString l) {
	listString::iterator it = l.begin();
	b << l.size() << ": ";
	while (it != l.end()) {
		b << *it << " ";
		it++;
	}
	b << endl;
	return b;
}

void Mikser::open(string fname) {
	ifstream f(fname);
	if(f.is_open()) {
		string line;
		while(getline(f, line)) {
			//wczytanie do listy slow pomocniczej linii tekstu
			list<string> pom;
			string word;
			string spr;
			if (line.empty())
				continue;
			istringstream iss(line);
			while (!iss.eof()) {
				spr = word;
				iss >> word;
				if (word == "\n" || spr == word)
					continue;
				pom.push_back(word);
			}
			if (pom.size() < 6) {
				//sortuj rosnaco
				pom.sort(sortros());
			} else if (pom.size() >= 6){
				//sortuj malejaco
				pom.sort(sortmal());
			}
			push(pom);
		}
		f.close();
	} else {
		cout << "Nie otwarto pliku." << endl;
	}
}



void Mikser::write(string fname) {
	ofstream f(fname);
	if(f.is_open()) {
		while(!empty()) {
			listString l = top();
			f << l;
			pop();
		}
		f.close();
	}
}

int main() {

	Mikser m;
	m.open("mistrz.txt");
	m.write("wynik.txt");

	return 0;
}