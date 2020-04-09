#include<iostream>

using namespace std;

int divide(int n, int m) {
	if (m <= 1 || n <= 1)
		return 1;
	if (n <= m)
		return divide(n, n - 1) + 1;
	else
		return divide(n, m - 1) + divide(n - m, m);
}

void input(int* a) {
	char c;
	int i = 0;
	cin >> a[0];
	c = getchar();

	while (c != EOF) {
		c = getchar();
		if (c !=EOF&& c !='\n') {
			cin.putback(c);
			i++;
			cin >> a[i];
		}
	}
}

int main() {
	int a[10] = { 0 };
	input(a);
	for (int i = 0; a[i] != 0; i++) {
		cout << divide(a[i],a[i])<<endl;
	}
	return 0;
}