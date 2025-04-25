#include <iostream>
#include <fstream>
using namespace std;

void fVarA(int A, int len, ofstream &fout,int buf[]) {
	if (len == 0) {
		for (int i = A; i > 0; i--) {
			fout << buf[i];
		}
		fout << ' ';
		return;
	}
	for (int i = 0; i <=A; i++) {
		if (i == 0 && len == A) {
			i++;
		}
		buf[len] = i;
		fVarA(A, len - 1, fout, buf);
	}
	return;
}

int main() {
	char fname[] = "ans.txt";
	int A,buf[256];
	ofstream fout(fname);
	cin >> A;
	fVarA(A, A, fout, buf);
	return 0;
}