#ifndef __STACK_H_
#define __STACK_H_

#include "BigNum.h"

struct Node {
	char x;
	Node* pNext;
};

struct List {
	Node* pHead;
	Node* pTail;
};

struct Stack {
	List l;
};

// -----Node & List-------
Node* CreateNode(const char& x);
void InitList(List& l);
bool List_IsEmpty(const List& l);
void AddHead(List& l, Node* pNewNode);
char RemoveHead(List& l);
void RemoveList(List& l);
// ----------STACK---------
bool Stack_IsEmpty(const Stack& s);
void InitStack(Stack& s);
char Stack_Top(Stack s);
char Stack_Pop(Stack& s);
bool Stack_Push(Stack& s, const char& x);
void Stack_Clear(Stack& s);

#endif // !__STACK_H_