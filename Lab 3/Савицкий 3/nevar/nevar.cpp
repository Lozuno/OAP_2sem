#include <iostream>
#include <fstream>
using namespace std;

int countWordsInLine(const char* line) {
    int wordCount = 0;
    bool inWord = false;

    for (int i = 0; line[i] != '\0'; ++i) {
        if (isspace(line[i])) {
            if (inWord) {
                wordCount++;
                inWord = false;
            }
        }
        else {
            inWord = true;
        }
    }

    if (inWord) {
        wordCount++;
    }

    return wordCount;
}

void findLongestWordInfo(const char* line, int& index, int& length) {
    int maxLength = 0;
    int wordIndex = 0;
    int maxWordIndex = -1;
    int currentLength = 0;
    bool inWord = false;

    for (int i = 0; line[i] != '\0'; ++i) {
        if (isspace(line[i])) {
            if (inWord) {
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                    maxWordIndex = wordIndex;
                }
                currentLength = 0;
                inWord = false;
                wordIndex++;
            }
        }
        else {
            currentLength++;
            inWord = true;
        }
    }

    if (inWord) {
        if (currentLength > maxLength) {
            maxLength = currentLength;
            maxWordIndex = wordIndex;
        }
    }

    index = maxWordIndex;
    length = maxLength;
}

int main() {
    setlocale(LC_ALL, "ru");

    char buff[100];
    cout << "Введите строку символов: ";
    cin.getline(buff, 100);

    ofstream outFile("TEXT.txt");
    if (!outFile) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }
    outFile << buff;
    outFile.close();

    ifstream inFile("TEXT.txt");
    if (!inFile) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return 1;
    }
    char fileLine[256];
    inFile.getline(fileLine, 256);
    inFile.close();

    int index = 0;
    int length = 0;
    findLongestWordInfo(fileLine, index, length);

    if (index != -1) {
        cout << "Порядковый номер слова максимальной длины: " << (index + 1) << endl;
        cout << "Количество символов в этом слове: " << length << endl;
        for (int i = 0; buff[i] != '\0'; i++) {
            if (index > 0) {
                if (buff[i] == ' ') {
                    index--;
                }
            }
            else {
                for (int j = i; j <= i+length; j++) {
                    cout << buff[j];
                }
                break;
            }
        }
    }
    else {
        cout << "Строка не содержит слов." << endl;
    }

    return 0;
}