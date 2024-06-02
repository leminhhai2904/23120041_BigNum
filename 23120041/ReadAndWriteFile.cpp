#include "BigNum.h"
#include "StackAndQueue.h"
#include "ReadAndWriteFile.h"

void ReadAndWriteFile(string filenameInput, string filenameOutput) {
	ifstream fi(filenameInput);
	ofstream fo("output.txt");
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
			//PrintQueue(q);
			cout << line << " ";
			BigInt result = CalculatePostfix(q);
			cout << " = " << result << endl;

			Stack_Clear(st);

			fo << line << endl;
		}
	}
	else {
		cout << "Mo file that bai!";
	}
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
				Queue_Push(q, data);
				ResetData(data);
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
			cout << p->data.bi;
			cout << " ";
		}
		else {
			cout << p->data.oper << " ";
		}
	}
	cout << endl;
}
