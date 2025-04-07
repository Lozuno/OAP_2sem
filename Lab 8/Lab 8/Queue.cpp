#include "Queue.h"

using namespace std;

void clear(Queue* q) {
    q->first = q->mas;
    q->last = q->mas;
}

void fixQueue(Queue* q) {
    A* newfirst = q->mas;
    A* newlast = q->mas;
    while (q->first != q->last) {
        *newlast++ = *q->first++;
    }
    q->first = newfirst;
    q->last = newlast;
}

bool isEmpty(Queue* q) {
    return q->first == q->last;
}

bool isFull(Queue* q) {
    return q->first == q->mas && q->last == (q->mas + MAXSIZE-1);
}

A top(Queue* q) {
    if (!isEmpty(q)) {
        return *q->first;
    }
    else {
        cout << "Очередь пуста\n";
        return -1;
    }
}

A pop(Queue* q) {
    if (!isEmpty(q)) {
        return *q->first++;
    }
    else {
        cout << "Очередь пуста\n";
        return -1;
    }
}

bool push(A element, Queue* q) {
    if (isFull(q)) {
        cout << "Очередь заполнена\n";
        return false;
    }
    if (q->last == (q->mas + MAXSIZE)) {
        fixQueue(q);
    }
    *q->last++ = element;
    return true;
}

void print(Queue* q) {
    Queue* temp = new Queue;
    while (!isEmpty(q)) {
        A buf = pop(q);
        cout << buf << ' ';
        push(buf, temp);
    }
    cout << '\n';
    while (!isEmpty(temp)) {
        push(pop(temp), q);
    }
    delete temp;
    return;
}
void copyQueue(Queue* q1, Queue* q2) {
    Queue* temp = new Queue;
    while (!isEmpty(q1)) {
        A buf=pop(q1);
        push(buf, temp);
        push(buf, q2);
    }
    while (!isEmpty(temp)) {
        push(pop(temp), q1);
    }
}
int curSize(Queue* q) {
    return q->last - q->first;
}
void minmax(Queue* q, Queue* q1, Queue* q2) {
    Queue* temp = new Queue;
    copyQueue(q, temp);
    Queue* buf = new Queue;
    int i = 0;
    while (!isEmpty(temp)) {
        A minmax = pop(temp);
        push(minmax, buf);
        while (!isEmpty(temp)) {
            A el = pop(temp);
            push(el, buf);
            if ((i % 2 == 0 ? minmax<el : minmax>el)) {
                minmax = el;
            }
        }
        while (!isEmpty(buf)) {
            A el = pop(buf);
            if (el == minmax) {
                push(el, (i % 2 == 0 ? q1 : q2));
            }
            else {
                push(el, temp);
            }
        }
        i++;
    }
    delete buf;
    delete temp;
}