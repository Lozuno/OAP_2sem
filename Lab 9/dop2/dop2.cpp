#include <iostream>
#include <iomanip>
#include <limits>
#include <cstring>

using namespace std;

const int MAX = 30;
const int SUBJ = 5;

struct Student {
    char lastName[MAX];
    char firstName[MAX];
    char patronymic[MAX];
    int birth;
    int course;
    int group;
    int grades[SUBJ] = { 0 };
    Student* next;
    Student* prev;
};

void addStudent(Student*& head, Student*& tail, Student* student) {
    if (!head) {
        head = tail = student;
    }
    else {
        tail->next = student;
        student->prev = tail;
        tail = student;
    }
    student->next = nullptr;
}

int inputInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Пожалуйста, введите целое число: ";
    }
    return value;
}

void inputStudent(Student*& head, Student*& tail) {
    Student* newStudent = new Student();

    cout << "Введите фамилию: ";
    cin.ignore(cin.rdbuf()->in_avail());
    cin.getline(newStudent->lastName, MAX);

    cout << "Введите имя: ";
    cin.getline(newStudent->firstName, MAX);

    cout << "Введите отчество: ";
    cin.getline(newStudent->patronymic, MAX);

    cout << "Введите год рождения: ";
    newStudent->birth = inputInt();

    cout << "Введите курс: ";
    newStudent->course = inputInt();

    cout << "Введите группу: ";
    newStudent->group = inputInt();

    cout << "Введите оценки по пяти предметам:\n";
    for (int i = 0; i < SUBJ; i++) {
        cout << "Предмет " << i + 1 << ": ";
        newStudent->grades[i] = inputInt();
    }

    addStudent(head, tail, newStudent);
}

void sortStudents(Student*& head, Student*& tail) {
    if (!head || !head->next) return;

    bool swapped;
    do {
        swapped = false;
        Student* current = head;
        Student* prev = nullptr;
        Student* nextNode = nullptr;

        while (current && current->next) {
            nextNode = current->next;
            bool needSwap = false;

            if (current->course > nextNode->course) {
                needSwap = true;
            }
            else if (current->course == nextNode->course) {
                if (strcmp(current->lastName, nextNode->lastName) > 0) {
                    needSwap = true;
                }
            }

            if (needSwap) {
                if (current->prev) current->prev->next = nextNode;
                nextNode->prev = current->prev;
                current->prev = nextNode;
                current->next = nextNode->next;
                if (nextNode->next) nextNode->next->prev = current;
                nextNode->next = current;

                if (current == head) head = nextNode;
                if (nextNode == tail) tail = current;

                swapped = true;
                prev = nextNode;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);
}

void calculateGroupAverages(Student* head) {
    struct GroupData {
        int course;
        int group;
        double sums[SUBJ] = { 0 };
        int count = 0;
    };

    GroupData groups[100];
    int groupCount = 0;

    for (Student* curr = head; curr; curr = curr->next) {
        bool found = false;
        for (int i = 0; i < groupCount; i++) {
            if (groups[i].course == curr->course && groups[i].group == curr->group) {
                for (int j = 0; j < SUBJ; j++) {
                    groups[i].sums[j] += curr->grades[j];
                }
                groups[i].count++;
                found = true;
                break;
            }
        }
        if (!found) {
            groups[groupCount].course = curr->course;
            groups[groupCount].group = curr->group;
            for (int j = 0; j < SUBJ; j++) {
                groups[groupCount].sums[j] = curr->grades[j];
            }
            groups[groupCount].count = 1;
            groupCount++;
        }
    }

    cout << "\nСредние баллы по группам:\n";
    for (int i = 0; i < groupCount; i++) {
        cout << "Курс " << groups[i].course
            << ", Группа " << groups[i].group << ": ";
        for (int j = 0; j < SUBJ; j++) {
            cout << fixed << setprecision(2)
                << groups[i].sums[j] / groups[i].count << " ";
        }
        cout << endl;
    }
}

void findAgeExtremes(Student* head) {
    if (!head) return;

    Student* oldest = head;
    Student* youngest = head;

    for (Student* curr = head; curr; curr = curr->next) {
        if (curr->birth < oldest->birth) oldest = curr;
        if (curr->birth > youngest->birth) youngest = curr;
    }

    cout << "\nСамый старший: " << oldest->lastName
        << " " << oldest->firstName << " (" << oldest->birth << ")\n";
    cout << "Самый младший: " << youngest->lastName
        << " " << youngest->firstName << " (" << youngest->birth << ")\n";
}

void findTopStudents(Student* head) {
    struct GroupBest {
        int group;
        Student* best;
        double avg;
    };

    GroupBest bests[100];
    int groupCount = 0;

    for (Student* curr = head; curr; curr = curr->next) {
        double sum = 0;
        for (int grade : curr->grades) sum += grade;
        double avg = sum / SUBJ;

        bool found = false;
        for (int i = 0; i < groupCount; i++) {
            if (bests[i].group == curr->group) {
                if (avg > bests[i].avg) {
                    bests[i].best = curr;
                    bests[i].avg = avg;
                }
                found = true;
                break;
            }
        }

        if (!found) {
            bests[groupCount] = { curr->group, curr, avg };
            groupCount++;
        }
    }

    cout << "\nЛучшие студенты по группам:\n";
    for (int i = 0; i < groupCount; i++) {
        cout << "Группа " << bests[i].group << ": "
            << bests[i].best->lastName << " "
            << bests[i].best->firstName << " (Ср. балл: "
            << fixed << setprecision(2) << bests[i].avg << ")\n";
    }
}

void printStudents(Student* head) {
    cout << "\nСписок студентов:\n";
    for (Student* curr = head; curr; curr = curr->next) {
        cout << curr->lastName << " " << curr->firstName
            << " (Курс: " << curr->course
            << ", Группа: " << curr->group << ")\n";
    }
}

void deleteStudents(Student*& head) {
    while (head) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    Student* head = nullptr;
    Student* tail = nullptr;

    int count;
    cout << "Введите количество студентов: ";
    count = inputInt();

    for (int i = 0; i < count; i++) {
        cout << "\nСтудент #" << i + 1 << ":\n";
        inputStudent(head, tail);
    }

    sortStudents(head, tail);
    printStudents(head);
    calculateGroupAverages(head);
    findAgeExtremes(head);
    findTopStudents(head);

    deleteStudents(head);
    return 0;
}