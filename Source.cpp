#include <iostream>
#include "Header.h"

using namespace std;

void main() {
	string Inp = "-";
	while (Inp != "0") {
		cout << "Type what do you need!" << endl;
		cout << "Five11" << endl;
		cout << "Task 2" << endl;
		cout << "-> ";
		cin >> Inp;
		if (Inp == "1") {
			Five11();
		}
		else if (Inp == "2") {
			Task2();
		}
		else if (Inp != "0") {
			cout << "Error with input! Try again!" << endl;
		}
	}
}