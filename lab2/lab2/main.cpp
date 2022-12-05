#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class MyError {
public:
	string opis;
	int linia;
	MyError() : opis(""), linia(-1) { }
	MyError(string o) : opis(o), linia(-1) { }
	MyError(string o, int l) : opis(o), linia(l) { }
	~MyError() { }
	virtual void what() {
		cout << "ERROR: ";
		cout << opis << endl;
		if (linia != -1) {
			cout << "linia - " << linia << endl;
		}
	}
};

class FileError : public MyError {
public:
	string opis;
	explicit FileError(string o) : opis(o) { };
	void what() { 
		cout << "ERROR: ";
		cout << opis << endl;
	}
}; 

class CaseError : public MyError {
public:
	string opis;
	int linia;
	explicit CaseError(string o, int l) : opis(o), linia(l) { };
	void what() {
		cout << "ERROR: ";
		cout << opis << endl;
		cout << "Linia: " << linia << endl;
	}
};

void sprawdzPlik(ifstream& f) {
	try {
		bool tableflag = 0;
		bool trflag = 0;
		int counter = 1;
		if (!f.is_open()) {
			throw FileError("Blad przy otwieraniu pliku");
		}
		string linia;
		while (!f.eof()) {
			getline(f, linia, '\n');
			//cout << linia << endl;
			if (linia.find("<TABLE>") < 100) {
				if (tableflag == 1) {
					throw MyError("Brak klamry konczacej TABLE przed rozpoczeciem nowej TABLE", counter);
				}
				tableflag = 1;
			}
			else if (linia.find("<TR>") < 100) {
				if (trflag == 1) {
					throw MyError("Brak klamry konczacej TR przed rozpoczynajaca nowe TR", counter);
				}
				trflag = 1;
			}
			else if (linia.find("</TABLE>") < 100) {
				tableflag = 0;
			}
			else if (linia.find("</TR>") < 100 ) {
				trflag = 0;
			}
			else {
				if (linia.find("<CAPTION>") < 100) {
					size_t pos = linia.find("</CAPTION>");
					size_t pos1 = linia.find("<CAPTION>");
					if (pos > 100 || pos1 > 100) {
						throw MyError("Brak klamry konczoncej dla znacznika <CAPTION>", counter);
					}
				}
				else if (linia.find("<TD>") < 100) {
					size_t pos = linia.find("<TD>");
					size_t pos1 = linia.find("</TD>");
					if (pos > 100 || pos1 > 100) {
						throw MyError("Brak klamry konczoncej dla znacznika <TD>", counter);
					}
				}
				else if (linia.find("<TH>") < 100) {
					size_t pos = linia.find("<TH>");
					size_t pos1 = linia.find("</TH>");
					if (pos > 100 || pos1 > 100) {
						throw MyError("Brak klamry konczoncej dla znacznika <TH>", counter);
					}
				}
				else {
					throw CaseError("Blad przy pisowni klamry", counter);
				}
			}
			counter++;
		}
	}
	catch (MyError& r) {
		r.what();
		cout << "Typ: " << typeid(r).name() << endl;
		throw;
	}
}

int main() {
	ifstream f;
	f.open("plik.txt");
	try {
		sprawdzPlik(f);
	}
	catch (FileError& r) {
		cout << "FileError - ";
		r.what();
	}
	catch (CaseError& r) {
		cout << "CaseError - ";
		r.what();
	}
	catch (MyError& r) {
		cout << "MyError - ";
		r.what();
	}

	f.close();

	return 0;
}