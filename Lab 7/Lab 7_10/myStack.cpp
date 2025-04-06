#include <iostream>
#include <fstream>
#include "myStack.h"
using namespace std;

void push(int x, Stack*& myStk)   //���������� �������� � � ����	
{
	Stack* e = new Stack;    //��������� ������ ��� ������ ��������
	e->data = x;             //������ �������� x � ���� data 
	e->next = myStk;         //������� ������� �� ��������� ������� 
	myStk = e;               //����� ������� �� ������� ������
}

int pop(Stack*& myStk)   //���������� (��������) �������� �� �����
{
	if (myStk == NULL)
	{
		cout << "���� ����!" << endl;
		return -1;               //���� ���� ���� - ������� (-1) 
	}
	else
	{
		Stack* e = myStk;        //�-���������� ��� �������� ������ ��������
		int x = myStk->data;    //������ �������� �� ���� data � �����. x 
		if (myStk)
			myStk = myStk->next;   //������� �������
		delete e;
		return x;
	}
}
void toFile(Stack*& myStk) //������ � ����
{
	Stack* e = myStk;
	Stack buf;
	ofstream frm("mStack.txt");
	if (frm.fail())
	{
		cout << "\n ������ �������� �����";
		exit(1);
	}
	while (e)
	{
		buf = *e;
		cout << buf.data << ' ';
		e = e->next;
	}
	frm.close();
	cout << "���� ������� � ���� mStack.txt\n";
}

void fromFile(Stack*& myStk)          //���������� �� �����
{
	Stack buf, * p = nullptr, * e = nullptr;
	ifstream frm("mStack.txt");
	if (frm.fail())
	{
		cout << "\n ������ �������� �����";
		exit(1);
	}
	frm.seekg(0);
	frm >> buf.data;
	while (!frm.eof())
	{
		push(buf.data, e);
		frm >> buf.data;
	}
	frm.close();
	while (e != NULL)
	{
		buf.data = pop(e);
		push(buf.data, p);
		myStk = p;
	}
	cout << "\n���� ������ �� ����� mStack.txt\n\n";
}
void show(Stack*& myStk)  //����� ����� � ��������
{
	Stack* e = myStk;
	if (e == NULL)
		cout << "���� ����!" << endl;
	while (e != NULL)
		cout << pop(e) << " ";
	cout << endl;
}

void checkDiapason(Stack*& myStack, int min, int max) {
	Stack* bufStack = NULL;
	int k = 1;
	int buf;
	bool flag = false;
	while (myStack != NULL) {
		buf = pop(myStack);
		push(buf, bufStack);
		if (min <= buf && buf <= max) {
			flag = true;
			break;
		}
		k++;
	}
	while (bufStack != NULL) {
		push(pop(bufStack), myStack);
	}
	if (flag) {
		cout << "������� ������ ��� �������: " << k << endl;
	}
	else {
		cout << "������� �� ������";
	}
	return;
}
void fuseStack(Stack*& stack1, Stack*& stack2, Stack*& resultStack) {
	Stack* temp1 = NULL;
	Stack* temp2 = NULL;
	Stack* temp = NULL;
	while (stack2 != NULL) {
		int buf=pop(stack2);
		push(buf, temp);
		push(buf, temp2);
	}
	while (temp2 != NULL) {
		push(pop(temp2), stack2);
	}
	while (stack1 != NULL) {
		int value = pop(stack1);
		push(value, temp1);  

		while (temp != NULL) {
			int value2 = pop(temp);

			if (value2 == value) {
				push(value, resultStack);
				break;
			}
			push(value2, temp2);
		}
		while (temp2 != NULL) {
			push(pop(temp2), temp);
		}
	}

	while (temp1 != NULL) {
		push(pop(temp1), stack1);
	}
}
void removeFirstDuplicate(Stack*& myStk) {
	if (!myStk || !myStk->next) return;  

	Stack* tempStack = NULL;  
	int removedValue = -1;    
	bool found = false;       

	
	while (myStk != NULL && !found) {
		int value = pop(myStk);
		Stack* temp = NULL;
		while (tempStack != NULL) {
			int value1 = pop(tempStack);
			if (value1 == value) {
				removedValue = value;
				found = true;
				break;
			}
			push(value1, temp);
		}
		while (temp != NULL) {
			push(pop(temp), tempStack);
		}
		if (found) {
			while (tempStack != NULL) {
				push(pop(tempStack), myStk);
			}
			cout << "����� �������: " << removedValue << endl;
			return;
		}

		push(value, tempStack); 
	}
	while (tempStack != NULL) {
		push(pop(tempStack), myStk);
	}
	cout << "������������� ��������� ���" << endl;
}
void remDupl(Stack*& stack1,Stack*& same, Stack*& res){
	Stack* temp = NULL;
	Stack* buftemp = NULL;
	Stack* res1 = NULL;
	while (stack1 != NULL) {
		int buf = pop(stack1);
		push(buf, temp);
		push(buf, res1);
	}
	while (res1 != NULL) {
		push(pop(res1), stack1);
	}
	while (same != NULL) {
		int buf = pop(same);
		push(buf, buftemp);
		while (temp != NULL) {
			int value1 = pop(temp);
			if (value1 == buf) {
				break;
			}
			push(value1, res1);
		}
		while (res1 != NULL) {
			push(pop(res1), temp);
		}
	}
	while (temp != NULL) {
		push(pop(temp), res);
	}
	while (buftemp != NULL) {
		push(pop(buftemp), same);
	}
}
void delStacks(Stack*& stack1,Stack*& stack2, Stack*& res) {
	Stack* same = NULL;
	Stack* res1 = NULL;
	fuseStack(stack1, stack2, same);
	remDupl(stack1, same, res1);
	while (res1 != NULL) {
		push(pop(res1), res);
	}
	remDupl(stack2, same, res1);
	while (res1 != NULL) {
		push(pop(res1), res);
	}
}
void clear(Stack*& myStk) {
	while (myStk != NULL) {
		pop(myStk);
	}
	return;
}