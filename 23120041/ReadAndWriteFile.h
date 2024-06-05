#ifndef __READWRITEFILE_H_
#define __READWRITEFILE_H_

#include "BigNum.h"
#include "StackAndQueue.h"
#include "ReadAndWriteFile.h"

void ReadAndWriteFile(string filenameInput, string filenameOutput);
bool isOperator(char x);
void InfixToPostfix(string line, Stack& st, Queue& q);
BigInt CalculatePostfix(Queue q);
void PrintQueue(const Queue& q);
bool checkLine(string line);
int checkDivideZero(const Queue& q);
bool checkExpression(const Queue& q, int checkDivideZero);

#endif // !__READWRITEFILE_H_
