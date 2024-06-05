#include "BigNum.h"
#include "StackAndQueue.h"
#include "ReadAndWriteFile.h"

void ReadAndWriteFile(string filenameInput, string filenameOutput) {
	ifstream fi(filenameInput);
	ofstream fo(filenameOutput);
	if (fi.is_open() && fo.is_open()) {
		string line;
		while (!fi.eof())	//khi chưa tới cuối file thì tiếp tục đọc
		{
			Queue q;
			InitQueue(q);
			Stack st;
			InitStack(st);
			getline(fi, line);
			InfixToPostfix(line, st, q);
			if (!checkLine(line)) {
				continue;
			}
			if (!checkExpression(q, checkDivideZero(q))) {
				cout << "Invalid expression\n";
				fo << "Invalid expression\n";
			}
			else {
				//PrintQueue(q);
				BigInt result = CalculatePostfix(q);
				cout << line << " = " << result << endl;
				fo << result << endl;
			}
			
		}
	}
	else {
		cout << "Open file failed!";
	}
}

bool isNumber(char x) {
	if (x >= '0' && x <= '9') {
		return true;
	}
	return false;
}

bool isOperator(char x) {
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')') {
		return true;
	}
	return false;
}

void InfixToPostfix(string line, Stack& st, Queue& q) {
	Data data;
	ResetData(data);
	int flag = 0;
	for (int i = 0; i < line.size(); i++) {
		// Bỏ khoảng trắng
		if (line[i] == ' ')
			continue;

		if (isOperator(line[i])) {
			// Đánh dấu số âm
			if ((i == 0 && line[i] == '-') || (i > 0 && line[i - 1] == '(' && line[i] == '-')) {
				if (flag == 0) {
					flag = 1;
					data.bi.sign = 1;
				}
				else {
					flag = 0;
					data.bi.sign = 0;
				}
				
				continue;
			}
			// Push số vào Queue
			if (data.bi.digits.size() > 0) {
				bool t = Queue_Push(q, data);
				ResetData(data);
				flag = 0;
			}

			// ----- Xử lí toán tử -----

			// Nếu là dấu (
			if (line[i] == '(') {
				data.isOperator = 1;
				data.oper = line[i];
				Stack_Push(st, data);
				ResetData(data);
			}

			// Nếu là dấu )
			if (line[i] == ')') {
				Data d = Stack_Pop(st);
				while (d.oper != '(') {
					Queue_Push(q, d);
					ResetData(d);
					d = Stack_Pop(st);
				}
			}

			// Stack rỗng và không rỗng
			if (line[i] != '(' && line[i] != ')' && Stack_Size(st) == 0) {
				data.isOperator = 1;
				data.oper = line[i];
				Stack_Push(st, data);
				ResetData(data);
			}
			else if (line[i] != '(' && line[i] != ')' && Stack_Size(st) >= 0){
				Data d = Stack_Top(st);
				if (d.oper == '(') {
					data.isOperator = 1;
					data.oper = line[i];
					Stack_Push(st, data);
					ResetData(data);
				}
				else {
					d = Stack_Top(st);
					int OP_Stack = OperatorPrecedence(d.oper);
					int OP_Now = OperatorPrecedence(line[i]);
					if (OP_Stack < OP_Now) {
						data.isOperator = 1;
						data.oper = line[i];
						Stack_Push(st, data);
						ResetData(data);
					}
					else {
						while (OP_Stack >= OP_Now) {
							Data d = Stack_Pop(st);
							Queue_Push(q, d);
							if (Stack_Size(st) == 0 ) {
								break;
							}
							d = Stack_Top(st);
							OP_Stack = OperatorPrecedence(d.oper);
							OP_Now = OperatorPrecedence(line[i]);
						}
						data.isOperator = 1;
						data.oper = line[i];
						Stack_Push(st, data);
						ResetData(data);
					}
				}
			}
		}
		else {
			data.bi.digits.push_back(line[i]);
		}

		if (i == line.size() - 1) {
			if (data.bi.digits.size() > 0) {
				Queue_Push(q, data);
				ResetData(data);
			}
			while (Stack_Size(st)) {
				Data d = Stack_Pop(st);
				Queue_Push(q, d);
			}
		}
	}
}

