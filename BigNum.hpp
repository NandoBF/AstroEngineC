#include <vector>
#include <iostream>

using namespace std;

class bignum {
public:
	typedef int lnum[64];\
public:
	lnum num = {};

	bignum() {
		lnum num = {};
	}
	
	bignum(char number[], int size) {
		for (int i = 0; i < size; i++) {
			num[64 - size + i] = number[i] - '0';
		}
		
	}

	void print() {
		return;
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
	}

};



