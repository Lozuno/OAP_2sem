#include <iostream>
#include <iomanip>
#define N 8
using namespace std;

struct TRAIN {
	char where[20];
	int nomer;
	int when;
	char whenTime[20];
};

bool compStr(char a[], char b[]) {
	int i=0;
	for (; a[i] != '\0' && b[i] != '\0'; i++) {
		if (tolower(a[i]) < tolower(b[i])) {
			return true;
		}
		if (tolower(a[i]) > tolower(b[i])) {
			return false;
		}
	}
	if (a[i] == '\0') {
		return true;
	}
	return false;
}
void sortTrain(TRAIN all[]) {
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (!compStr(all[i].where, all[j].where)) {
				TRAIN temp = all[i];
				all[i] = all[j];
				all[j] = temp;
			}
		}
	}
}

int main() {
	TRAIN all[N];
	for (int i = 0; i < N; i++) {
		cin >> all[i].where >> all[i].nomer;
		cin >> all[i].whenTime;
		char temp[20] = "";
		strcpy_s(temp, all[i].whenTime);
		all[i].when = ((temp[0] - '0') * 10 + (temp[1] - '0')) * 60 + (temp[3] - '0') * 10 + (temp[4] - '0');
	}
	cout << '\n';
	sortTrain(all);
	for (int i = 0; i < N; i++) {
		cout<<left <<setw(20)<< all[i].where << setw(15) << all[i].nomer << setw(10) << all[i].whenTime << '\n';
	}
	cout << '\n';
	char time[15];
	cin >> time;
	int min = ((time[0] - '0') * 10 + (time[1] - '0')) * 60 + (time[3] - '0') * 10 + (time[4] - '0');
	for (int i = 0; i < N; i++) {
		if (all[i].when - min > 0) {
			cout << left << setw(20) << all[i].where << setw(15) << all[i].nomer << setw(10) << all[i].whenTime << '\n';
		}
	}
	return 0;
}

/*
Moscow 101 14:30
SaintPetersburg 202 09:15
Kazan 303 16:45
Novosibirsk 404 12:00
Yekaterinburg 505 18:30
NizhnyNovgorod 606 10:00
Rostov 707 15:15
Vladivostok 808 20:00
*/