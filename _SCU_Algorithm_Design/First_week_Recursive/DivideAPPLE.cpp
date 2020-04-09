#include<stdio.h>
#include<iostream>
using namespace std;

int divideAPPLE(int m,int n) {
	if (m <= 1|| n <= 1)
		return 1;
	if (n > m)
		return divideAPPLE(m, m);
	else
		return divideAPPLE(m, n - 1) + divideAPPLE(m - n, n);
}

void input(int* a) {
	char c;
	int i = 0;
	cin >> a[0];
	c = getchar();

	while (c != EOF) {
		c = getchar();
		if (c != EOF && c != '\n') {
			cin.putback(c);
			i++;
			cin >> a[i];
		}
	}
}

int main() {
	int m[10] = { 0 }, n[10] = {0};
	int i = 0;
	while (scanf_s("%d %d", &m[i], &n[i]) != EOF) {
		i++;
	}
	for (int i = 0; m[i] != 0; i++) {
		cout << divideAPPLE(m[i], n[i])<<endl;
	}
	return 0;
}


