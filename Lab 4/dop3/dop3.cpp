#include <iostream>
#include <iomanip>
#define N 13
using namespace std;

struct SANIT {
	char name[25];
	char where[20];
	char profil[20];
	int col;
};

bool compStr(char a[], char b[]) {
	int i = 0;
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
void sortProfil(SANIT all[]) {
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (!compStr(all[i].profil, all[j].profil)) {
				SANIT temp = all[i];
				all[i] = all[j];
				all[j] = temp;
			}
		}
	}
}
void sortName(SANIT all[]) {
	int start = 0;
	for (int k = 1; k <= N; k++) {
		if (k == N) {
			for (int j = start; j < k; j++) {
				for (int i = j; i < k; i++) {
					if (compStr(all[i].where, all[j].where)) {
						SANIT temp = all[i];
						all[i] = all[j];
						all[j] = temp;
					}
				}
			}
		}
		else {
			if (strcmp(all[k].profil, all[k - 1].profil)!=0) {
				for (int j = start; j < k; j++) {
					for (int i = j; i < k; i++) {
						if (compStr(all[i].where, all[j].where)) {
							SANIT temp = all[i];
							all[i] = all[j];
							all[j] = temp;
						}
					}
				}
				start = k;
			}
			
		}
	}
}
int main() {
	SANIT all[N];
	for (int i = 0; i < N; i++) {
		cin >> all[i].name >> all[i].where >> all[i].profil >> all[i].col;
	}
	cout << '\n';
	sortProfil(all);
	for (int i = 0; i < N; i++) {
		cout << left << setw(20) << all[i].name << setw(20) << all[i].where << setw(20) << all[i].profil << setw(7) << all[i].col << '\n';
	}
	cout << '\n';
	sortName(all);
	for (int i = 0; i < N; i++) {
		cout << left << setw(20) << all[i].name << setw(20) << all[i].where << setw(20) << all[i].profil << setw(7) << all[i].col << '\n';
	}
	return 0;
}
/*
SunnyHealth Sochi Therapy 20
GreenValley Anapa Orthopedics 15
CrystalSpring Gelendzhik Cardiology 10
HealthNest KrasnayaPolyana Therapy 5
MountainAir Yalta Orthopedics 8
OceanBreeze Crimea Cardiology 12
VitalityCenter Moscow Therapy 25
RelaxSanatorium StPetersburg Spa 30
NatureCure NizhnyNovgorod Cardiology 18
PeacefulRetreat Kazan Orthopedics 22
HarmonyHealth Vladivostok Therapy 11
SerenityBay Sochi Spa 14
HealingSprings Anapa Cardiology 9
*/