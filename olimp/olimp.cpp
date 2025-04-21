#include <iostream>
#include <vector>
#define ll long long
using namespace std;
int main() {
	int n;
	cin >> n;
	vector <ll> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int m;
	cin >> m;
	vector<ll> pref(m);
	vector <ll> b(m);
	cin >> b[0];
	pref[0] = b[0];
	for (int i = 1; i < m; i++) {
		cin >> b[i];
		pref[i] = pref[i - 1] + b[i];
	}

}