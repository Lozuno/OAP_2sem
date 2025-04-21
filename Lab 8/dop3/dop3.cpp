#include "/Уник/2sem/OAP_2sem/Lab 8/Lab 8/Queue.h"
using namespace std;

int main() {
	ifstream fin("f.txt");
	ofstream fout("g.txt");
	char buf[256];
	while (fin.getline(buf, 256)) {
		Queue* q=new Queue;	
		int start = 0, end;
		int i = 0;
		while (buf[i-1] != '\0') {
			if (buf[i] == ' '||buf[i]=='\0') {
				char c[256];
				end = i;
				bool flag = true;
				for (int j = start; j < end; j++) {
					c[j - start] = buf[j];
					if (!isdigit(buf[j])) {
						flag = false;
					}
				}
				c[end-start] = '\0';
				if (flag) {
					push(atoi(c), q);
				}
				else {
					fout << c<<' ';
				}
				start = i + 1;
			}
			i++;
		}
		Queue* temp = new Queue;
		while (!isEmpty(q)) {
			A buf = pop(q);
			fout << buf << ' ';
			push(buf, temp);
		}
		fout << '\n';
		while (!isEmpty(temp)) {
			push(pop(temp), q);
		}
		delete temp;
	}
	return 0;
}