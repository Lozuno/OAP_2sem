#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Student {
    string fullName;
    int numExams;
    int grades[10];
};

bool allExamsPassedOnGoodGrades(const Student& student) {
    for (int i = 0; i < student.numExams; i++) {
        if (student.grades[i] < 4) {
            return false;
        }
    }
    return true;
}

void calculatePerformance(Student students[], int size) {
    int passedCount = 0;

    for (int i = 0; i < size; i++) {
        if (allExamsPassedOnGoodGrades(students[i])) {
            passedCount++;
        }
    }

    double performance = (double(passedCount) / size) * 100;

    cout << fixed << setprecision(2);
    cout << "Процент студентов, сдавших все экзамены на 4 и 5: " << performance << "%" << endl;
}

void displayStudentInfo(const Student& student) {
    cout << setw(30) << student.fullName << setw(10) << student.numExams;
    for (int i = 0; i < student.numExams; i++) {
        cout << setw(5) << student.grades[i];
    }
    cout << endl;
}

void displayAllStudents(Student students[], int size) {
    cout << setw(30) << "ФИО студента" << setw(10) << "Экзамены" << setw(15) << "Оценки" << endl;

    for (int i = 0; i < size; i++) {
        displayStudentInfo(students[i]);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int n;
    cout << "Введите количество студентов: ";
    cin >> n;
    cin.ignore();

    Student *students=new Student[n];

    for (int i = 0; i < n; i++) {
        cout << "\nВведите ФИО студента " << i + 1 << ": ";
        getline(cin, students[i].fullName);
        cout << "Введите количество экзаменов: ";
        cin >> students[i].numExams;
        cout << "Введите оценки за экзамены: ";
        for (int j = 0; j < students[i].numExams; j++) {
            cin >> students[i].grades[j];
        }
        cin.ignore();
    }

    displayAllStudents(students, n);

    calculatePerformance(students, n);
    delete[] students;
    return 0;
}
