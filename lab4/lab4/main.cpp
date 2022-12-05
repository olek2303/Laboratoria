#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<exception>
#include <iomanip>

using namespace std;

class _Bazowe_Cechy {
public:
	// pola statyczne sta³e - dla sta³ych wartoœci ca³kowitych
	static const bool _jest_liczba = false;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const bool _musi_byc_l_parz = false; // dodana cecha
	static const bool _czy_pierwsza = false; // dodoana cecha
};

template<typename T>
class _Cechy : public _Bazowe_Cechy {
public:
	// metody statyczne - dla wartoœci innych typów ni¿ liczby ca³kowite
	static const T _dolna_granica() { return T(); };
	static const T _gorna_granica() { return T(); };
	static const int _il_miejsc_po_przecinku = 0; // dodana cecha
	static const bool _ma_okreslona_wielokrotnosc = false; // dodana cecha
};

template<typename T>
class Cechy : public _Cechy<T> {
};

class przyspieszenie {
	double a;
public:
	przyspieszenie(double acc = 0) : a(acc) {};
	double operator()() const { return a; };
	przyspieszenie& operator=(double acc) { a = acc; return *this; };
	bool operator<(const przyspieszenie& p) const { return (a < p.a); };
	friend ostream& operator<<(ostream& os, const przyspieszenie&);
};
ostream& operator<<(ostream& os, const przyspieszenie& p) { return os << p.a; };

template<>
class Cechy<przyspieszenie> : public _Cechy<przyspieszenie> {
public:
	static const bool _jest_liczba = true;
};

class temperatura_wody {
	double t;
public:
	temperatura_wody(double temp = 50) : t(temp) {};
	double operator()() const { return t; };
	temperatura_wody& operator=(double temp) { t = temp; return *this; };
	bool operator<(const temperatura_wody& tw) const { return (t < tw.t); };
	friend ostream& operator<<(ostream& os, const temperatura_wody&);
};
ostream& operator<<(ostream& os, const temperatura_wody& tw) { return os << tw.t; };

template<>
class Cechy<temperatura_wody> : public _Cechy<temperatura_wody> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const temperatura_wody _dolna_granica() { return temperatura_wody(0); };
	static const temperatura_wody _gorna_granica() { return temperatura_wody(100); };
};

class kostka_do_gry {
	int n;
public:
	kostka_do_gry(int num = 1) : n(num) {};
	int operator()() const { return n; };
	kostka_do_gry& operator=(int num) { n = num; return *this; };
	bool operator<(const kostka_do_gry& k) const { return (n < k.n); };
	friend ostream& operator<<(ostream& os, const kostka_do_gry&);
};
ostream& operator<<(ostream& os, const kostka_do_gry& k) { return os << k.n; };

template<>
class Cechy<kostka_do_gry> : public _Cechy<kostka_do_gry> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const kostka_do_gry _dolna_granica() { return kostka_do_gry(1); };
	static const kostka_do_gry _gorna_granica() { return kostka_do_gry(6); };
};


// klasy dodane
class minuta_dnia {
	int n;
public:
	minuta_dnia(int minuta = 1) : n(minuta) {};
	int operator()() const { return n; };
	minuta_dnia& operator=(int minuta) { n = minuta; return *this; };
	bool operator<(const minuta_dnia& k) const { return (n < k.n); };
	friend ostream& operator<<(ostream& os, const minuta_dnia&);
};
template<>
class Cechy<minuta_dnia> : public _Cechy<minuta_dnia> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const minuta_dnia _dolna_granica() { return minuta_dnia(1); };
	static const minuta_dnia _gorna_granica() { return minuta_dnia(1440); } // tyle minut ma doba
};
ostream& operator<<(ostream& os, const minuta_dnia& k) { // // korzysta z cechy _jest_liczba_calkowita
	if (Cechy<minuta_dnia>::_jest_liczba_calkowita)
		return os << k.n;
	else {
		os.precision(Cechy<minuta_dnia>::_il_miejsc_po_przecinku);
		return os << k.n;
	}
};

class liczba_sekund {
	int l; // laczny czas uderzenia: 0,8s + 1,2s = 2s
public:
	liczba_sekund(int sek = 0) : l(sek) {};
	int operator()() const { return l; };
	liczba_sekund& operator=(int sek) { l = sek; return *this; };
	bool operator<(const liczba_sekund& k) const { return (l < k.l); };
	friend ostream& operator<<(ostream& os, const liczba_sekund&);
};
template<>
class Cechy<liczba_sekund> : public _Cechy<liczba_sekund> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const liczba_sekund _dolna_granica() { return liczba_sekund(0); }; // 00:00 - najmniejsza ilosc uderzen
	static const liczba_sekund _gorna_granica() { return liczba_sekund(82 * 2); } // 23:59 - najwieksza ilosc uderzen;
	static const bool _musi_byc_l_parz = true;
};
ostream& operator<<(ostream& os, const liczba_sekund& k) { // korzysta z cechy _jest_liczba_calkowita
	if (Cechy<liczba_sekund>::_jest_liczba_calkowita)
		return os << k.l;
	else {
		os.precision(Cechy<liczba_sekund>::_il_miejsc_po_przecinku);
		return os << k.l;
	}
};

