#include "BigNum.h"
#include "Stack.h"

int main() {
	/*
	ifstream fi("input.txt");
	ofstream fo("output.txt");
	if (fi.is_open() && fo.is_open()) {
		string line;
		while (!fi.eof())	//khi chưa tới cuối file thì tiếp tục đọc
		{
			getline(fi, line);
			fo << line << endl;
		}
	}
	else {
		cout << "Mo file that bai!";
	}
	*/

	BigInt a, b, c;
	cin >> a;
	cin >> b;
	c = a / b;
	cout << endl;
	cout << a << " / " << b << " = " << c << endl;

	//BigInt a, c;
	//int b;
	//cin >> a >> b;
	//ConvertIntToBigInt(b, c);
	//cout << a << " / " << b << " = " << c << endl;

	//change(a, b);
	//cout << a << endl << b;

	return 0;
}

/*
		123456789
		
*/