#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <random>

using namespace std;

void DInicMatrix(string**& a, int& m, int& n) {
	a = new string* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new string[m];
	}
}

void DelMatrix(string**& a, int n) {
	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[]a;
}

int mini(int a, int b) {
	if (a > b) return b;
	return a;
}

bool IsBigger(string a, string b) {
	int lenmin = mini(a.length(), b.length());
	int i = 0;
	while (a[i] == b[i] && i < lenmin) i++;
	if (i == lenmin) return false;
	if ((int)a[i] > (int)b[i]) return true;
	else return false;
}

bool IsLower(string a, string b) {
	int lenmin = mini(a.length(), b.length());
	int i = 0;
	while (a[i] == b[i] && i < lenmin) i++;
	if (i == lenmin) return false;
	if ((int)a[i] < (int)b[i]) return true;
	else return false;
}

void DoubleSwap(string Names[], int Reult[], int i, int j) {
	string Buff1 = Names[i];
	int Buff2 = Reult[i];
	Names[i] = Names[j];
	Reult[i] = Reult[j];
	Names[j] = Buff1;
	Reult[j] = Buff2;
}

void Qsortstring(string Names[], int Reult[], int L, int R)
{
	int i = L, j = R;
	string w, x;
	x = Names[(L + R) / 2];
	do
	{
		while (IsLower(Names[i], x)) i++;
		while (IsBigger(Names[j], x)) j--;
		if (i <= j)
		{
			DoubleSwap(Names, Reult, i, j);
			i++; j--;
		}
	} while (i < j);
	if (L < j) Qsortstring(Names, Reult, L, j);
	if (i < R) Qsortstring(Names, Reult, i, R);
}

void Five11() {
	cout << "Working with file!" << endl;
	ifstream f1;
	f1.open("Results.txt");
	if (f1.is_open()) {
		string line;
		string numb;
		string Names[50];
		int Reult[50];
		int i = -1;
		bool Raz;
		while (getline(f1, line)) {
			i++;
			Names[i] = "";
			numb = "";
			Raz = true;
			for (int j = 0; j < line.length(); j++) {
				if (line[j] != ' ') {
					if (Raz) {
						Names[i] += line[j];
					}
					else {
						numb += line[j];
					}
				}
				else {
					Raz = false;
				}
			}
			Reult[i] = stoi(numb);
		}
		if (i != -1) {
			Qsortstring(Names, Reult, 0, 49);
			ofstream f2;
			f2.open("NewRez.txt");
			for (int i = 0; i < 50; i++) {
				if (Names[i] != "") f2 << Names[i] << setw(18 - Names[i].length()) << Reult[i] << endl;
			}
			f2.close();
		}
		else {
			cout << "File is empty!" << endl;
			f1.close();
		}
	}
	else {
		cout << "File does not exist" << endl;
	}
}

void RandMass(int* a, int N) {
	for (int i = 0; i < N; i++) {
		a[i] = rand() % 100 - 50;
	}
}

void MassOutput(int* a, int N) {
	for (int i = 0; i < N; i++) {
		cout << setw(4) << a[i];
	}
	cout << endl;
}

void IntSwap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

void SortIncert(int*& a, int N) {
	int j, r, d = 0;
	bool Checker = true;
	for (int i = 0; i < N; i++) {
		r = a[i];
		j = i - 1;
		if (r >= 0) {
			while (j >= d && a[j] < r || a[j] < 0 && j >= d /*  || a[j] < 0 && j >= d */) {
				a[j + 1] = a[j];
				j--;
			}
			a[j + 1] = r;
		}
		else {
			while (j >= 0 && a[j] > r || a[j] >= 0 && j >= 0 /*  || a[j] >= 0 && j >= 0 */) {
				a[j + 1] = a[j];
				j--;
			}
			if (a[0] >= 0 && Checker) {
				a[1] = a[0];
				a[0] = r;
				Checker = false;
				d = 1;
			}
			else {
				a[j + 1] = r;
				d++;
			}
		}
	}
}

bool Tester(int* a, int N) {
	bool Beg = false;
	if (N > 0) {
		if (a[0] >= 0) {
			int i = 0;
			while (a[i] >= a[i + 1] && (i < N - 1)) i++;
			if (a[i] >= 0 && a[i + 1] >= 0 && (i < N - 1)) return false;
			while (a[i] <= a[i + 1] && (i < N - 1)) i++;
			if (i != N - 1) return false;
		}
		else {
			int i = 0;
			while (a[i] <= a[i + 1] && (i < N - 1)) i++;
			if (a[i] < 0 && a[i + 1] < 0 && (i < N - 1)) return false;
			while (a[i] >= a[i + 1] && (i < N - 1)) i++;
			if (i != N - 1) return false;
		}
	}
	return true;
}

void Task2() {
	int N, T;
	string tests;
	cout << "Type len of mass that you need!" << endl;
	cout << "-> ";
	cin >> N;
	int* a = new int[N];
	cout << "Type do you need tests! Y/N" << endl;
	cout << "-> ";
	cin >> tests;
	if (tests == "Y" || tests == "y") {
		cout << "How many tests do you need!" << endl;
		cout << "-> ";
		cin >> T;
		srand(time(0));
		for (int i = 0; i < T; i++) {
			RandMass(a, N);
			SortIncert(a, N);
			cout << boolalpha << Tester(a, N) << " - "; 
			MassOutput(a, N);
		}
	}
	else if (tests == "N" || tests == "n") {
		RandMass(a, N);
		MassOutput(a, N);
		SortIncert(a, N);
		MassOutput(a, N);
	}
	delete[]a;
}