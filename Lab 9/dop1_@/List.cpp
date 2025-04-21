#include "List.h"

Object Create() {
    return Object();
}

void printCar(void* b) {
    Car* a = (Car*)b;
    cout << "Марка: " << a->brand << "\nЦвет: " << a->color
        << "\nVIN: " << a->vin << "\nДата выпуска: " << a->prod_date
        << "\nТип кузова: " << a->body_type << "\nТехосмотр: "
        << a->last_check << "\nВладелец: " << a->owner << "\n\n";
}

bool Object::Insert(void* data) {
    Head = new Element(nullptr, data, Head);
    if (Head->Next) Head->Next->Prev = Head;
    return true;
}

bool Object::InsertEnd(void* data) {
    Element* last = GetLast();
    Element* newElem = new Element(last, data, nullptr);
    if (last) last->Next = newElem;
    else Head = newElem;
    return true;
}

Element* Object::Search(void* data) {
    Element* e = Head;
    while (e && e->Data != data) e = e->Next;
    return e;
}

bool Object::Delete(Element* e) {
    if (!e) return false;
    if (e->Prev) e->Prev->Next = e->Next;
    else Head = e->Next;
    if (e->Next) e->Next->Prev = e->Prev;
    delete e;
    return true;
}

bool Object::Delete(void* data) {
    return Delete(Search(data));
}

bool Object::DeleteList() {
    while (Head) Delete(Head);
    return true;
}

Element* Object::GetLast() {
    Element* e = Head;
    while (e && e->Next) e = e->Next;
    return e;
}

void Object::PrintList(void(*f)(void*)) {
    Element* e = Head;
    while (e) {
        f(e->Data);
        e = e->Next;
    }
}

void Object::PrintList(void(*f)(void*), Element* start) {
    Element* e = start;
    while (e) {
        f(e->Data);
        e = e->Next;
    }
}

int Object::CountList() {
    int count = 0;
    Element* e = Head;
    while (e) {
        count++;
        e = e->Next;
    }
    return count;
}

Element* Object::SearchByOwner(const char* owner) {
    Element* e = Head;
    while (e) {
        Car* car = (Car*)e->Data;
        if (strcmp(car->owner, owner) == 0) return e;
        e = e->Next;
    }
    return nullptr;
}

Element* Object::SearchByVIN(const char* vin) {
    Element* e = Head;
    while (e) {
        Car* car = (Car*)e->Data;
        if (strcmp(car->vin, vin) == 0) return e;
        e = e->Next;
    }
    return nullptr;
}