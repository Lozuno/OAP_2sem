#pragma once
#include <iostream>
#include <cstring>

using namespace std;

struct Element {
    Element* Prev;
    Element* Next;
    void* Data;
    Element(Element* prev, void* data, Element* next)
        : Prev(prev), Data(data), Next(next) {
    }
};

struct Car {
    char brand[20];
    char color[15];
    char vin[17];
    char prod_date[11];
    char body_type[10];
    char last_check[11];
    char owner[30];
};

struct Object {
    Element* Head;
    Object() : Head(nullptr) {}

    Element* GetFirst() { return Head; }
    Element* GetLast();
    Element* Search(void* data);
    bool Insert(void* data);
    bool InsertEnd(void* data);
    bool Delete(Element* e);
    bool Delete(void* data);
    bool DeleteList();
    void PrintList(void(*f)(void*));
    void PrintList(void(*f)(void*), Element*);
    int CountList();
    Element* SearchByOwner(const char* owner);
    Element* SearchByVIN(const char* vin);
};

Object Create();
void printCar(void* b);