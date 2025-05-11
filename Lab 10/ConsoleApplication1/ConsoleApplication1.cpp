﻿#include <iostream>
#include <cstring> 
using namespace std;
const char* w[] = { "ПАЛКА", "ЛЯГУШКА", "КАПЛЯ", "КАРТА", NULL };

bool test(const char* s, const char* r) {
    int n = strlen(s);
    if (n == 0) {
        return true;
    }
    for (; *s != '\0' && n > 1; s++, n--) {
        if (strncmp(s, r, n) == 0) {
            return true;
        }
    }
    return false;
}

int step(const char* lw) {
    setlocale(LC_CTYPE, "Russian");
    int n;

    for (n = 0; w[n] != NULL; n++) {
        if (*w[n] != '\0') {
            break;
        }
    }
    if (w[n] == NULL)         return 1;
for (n = 0; w[n] != NULL; n++) {
    const char* pw;
    if (*w[n] == '\0') {
        continue;
    }

    pw = w[n];
    w[n] = "";
    if (test(lw, pw)) {
        if (step(pw)) {
            cout << pw << "\n";
            return 1;
        }
    }

    w[n] = pw;
}
return 0;
}

int main() {
    step("");
    return 0;
}

