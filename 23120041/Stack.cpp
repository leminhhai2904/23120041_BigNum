#include "Stack.h"
#include "BigNum.h"

Node* CreateNode(const char& x) {
	Node* p = new Node;
	if (p != NULL) {
		p->x = x;
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

char RemoveHead(List& l) {
	char kq = ' ';
	if (l.pHead == NULL) {
		return kq;
	}
	Node* p = l.pHead;
	l.pHead = l.pHead->pNext;
	if (l.pHead == NULL) {
		l.pTail = NULL;
	}
	kq = p->x;
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
// ----------STACK---------

bool Stack_IsEmpty(const Stack& s) {
	return List_IsEmpty(s.l);
}

void InitStack(Stack& s) {
	InitList(s.l);
}

char Stack_Top(Stack s) {
	char info = ' ';
	if (!Stack_IsEmpty(s)) {
		info = s.l.pHead->x;
	}
	return info;
}

char Stack_Pop(Stack& s) {
	char x = ' ';
	if (!Stack_IsEmpty(s)) {
		x = RemoveHead(s.l);
	}
	return x;
}

bool Stack_Push(Stack& s, const char& info) {
	Node* p = CreateNode(info);
	if (p == NULL) {
		return false;
	}
	AddHead(s.l, p);
	return true;
}

void Stack_Clear(Stack& s) {
	RemoveList(s.l);
}
