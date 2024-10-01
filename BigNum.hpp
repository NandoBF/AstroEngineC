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

	bignum(int n) {
		string number = to_string(n);
		for (int i = number.size() - 1; i >= 0; i++) {
			num[i] = number[i];
		}
	}

	bignum(string number) {
		int size = number.size();
		for (int i = 0; number[i]; i++) {
			num[64 - size + i] = number[i] - '0';
		}
		updateEnd();
		
	}

	bignum(const bignum& b) {
		for (int i = 0; i < 64; i++) {
			num[i] = b.num[i];
		}
		updateEnd();
	}

	bignum(const lnum num1) {
		for (int i = 0; i < 64; i++) {
			num[i] = num1[i];
		}
		updateEnd();
	}
			
	void updateEnd() {
		for (int i = 0; i < 64; i++) {
			if (num[i] != 0) {
				number_end = i;
				break;
			}
		}
	}

	bignum& operator=(const string b) {
		int size = b.size();
		int i = size - 1;
		lnum temp = {};
		for (; b[i] != 'e'; i--);
		i--;
		cout << i << '\n';
		for (; i >= 0; i--) {
			temp[i] = b[i];
		}
		bignum newbig(temp);
		return newbig;
	}

	bignum operator+(bignum& b) {
		int smallest = 0;
		int over = 0;
		lnum temp = {};
		if (number_end < b.number_end) smallest = number_end; else smallest = b.number_end;
		for (int i = 63; i >= smallest; i--) {
			int sum = num[i] + b.num[i] + over;
			temp[i] = sum % 10;
			over = sum / 10;
		}
		bignum newbig(temp);
		return newbig;
	}
	bignum operator+(int a) {
		string ch = to_string(a);
		int j = ch.size() - 1;
		int over = 0;
		lnum temp = {};
		for (int i = 63; i >= 0; i--, j--) {
			int to_int = 0;
			if (j >= 0) to_int = ch[j] - '0';
			int sum = num[i] + to_int + over;
			temp[i] = sum % 10;
			over = sum / 10;
		}
		bignum newbig(temp);
		return newbig;
	}

	bignum& operator+=(bignum& b) {
		int smallest = 0;
		int over = 0;
		if (number_end < b.number_end) smallest = number_end; else smallest = b.number_end;
		for (int i = 63; i >= smallest; i--) {
			int sum = num[i] + b.num[i] + over;
			num[i] = sum % 10;
			over = sum / 10;
		}
		if(b.number_end <= number_end) updateEnd();
		return *this;
	}
	bignum& operator+=(int a) {
		string ch = to_string(a);
		int j = ch.size() - 1;
		int over = 0;
		for (int i = 63; i > number_end && j > -2; i--, j--) {
			int to_int = 0;
			if (j >= 0) to_int = ch[j] - '0';
			int sum = num[i] + to_int + over;
			num[i] = sum % 10;
			over = sum / 10;
		}
		if(ch.size() >= (64 - number_end)) updateEnd();
		return *this;
	}

	bignum operator*(bignum& b) {
		int over = 0;
		lnum temp = {};
		for (int i = 63; i >= b.number_end || over != 0; i--) {
			int sum = 0;
			for (int j = 63; j >= number_end || over != 0; j--) {
				sum = num[j] * b.num[i] + over;
				temp[i - (63 - j)] += sum % 10;
				over = sum / 10;
				temp[i - (63 - j)] = temp[i - (63 - j)] % 10;
				over += temp[i - (63 - j)] / 10;
			}
		}
		bignum newbig(temp);
		return newbig;
	}

	int size() {
		return 64 - number_end;
	}

	void print(int precision=2) {
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

	void printAll() {
		for (int i = 0; i < 64; i++) {
			cout << num[i];
		}
		cout << '\n';
	}

	int check_mistakes() {
		for (int i = 0; i < 64; i++) {
			if (num[i] > 9) {
				return 1;
			}
		}
		return 0;
	}
};



