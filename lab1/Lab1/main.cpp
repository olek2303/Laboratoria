#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <fstream>
#include <ctime>

using namespace std;

struct Dane {
	int id;
	char nazwa[10];
	double temp;
	double pojemn;
	friend ostream& operator<< (ostream& b, const Dane t) {
		b.width(6);
		b.fill('0');
		b << t.id;
		b.fill(' ');
		b.width(10);
		b.setf(ios::left);
		b << t.nazwa;
		b.unsetf(ios::left);
		b.width(7);
		b.setf(ios::right);
		b.precision(3);
		b << t.temp;
		b.width(6);
		b.precision(1);
		b << t.pojemn;
		b << endl;
		return b;
	}
	Dane& operator+= (const Dane& t) {
		id = 0;
		strcpy(nazwa, " ");
		temp += t.temp;
		pojemn += t.pojemn;
		return *this;
	}
	bool& operator==(const Dane& d) {
		bool same = 0;
		if (id == d.id && strcmp(nazwa, d.nazwa) && temp == d.temp && pojemn == d.pojemn)
			same = 1;
		return same;
	}
};

template <typename T, int rozmiar>
class Tablica {
public:
	T A[rozmiar];
	T& operator[](int index);
	T put(T* d);	
	T get(T* d);
};

template <typename T, int rozmiar>
T& Tablica<T, rozmiar>::operator[](int index)
{
	if (index >= rozmiar || index < 0)
		return A[0];
	else
		return A[index];
}

template <typename T, int rozmiar>
T Tablica<T, rozmiar>::put(T* d) {

	return d;
}

template <typename T, int rozmiar>
T Tablica<T, rozmiar>::get(T* d) {
	int k = -1;
	for (int i = 0; i < rozmiar; i++) {
		if (A[i] == d) {
			k = i;
			break;
		}
	}
	if (k != -1) {
		A[k].id = 0; // wyzerowanie obiektu do usuniecia
		strcpy(A[k].nazwa, " ");
		A[k].temp = 0.0;
		A[k].pojemn = 0.0;
	}

	return d; // zwracanie obiektu do usuniecia z danymi 
}


void raport(Tablica<Dane, 5>& t, char nazwa[20]) {
	ofstream f;
	f.open(nazwa, ios::app);
	if (f.is_open()) {
		//naglowek
		time_t rawtime;
		time(&rawtime);
		f.width(40);
		f.setf(ios::right);
		f << ctime(&rawtime) << endl;
		f.unsetf(ios::right);
		f.setf(ios::left);
		f << "DELL 17" << endl;
		f.unsetf(ios::left);
		f.width(35); 
		f << f.fill('-');
		f << endl;
		f.fill(' ');
		f.width(6);
		f << internal << "ID";
		f.width(10);
		f << internal << "NAZWA";
		f.width(7);
		f << internal << "TEMP";
		f.width(8);
		f << internal << "POJEMN"; 
		f << endl ;
		f.width(35);
		f << f.fill('-');
		f << endl;
		//dane
		for (int i = 0; i < 5; i++) {
			f << t.A[i];
		}
		//stopka
		f.width(35);
		f << f.fill('-');
		f << endl;
		Tablica<Dane,2> suma;
		suma.A[0].temp = 0.0;
		suma.A[0].pojemn = 0.0;
		for (int i = 0; i < 5; i++) {
			suma.A[0] += t.A[i];
		}
		f.width(6);
		f.fill('0');
		f << suma.A[0].id;
		f.fill(' ');
		f.width(10);
		f.setf(ios::left);
		f << suma.A[0].nazwa;
		f.unsetf(ios::left);
		f.setf(ios::right);
		f.width(7);
		f.precision(3);
		f << suma.A[0].temp;
		f.width(6);
		f.precision(2);
		f << suma.A[0].pojemn;
		f << endl;
		f << endl;
	}
	f.close();
}

int main() {

	Tablica<Dane,5> t1;
	for (int i = 0; i < 5; i++) {
		t1[i].id = i;
		strcpy(t1[i].nazwa, "nazwa");
		t1[i].temp = (double)i + 10.12352;
		t1[i].pojemn = (double)i + 5.3;
	}

	char nazwa[20] = "test.txt";
	raport(t1, nazwa); // tworzy plik

	Dane* dd = (Dane*)malloc(sizeof(Dane));
	dd->id = 5;
	strcpy(dd->nazwa, "nowy");
	dd->temp = 10.5;
	dd->pojemn = 18.5;

	t1.put(dd);



	return 0;
} 