#ifndef __BIGNUM_H_
#define __BIGNUM_H_

#include "Stack.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdint.h>

using namespace std;

struct BigInt {
	vector<uint8_t> digits;
	short sign = 0;
};


istream& operator >> (istream& cin, BigInt& number);
ostream& operator << (ostream& cout, const BigInt& a);
void add_zero(BigInt& a, int sz);
void change(BigInt& a, BigInt& b);
void del_zero(BigInt& a);
void ConvertIntToBigInt(int a, BigInt& b);
bool operator < (BigInt a, BigInt b);
bool operator <= (BigInt a, BigInt b);
bool operator == (BigInt a, BigInt b);
bool operator < (BigInt a, int b);
bool operator <= (BigInt a, int b);
bool operator == (BigInt a, int b);
BigInt operator+ (BigInt a, BigInt b);
BigInt operator- (BigInt a, BigInt b);
BigInt operator* (BigInt a, BigInt b);
BigInt operator/ (BigInt a, BigInt b);
BigInt operator* (BigInt a, int b);
BigInt operator/ (BigInt a, int b);

#endif // !__BIGNUM_H_
/*
		3 x 3
		3 + 6 
*/