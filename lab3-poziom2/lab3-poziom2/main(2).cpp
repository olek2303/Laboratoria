#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

double randdouble() {
	int number = rand() % 10;
	return (double)number + (rand() / (double(RAND_MAX) + 1));
}

template<typename T>
class node {
public:
	T dane;
	node<T>* nast;
	node() { dane = NULL; nast = NULL; }
	node(T d, node<T>* n) { dane = d; nast = n; }
};

template<typename T>
class Konten {
	node<T>* head;
	node<T>* tail;
public:
	Konten() { head = tail = NULL; }
	void push(T i);
	void pokaz();
	class iterator {
		node<T>* curr;
	public:
		iterator(node<T>* is) : curr(is) { };
		iterator operator++() { // Prefix
			if (curr)
				curr = curr->nast;
			return *this;
		};
		iterator operator++(int) { // Postfix
			iterator it = *this;
			++* this;
			return *this;
		};
		T operator*() const { return curr->dane; };
		iterator& operator=(const iterator& rv) {
			curr = rv.curr;
			return *this;
		}
		iterator& operator=(T d) {
			curr->dane = d;
			return *this;
		}
		bool operator==(const iterator& rv) const { return curr == rv.curr; }
		bool operator!=(const iterator& rv) const { return curr != rv.curr; }

	};
	iterator begin() { return iterator(head); };
	iterator end() { return iterator(tail->nast); };
	friend class iterator;
};

template<typename T>
class kalkulator {
public:
	static double MaxObjetoscChmury(
		typename Konten<Konten<T>>::iterator& pierwszy,
		typename Konten<Konten<T>>::iterator& drugi) {




	}
};

template<typename T>
void Konten<T>::push(T i) {
	if (head == NULL) {
		head = tail = new node<T>();
		tail->dane = i;
		tail->nast = NULL;
	}
	else {
		tail->nast = new node<T>();
		tail->nast->dane = i;
		tail = tail->nast;
		tail->nast = NULL;
	}
}

template<typename T>
void Konten<T>::pokaz() {
	node<T>* wsk = head;
	while (wsk != NULL) {
		cout << wsk->dane << " ";
		wsk = wsk->nast;
	}
	cout << endl;
}

template<typename T>
void transformuj(T i1, T i2, T i3) {
	while (i1 != i2) {
		if (*i1 < *i3) {
			double pom = *i1;
			i1 = *i3;
			i3 = pom;
		}
		i1++;
		i3++;
	}
}

template<typename T>
void roznicuj(T i1, T i2, T i3) {
	while (i1 != i2) {
		i1 = *i1 - *i3;
		i1++;
		i3++;
	}
}

template<typename T, typename U>
U objetosc(T i1, T i2, U& a) {
	while (i1 != i2) {
		a = a * (*i1);
		i1++;
	}
	return a;
}

void algorytm() {
	Konten<double> p, q;
	Konten<double>::iterator itp(p.begin());
	for (int i = 0; i < 5; i++) {
		p.push(randdouble());
		q.push(randdouble());
	}
	itp = p.begin();

	cout << "P: ";
	p.pokaz();
	cout << "Q: ";
	q.pokaz();

	cout << endl;
	cout << "TRANSFORMUJ" << endl;
	transformuj(p.begin(), p.end(), q.begin());
	cout << "Po zamianie P: ";
	p.pokaz();
	cout << "Po zamianie Q: ";
	q.pokaz();
	cout << "ROZNICUJ" << endl;
	roznicuj(p.begin(), p.end(), q.begin());
	cout << "Po zamianie P: ";
	p.pokaz();

	double a = 1;
	a = objetosc(p.begin(), p.end(), a);
	cout << "Objetosc: " << a << endl;
}

int main() {
	srand(unsigned(time(NULL)));
	//algorytm();


	cout << endl;
	Konten<double> t[6];
	//Konten<Konten<double>> t;
	for (int i = 0; i < 6; i++) {
		//Konten<double> t1;
		for (int j = 0; j < 6; j++) {
			t[i].push(randdouble());
		}
		cout << i << ": ";
		t[i].pokaz();
		//t.push(t1);
	}

	//kalkulator<double>::MaxObjetoscChmury(t.begin(), t.end());

	return 0;
}