#include <iostream>
#include <set>
#include <list>
#include <string>
#include <fstream>

using namespace std;

typedef list<set<string>> lsString;

template<typename T>
struct sortuj {
	bool operator()(const T& t1, const T& t2) {
		return size(t1) > size(t2);
	}
};

template<typename T>
class domieszka : public T {
public:
	void write_set(ofstream& f, lsString::iterator it) {
		f << (*it).size() << ": ";
		T::write_set(f, it);
	}
};

class Mikser2 : public lsString {
public:
	Mikser2() {};
	Mikser2(string fname) { open(fname); }
	~Mikser2() { clear(); };
	void open(string fname);
	void execute() { sort(sortuj<set<string>>()); };
	void write(string fname);
	virtual void write_set(ofstream& f, lsString::iterator it);
};

void Mikser2::open(string fname) {
	ifstream f(fname);
	if(f.is_open()) {
		string word;
		set<string> acc;
		while(f >> word) {
			acc.insert(word);
			if(f.peek() == '\n') {
				push_back(acc);
				acc.clear();
			}
				
		}
		f.close();
	} else {
		cout << "Plik sie nie otworzyl" << endl;
	}
}

void Mikser2::write(string fname) {
	ofstream f(fname);
	if(f.is_open()) {
		lsString::iterator it = begin();
		while(it != end()) {
			write_set(f, it);
			it++;
		}
		f << "Wczytanych setow: " << endl;
		f.close();
	} else {
		cout << "Plik sie nie otworzyl" << endl;
	}
}

void Mikser2::write_set(ofstream& f, lsString::iterator it ) {
	set<string>::iterator sit_start= (*it).begin();
	set<string>::iterator sit_end= (*it).end();
	while(sit_start != sit_end) {
		f << *sit_start << " ";
		sit_start++;
	}
	f << endl;
}

int main() {
	domieszka<Mikser2> m;
	m.open("quovadis.txt");
	m.execute();
	m.write("wynik.txt");

	return 0;
}