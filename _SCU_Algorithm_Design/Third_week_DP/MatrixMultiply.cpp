#include<iostream>
using namespace std;

void MatrixMultiply(int a[], int b[100][100],int n) {
	for (int i = 0; i < n; i++) {
		b[i][i] = 0;
	}
	for (int k = 1; k < n; k++) {
		for (int i = 0; i < n - k; i++) {
			b[i][i + k] = 2147483647;
			for (int j = i; j < i + k; j++) {
				int x = b[i][j] + b[j + 1][i + k] + a[i] * a[j + 1] * a[i + k + 1];
				if (x < b[i][i + k])
					b[i][i + k] = x;
			}
		}
	}
}

int main() {
	int num;
	cin >> num;
	int a[101];
	int b[100][100];
	for (int i = 0; i < num + 1; i++) {
		cin >> a[i];
	}
	MatrixMultiply(a, b, num);
	cout << b[0][num - 1]<<endl;
	return 0;
}