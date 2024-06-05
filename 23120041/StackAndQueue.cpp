#include "StackAndQueue.h"
#include "BigNum.h"

// -----Data & Node & List-------

void ResetData(Data& data) {
	data.bi.digits.clear();
	data.bi.sign = 0;
	data.isOperator = 0;
	data.oper = ' ';
}


Node* CreateNode(const Data& data) {
	Node* p = new Node;
	if (p != NULL) {
		p->data = data;
		p->pNext = NULL;
	}
	return p;
}

void InitList(List& l) {
	l.pHead = l.pTail = NULL;
}

bool List_IsEmpty(const List& l) {
	if (l.pHead == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void AddHead(List& l, Node* pNewNode) {
	pNewNode->pNext = l.pHead;
	l.pHead = pNewNode;
	if (l.pTail == NULL) {
		l.pTail = l.pHead;
	}
}

void AddTail(List& l, Node* pNewNode) {
	if (l.pHead == NULL) {
		l.pHead = l.pTail = pNewNode;
	}
	l.pTail->pNext = pNewNode;
	l.pTail = pNewNode;
}

Data RemoveHead(List& l) {
	Data kq;
	if (l.pHead == NULL) {
		return kq;
	}
	Node* p = l.pHead;
	l.pHead = l.pHead->pNext;
	if (l.pHead == NULL) {
		l.pTail = NULL;
	}
	kq = p->data;
	delete p;
	return kq;
}

void RemoveList(List& l) {
	Node* p = l.pHead;
	while (p != NULL)
	{
		Node* temp = p;
		p = p->pNext;
		delete temp;
	}
}

int OperatorPrecedence(char oper) {
	if (oper == '('){
		return 0;
	}
	if (oper == '+' || oper == '-') {
		return 1;
	}
	if (oper == '*' || oper == '/') {
		return 2;
	}
}

// ----------STACK---------

bool Stack_IsEmpty(const Stack& s) {
	return List_IsEmpty(s.l);
}

void InitStack(Stack& s) {
	InitList(s.l);
}

Data Stack_Top(Stack s) {
	Data data;
	if (!Stack_IsEmpty(s)) {
		data = s.l.pHead->data;
	}
	return data;
}

Data Stack_Pop(Stack& s) {
	Data data;
	if (!Stack_IsEmpty(s)) {
		data = RemoveHead(s.l);
	}
	return data;
}

bool Stack_Push(Stack& s, const Data& data) {
	Node* p = CreateNode(data);
	if (p == NULL) {
		return false;
	}
	AddHead(s.l, p);
	return true;
}

void Stack_Clear(Stack& s) {
	RemoveList(s.l);
}

int Stack_Size(Stack& s) {
	int length = 0;
	for (Node* p = s.l.pHead; p != NULL; p = p->pNext) {
		length++;
	}
	return length;
}

// ----------QUEUE---------

bool Queue_IsEmpty(const Queue& q) {
	return List_IsEmpty(q.l);
}

void InitQueue(Queue& q) {
	InitList(q.l);
}

Data Queue_Front(const Queue& q) {
	Data data;
	if (!Queue_IsEmpty(q)) {
		data = q.l.pHead->data;
	}
	return data;
}

Data Queue_Pop(Queue& q) {
	Data data;
	if (!Queue_IsEmpty(q)) {
		data = RemoveHead(q.l);
	}
	return data;
}

bool Queue_Push(Queue& q, const Data& data) {
	Node* p = CreateNode(data);
	if (p == NULL) {
		return false;
	}
	AddTail(q.l, p);
	if (q.l.pHead == q.l.pTail) {
		q.l.pHead->pNext = q.l.pTail->pNext = NULL;
	}
	return true;
}

int Queue_Size(const Queue& q) {
	int length = 0;
	for (Node* p = q.l.pHead; p != NULL; p = p->pNext) {
		length++;
	}
	return length;
}

void Queue_Clear(Queue& q) {
	RemoveList(q.l);
}