class il_piwa {
	double l;
public:
	il_piwa(double il = 1) : l(il) {};
	double operator()() const { return l; };
	il_piwa& operator=(double il) { l = il; return *this; };
	bool operator<(const il_piwa& k) const { return (l < k.l); };
	friend ostream& operator<<(ostream& os, const il_piwa&);
};
template<>
class Cechy<il_piwa> : public _Cechy<il_piwa> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const il_piwa _dolna_granica() { return il_piwa(0.568); };
	static const il_piwa _gorna_granica() { return il_piwa(INT_MAX); };
	static const int _il_miejsc_po_przecinku = 5;
	static const bool _ma_okreslona_wielokrotnosc = true; // dotyczy tylko pinty piwa
};
ostream& operator<<(ostream& os, const il_piwa& k) { // // korzysta z cechy _jest_liczba_calkowita
	if (Cechy<il_piwa>::_jest_liczba_calkowita)
		return os << k.l;
	else {
		os.precision(Cechy<il_piwa>::_il_miejsc_po_przecinku);
		return os << k.l;
	}
};

class liczb_pierw {
	int l;
public:
	liczb_pierw(int il = 1) : l(il) {};
	int operator()() const { return l; };
	liczb_pierw& operator=(int il) { l = il; return *this; };
	bool operator<(const liczb_pierw& k) const { return (l < k.l); };
	friend ostream& operator<<(ostream& os, const liczb_pierw&);
};
template<>
class Cechy<liczb_pierw> : public _Cechy<liczb_pierw> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const liczb_pierw _dolna_granica() { return liczb_pierw(2); };
	static const liczb_pierw _gorna_granica() { return liczb_pierw(INT_MAX); };
	static const int il_miejsc_po_przec = 0;
	static const bool _czy_pierwsza = true;
};
ostream& operator<<(ostream& os, const liczb_pierw& k) { // // korzysta z cechy _jest_liczba_calkowita
	if (Cechy<liczb_pierw>::_jest_liczba_calkowita)
		return os << k.l;
	else {
		os.precision(Cechy<liczb_pierw>::_il_miejsc_po_przecinku);
		return os << k.l;
	}
};




class Przepelnienie : public exception {
	char opis[100];
public:
	Przepelnienie(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};
class BrakDanych : public exception {
	char opis[100];
public:
	BrakDanych(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};

template<typename T, int rozmiar, typename CechyT = Cechy<T>>
class SzablonStosu {
	T stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	SzablonStosu() : top(0) {}
	void push(const T& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	void push(int i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja wartoœci przekazanej do zapisu
		if (CechyT::_jest_liczba && CechyT::_jest_liczba_calkowita) {
			if (CechyT::_nalezy_do_przedzialu) {
				if (!(T(i) < CechyT::_dolna_granica()) && !(CechyT::_gorna_granica() < T(i))) {
					if (CechyT::_musi_byc_l_parz) { // dodana cecha sprawdzajaca czy liczba musi byc parzysta
						if (i % 2 == 0)
							stos[top++] = i;
					}
					else if (CechyT::_czy_pierwsza) { // dodana cecha sprawdza czy liczba zadeklarowana jako parzysta jest parzysta
						bool nie_pierw = false;
						for (int n = 2; n * n <= i; n++)
							if (i % n == 0)
								nie_pierw = true; // nie jest to liczba parzysta, poniewaz ma dzielnik
						if (nie_pierw == false)
							stos[top++] = i;
					}
					else {
						stos[top++] = i;
					}
				} 
			}
			else
				stos[top++] = i;
		}
	}
	void push(double i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja wartoœci przekazanej do zapisu
		if (CechyT::_jest_liczba && !CechyT::_jest_liczba_calkowita) {
			if (CechyT::_nalezy_do_przedzialu) {
				if (!(T(i) < CechyT::_dolna_granica()) && !(CechyT::_gorna_granica() < T(i))) {
					if (CechyT::_ma_okreslona_wielokrotnosc) { // dotyczy tylko piwa
						int liczba = toupper(i / 0.568);
						if (abs(i / 0.568) < (double)liczba+0.001) { // 0.568 - tyle ml ma jedna pinta
							stos[top++] = i;
						}
					} else {
						stos[top++] = i;
					}
				}
			}
			else
				stos[top++] = i;
		}
	}
	T pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());