BigInt CalculatePostfix(Queue q) {
	BigInt result;
	Stack s;
	InitStack(s);
	while (!Queue_IsEmpty(q)) {
		Data data = Queue_Pop(q);
		if (data.isOperator == 0) {
			Stack_Push(s, data);
		}
		else {
			int check1 = s.l.pHead->data.isOperator;
			int check2 = s.l.pHead->pNext->data.isOperator;
			if (check1 == 0 && check2 == 0) {
				Data a = Stack_Pop(s);
				Data b = Stack_Pop(s);
				Data c;
				ResetData(c);
				switch (data.oper) {
					case '+':
					{
						c.bi = b.bi + a.bi;
						break;
					}
					case '-':
					{
						c.bi = b.bi - a.bi;
						break;
					}
					case '*':
					{
						c.bi = b.bi * a.bi;
						break;
					}
					case '/':
					{
						c.bi = b.bi / a.bi;
						break;
					}
				}
				Stack_Push(s, c);
			}
			else {
				Stack_Push(s, data);
			}
		}
	}
	result = s.l.pHead->data.bi;
	Stack_Clear(s);
	return result;
}

void PrintQueue(const Queue& q) {
	for (Node* p = q.l.pHead; p != NULL; p = p->pNext) {
		if (p->data.isOperator == 0) {
			cout << p->data.bi << " ";
		}
		else {
			cout << p->data.oper << " ";
		}
	}
	cout << endl;
}

bool checkLine(string line) {
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ' ') {
			continue;
		}
		if (isOperator(line[i])) {
			return true;
		}
		if (isNumber(line[i])) {
			return true;
		}
	}
	return false;
}

int checkDivideZero(const Queue& q) {
	BigInt result;
	Stack s;
	InitStack(s);

	for (Node* p = q.l.pHead; p != NULL; p = p->pNext) {
		Data data = p->data;
		if (data.isOperator == 0) {
			Stack_Push(s, data);
		}
		else {
			int check1 = s.l.pHead->data.isOperator;
			int check2 = s.l.pHead->pNext->data.isOperator;
			if (check1 == 0 && check2 == 0) {
				Data a = Stack_Pop(s);
				Data b = Stack_Pop(s);
				Data c;
				ResetData(c);
				switch (data.oper) {
				case '+':
				{
					c.bi = b.bi + a.bi;
					break;
				}
				case '-':
				{
					c.bi = b.bi - a.bi;
					break;
				}
				case '*':
				{
					c.bi = b.bi * a.bi;
					break;
				}
				case '/':
				{
					if (a.bi == 0) {
						cout << "Can't divide for zero.\t";
						return 1;
					}
					c.bi = b.bi / a.bi;
					break;
				}
				}
				Stack_Push(s, c);
			}
			else {
				Stack_Push(s, data);
			}
		}

	}
	result = s.l.pHead->data.bi;
	Stack_Clear(s);
	return 0;
}

bool checkExpression(const Queue& q, int checkDivideZero) {
	if (checkDivideZero) {
		return false;
	}
	int numCheck = 0;
	int operatorCheck = 0;
	if (Queue_Size(q) < 2) {
		return false;
	}
	Data a = q.l.pHead->data;
	Data b = q.l.pHead->pNext->data;
	if (a.isOperator == 1 || b.isOperator == 1) {
		return false;
	}
	for (Node* p = q.l.pHead; p != NULL; p = p->pNext) {
		Data data = p->data;
		if (data.isOperator == 0) {
			numCheck++;
		}
		else {
			operatorCheck++;
		}
	}
	if ((operatorCheck + 1) == numCheck) {
		return true;
	}
	return false;
}