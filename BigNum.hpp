#include <vector>
#include <iostream>
#include <string>

using namespace std;

class bignum {
public:
	typedef int lnum[64];\
public:
	lnum num = {};

	bignum() {
		lnum num = {};
	}
	
	bignum(string number, int size) {
		for (int i = 0; i < size; i++) {
			num[64 - size + i] = number[i] - '0';
		}
		
	}

	void print(int precision=2) {
		int foundNumber = 0;
		int numberPos;
		string eNotation = "";
		for (int i = 0; i < 64; i++) {
			if (num[i] != 0) {
				foundNumber = 1;
				numberPos = i;
				cout << numberPos << '\n';
				break;
			}
		}
		
		if (foundNumber) {
			eNotation = eNotation + to_string(num[numberPos]) + '.';
			for (int i = numberPos + 1; i < numberPos + precision + 1 && i < 64; i++) {
				eNotation = eNotation + to_string(num[i]);
			}
			eNotation += 'e' + to_string(64 - numberPos - 1);
		}
		else {
			cout << 0 << '\n';

		}
		cout << eNotation << '\n';
	}

	void printNum() {
		int foundNumber = 0;
		for (int i = 0; i < 64; i++) {
			if (foundNumber) {
				cout << num[i];
			}
			else if (num[i] != 0) {
				foundNumber = 1;
				cout << num[i];
			}
		}
		cout << '\n';
	}

};