		return stos[--top];
	}
	template<typename U1, int r, typename U2>
	friend ostream& operator<<(ostream& os, const SzablonStosu<U1, r, U2>&);
};
template<typename U1, int r, typename U2>
ostream& operator<<(ostream& os, const SzablonStosu<U1, r, U2>& S)
{
	for (int i = 0; i < S.top; i++) cout << S.stos[i] << endl;
	return os;
};

//dolaczona klasa - poziom 2

class Stos2 {
	static const int rozmiar = 10;
protected:
	double stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	Stos2() : top(0) {}
	virtual void push(const double& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	virtual double pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		return stos[--top];
	}
	int getRozm() { return rozmiar; }
};

template<typename T>
class pierwsza : public T {
public:
	virtual double pop() {
		if (T::top == 0)
			throw BrakDanych(typeid(T::stos[0]).name());
		cout << "Aktualna ilosc elementow: " << T::zajetosc() << endl;
		double zm_usuw = T::pop();
		cout << "Element usuniety: " << zm_usuw << endl;
		return zm_usuw;
	}
};

template<typename T>
class druga : public T {
	double suma = 0;
public:
	virtual void push(const double& i) {
		if (T::top == T::getRozm())
			throw Przepelnienie(typeid(i).name());
		T::stos[T::top++] = i;
		suma += i;
		cout << "Aktualna suma po dodaniu elementu " << i << " to: " << suma << endl;
	}
	virtual double pop() {
		if (T::top == 0)
			throw BrakDanych(typeid(T::stos[0]).name());
		double usuw = T::pop();
		suma -= usuw;
		cout << "Aktualna suma po usunieciu elementu " << usuw << " to: " << suma << endl;
	}
};


int main() {
	/*
	SzablonStosu<minuta_dnia, 5> K1;
	SzablonStosu<liczba_sekund, 10> K2;
	SzablonStosu<il_piwa, 10> K3;
	SzablonStosu<liczb_pierw, 10> K4;

	cout << "Dane wpisane do K1(minuta dnia): " << endl;
	K1.push(10); //powinno wejsc
	K1.push(-1); //nie powinno wejsc
	K1.push(2000);  // nie powinno wejsc, poza limitem
	cout << "Zajetosc K1: " << K1.zajetosc() << "\t zawartosc: \n" << K1 << endl;

	cout << "Dane wpisane do K2(liczba sekund): " << endl;
	K2.push(3); // nie powinno wejsc, liczba nieparzysta
	K2.push(4); // powinno wejsc
	K2.push(100); // powinno wejsc
	cout << "Zajetosc K2: " << K2.zajetosc() << "\t zawartosc: \n" << K2 << endl;

	cout << "Dane wpisane do K3(ilosc piwa w litrach): " << endl;
	K3.push(0.568); // powinno wejsc
	K3.push(1.0); // niepowinno wejsc, nie jest wielokrotnoscia
	K3.push(1.704); // powinno wejsc
	K3.push(1.136); // powinno wejsc
	cout << "Zajetosc K3: " << K3.zajetosc() << "\t zawartosc: \n" << K3 << endl;

	cout << "Dane wpisane do K4(liczba pierwsza): " << endl;
	K4.push(2); // powinno wejsc
	K4.push(4); // nie powinno wejsc, nie jest liczba pierwsza
	K4.push(17);
	cout << "Zajetosc K4: " << K4.zajetosc() << "\t zawartosc: \n" << K4 << endl;

	// opró¿nianie stosów
	cout << "Oproznianie stosow: " << endl;
	try {
		while (true)
			K1.pop();
	}
	catch (BrakDanych& e) {
		cout << "K1 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K2.pop();
	}
	catch (BrakDanych& e) {
		cout << "K2 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K3.pop();
	}
	catch (BrakDanych& e) {
		cout << "K3 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K4.pop();
	}
	catch (BrakDanych& e) {
		cout << "K4 pusty: " << e.what() << endl;
	}
	*/

	cout << "Poziom 2: " << endl;
	pierwsza<Stos2> KK;
	cout << "DOMIESZKA JEDEN: " << endl;
	KK.push(1);
	KK.push(3);
	KK.push(5);
	KK.push(6);
	KK.push(13);
	KK.push(9);

	KK.pop();
	KK.pop();
	KK.pop();
	cout << endl;

	druga<Stos2> d;
	cout << "Domieszka DWA: " << endl;
	d.push(1); 
	d.push(3);
	d.push(5);
	d.push(6);
	d.push(13);
	d.push(9);

	d.pop();
	d.pop();
	d.pop();
	cout << endl;

	druga<pierwsza<Stos2>> KKK;
	cout << "DOMIESZKA JEDEN I DWA: " << endl;
	KKK.push(1);
	KKK.push(3);
	KKK.push(5);
	KKK.push(6);
	KKK.push(13);
	KKK.push(9);

	KKK.pop();
	KKK.pop();
	KKK.pop();
	cout << endl;


	system("pause");
	return 0;
}