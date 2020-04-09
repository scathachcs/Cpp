#include<iostream>

using namespace std;

int main() {
	int a[100000] = { 0 };
	int b[100000] = { 0 };
	int num = 0;
	int input;
	cin >> num;
	int len = 1;
	for (int i = 0; i < num; i++) {
		cin >> input;
		a[i] = input;
		b[i] = 1;
		for (int j = 0; j < i; j++) {
			if (a[i] > a[j] && b[i] < (b[j] + 1)) {
				b[i] = b[j] + 1;
			}
		}
		if (b[i] > len)
			len = b[i];
	}
	cout << len << endl;
	return 0;
}