#include "List.h"

void showMenu(Object& list) {
    int choice;
    char input[30];
    Element* startElem = nullptr;

    do {
        cout << "\n=== Меню ===\n"
            << "1. Добавить в начало\n"
            << "2. Добавить в конец\n"
            << "3. Удалить по VIN\n"
            << "4. Показать все\n"
            << "5. Показать с элемента\n"
            << "6. Найти по владельцу\n"
            << "7. Количество автомобилей\n"
            << "8. Очистить список\n"
            << "9. Выход\n"
            << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
        case 2: {
            Car* newCar = new Car();
            cout << "Марка: "; cin.getline(newCar->brand, 20);
            cout << "Цвет: "; cin.getline(newCar->color, 15);
            cout << "VIN: "; cin.getline(newCar->vin, 17);
            cout << "Дата выпуска: "; cin.getline(newCar->prod_date, 11);
            cout << "Тип кузова: "; cin.getline(newCar->body_type, 10);
            cout << "Техосмотр: "; cin.getline(newCar->last_check, 11);
            cout << "Владелец: "; cin.getline(newCar->owner, 30);
            (choice == 1) ? list.Insert(newCar) : list.InsertEnd(newCar);
            break;
        }
        case 3: {
            cout << "Введите VIN: ";
            cin.getline(input, 17);
            Element* e = list.SearchByVIN(input);
            if (e) {
                list.Delete(e);
                cout << "Удалено.\n";
            }
            else cout << "Не найдено!\n";
            break;
        }
        case 4:
            list.PrintList(printCar);
            break;
        case 5: {
            cout << "Введите VIN начального элемента: ";
            cin.getline(input, 17);
            startElem = list.SearchByVIN(input);
            if (startElem) list.PrintList(printCar, startElem);
            else cout << "Элемент не найден!\n";
            break;
        }
        case 6: {
            cout << "Введите владельца: ";
            cin.getline(input, 30);
            Element* e = list.SearchByOwner(input);
            if (e) printCar(e->Data);
            else cout << "Не найдено!\n";
            break;
        }
        case 7:
            cout << "Количество: " << list.CountList() << "\n";
            break;
        case 8:
            list.DeleteList();
            cout << "Список очищен.\n";
            break;
        case 9:
            list.DeleteList();
            cout << "Выход.\n";
            break;
        default:
            cout << "Ошибка выбора!\n";
        }
    } while (choice != 9);
}

int main() {
    setlocale(LC_ALL, "Russian");
    Object carList = Create();
    showMenu(carList);
    return 0;
}/*
1 Toyota	Red	123456	2020-05-15	Sedan	2023-04-01	Ivanov
1 BMW	Black	234567	2019-07-20	SUV	2022-11-30	Petrov
1 Mercedes	White	345678	2018-03-10	Coupe	2021-12-05	Sidorov
1 Audi	Blue	456789	2021-01-25	Hatchback	2023-06-15	Smirnov
1 Volkswagen	Grey	567890	2017-08-05	Sedan	2021-09-22	Kuznetsov
1 Ford	Green	678901	2022-11-02	Universal	2023-07-10	Nikolaev
1 Kia	Yellow	789012	2020-09-17	Sedan	2023-02-28	Popov
1 Nissan	Silver	890123	2016-12-11	Hatchback	2020-05-13	Orlov
1 Hyundai	Orange	901234	2015-05-22	SUV	2022-10-25	Vasiliev

 */