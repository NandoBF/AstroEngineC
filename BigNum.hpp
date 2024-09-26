#include <vector>
#include <iostream>
#include <string>

using namespace std;

class bignum {
public:
	typedef int lnum[64];\
public:
	lnum num = {};
	int number_end=63;

	bignum() {
		lnum num = {};
	}
	
	bignum(string number, int size) {
		number_end = 64 - size;
		for (int i = 0; i < size; i++) {
			num[64 - size + i] = number[i] - '0';
		}
		
	}
	bignum(const bignum& b) {
		for (int i = 0; i < 64; i++) {
			num[i] = b.num[i];
		}
	}
			

	bignum& operator+(bignum& b) {
		int over = 0, smallest = 0;
		if (number_end < b.number_end) smallest = number_end; else smallest = b.number_end;
		for (int i = 63; i > smallest; i--) {
			int sum = num[i] + b.num[i] + over;
			num[i] = sum % 10;
			over = sum / 10;
			if (i == smallest && over != 0) {
				number_end = smallest + 1;
			}
		} 
		return *this;
	}

	bignum& operator+(int a) {
		int over = 0;
		string ch = to_string(a);
		int j = ch.size() - 1;
		for (int i = 63; i > number_end && j >= 0; i--, j--) {
			int sum = num[i] + (ch[j] - '0');
			num[i] = sum % 10;
			over = sum / 10;
			if (i == number_end && over != 0) number_end++;
		}
		if (64 - number_end < ch.size()) number_end = ch.size();

		return *this;
	}

	void update() {
	}

	int size() {
		return 64 - number_end;
	}

	void print(int precision=2) {
		int foundNumber = 0;
		string eNotation = "";
		eNotation = eNotation + to_string(num[number_end]) + '.';
		for (int i = number_end + 1; i < number_end + 1 + precision && i < 64; i++) {
			eNotation = eNotation + to_string(num[i]);
		}
		eNotation += 'e' + to_string(64 - number_end - 1);
		cout << eNotation << '\n';
	}

	void printNum() {
		for (int i = number_end; i < 64; i++) {
			cout << to_string(num[i]);
		}
		cout << '\n';
	}

};



