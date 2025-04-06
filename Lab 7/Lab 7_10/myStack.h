#pragma once
struct Stack
{
	int data;     //информационный элемент
	Stack* next;	 //указатель на следующий элемент
};
void show(Stack*& myStk);
int pop(Stack*& myStk);
void push(int x, Stack*& myStk);
void toFile(Stack*& myStk);
void fromFile(Stack*& myStk);
void checkDiapason(Stack*& myStack, int min, int max);
void clear(Stack*& myStk);
void fuseStack(Stack*& stack1, Stack*& stack2, Stack*& resultStack);
void removeFirstDuplicate(Stack*& myStk);
void delStacks(Stack*& stack1, Stack*& stack2, Stack*& res);