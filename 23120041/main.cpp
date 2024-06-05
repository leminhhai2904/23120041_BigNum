#include "BigNum.h"
#include "StackAndQueue.h"
#include "ReadAndWriteFile.h"

int main() {
	string filenameInput = "./Resource/input.txt";
	string filenameOutput = "./Resource/output.txt";
	ReadAndWriteFile(filenameInput, filenameOutput);
	return 0;
}

/*
(5-2)*3
800 / 4 + 20
((-5 + (89 * 6) - 36) * (55 + 5) + 33) * 4 - 10
-9 + 21 / 2 * 8 + 4
*/