#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct Train {
    string destination;
    int trainNumber;
    string departureTime;
};

bool compareTrainsByDestination(const Train& a, const Train& b) {
    return a.destination < b.destination;
}

int main() {
    int size = 8;
    Train* trains = new Train[size];

    for (int i = 0; i < size; i++) {
        cout << "\nВведите пункт назначения поезда " << i + 1 << ": ";
        getline(cin, trains[i].destination);
        cout << "Введите номер поезда: ";
        cin >> trains[i].trainNumber;
        cin.ignore();
        cout << "Введите время отправления (в формате HH:MM): ";
        getline(cin, trains[i].departureTime);
    }

    sort(trains, trains + size, compareTrainsByDestination);

    cout << setw(30) << "Пункт назначения" << setw(10) << "Номер поезда" << setw(10) << "Время отправления" << endl;

    for (int i = 0; i < size; i++) {
        cout << setw(30) << trains[i].destination << setw(10) << trains[i].trainNumber << setw(10) << trains[i].departureTime << endl;
    }

    string inputTime;
    cout << "\nВведите время для поиска поездов, отправляющихся позже этого времени (в формате HH:MM): ";
    getline(cin, inputTime);

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (trains[i].departureTime > inputTime) {
            cout << setw(30) << trains[i].destination << setw(10) << trains[i].trainNumber << setw(10) << trains[i].departureTime << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Поездов, отправляющихся после указанного времени, не найдено." << endl;
    }

    delete[] trains;

    return 0;
}
