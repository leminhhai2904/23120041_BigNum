#ifndef __STACKANDQUEUE_H_
#define __STACKANDQUEUE_H_

#include "BigNum.h"

struct Data {
	BigInt bi;
	char oper;
	int isOperator;
};

struct Node {
	Data data;
	Node* pNext;
};

struct List {
	Node* pHead;
	Node* pTail;
};

struct Stack {
	List l;
};

struct Queue {
	List l;
};

// -----Data & Node & List-------
void ResetData(Data& data);
int OperatorPrecedence(char oper);
Node* CreateNode(const Data& data);
void InitList(List& l);
bool List_IsEmpty(const List& l);
void AddHead(List& l, Node* pNewNode);
void AddTail(List& l, Node* pNewNode);
Data RemoveHead(List& l);
void RemoveList(List& l);
// ----------STACK---------
bool Stack_IsEmpty(const Stack& s);
void InitStack(Stack& s);
Data Stack_Top(Stack s);
Data Stack_Pop(Stack& s);
bool Stack_Push(Stack& s, const Data& data);
void Stack_Clear(Stack& s);
int Stack_Size(Stack& s);
// ----------QUEUE---------
bool Queue_IsEmpty(const Queue& q);
void InitQueue(Queue& q);
Data Queue_Front(const Queue& q);
Data Queue_Pop(Queue& q);
bool Queue_Push(Queue& q, const Data& data);
void Queue_Clear(Queue& q);
#endif // !__STACKANDQUEUE_H_