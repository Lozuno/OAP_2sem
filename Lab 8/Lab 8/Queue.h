#pragma once
#include <iostream>
#define MAXSIZE 1000
#define A int
using namespace std;
struct Queue {
    A mas[MAXSIZE];
    A* first = mas;
    A* last = mas;
};

int curSize(Queue* q);
void clear(Queue* q);
bool isEmpty(Queue* q);
bool isFull(Queue* q);
A top(Queue* q);
A pop(Queue* q);
bool push(A element, Queue* q);
void print(Queue* q);
void minmax(Queue* q, Queue* q1, Queue* q2);