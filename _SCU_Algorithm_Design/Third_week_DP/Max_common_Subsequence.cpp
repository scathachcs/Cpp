#include<iostream>
using namespace std;

int SubSequence(int a[], int b[], int n1, int n2) {
	int **c = new int *[n1+1];
	for (int i = 0; i <= n1; i++)
		c[i] = new int[n2+1];

	

	for (int i = 0; i <= n1; i++)
		c[i][0] = 0;
	for (int i = 0; i <= n2; i++)
		c[0][i] = 0;

	for (int i = 1; i <= n1; i++) {
		for (int j = 1; j <= n2; j++) {
			if (a[i] == b[j])
				c[i][j] = c[i - 1][j - 1] + 1;
			else
				c[i][j] = (c[i - 1][j] >= c[i][j - 1] ? c[i - 1][j] : c[i][j - 1]);
		}
	}

	int x = c[n1][n2];

	for (int i = 0; i <= n1; i++)
		delete[] c[i];
	delete[] c;

	return x;
}

int main() {
	int num;
	int a[1001];
	int b[1001];
	cin >> num;
	for (int i = 1; i <= num; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= num; i++) {
		cin >> b[i];
	}
	cout<<SubSequence(a, b, num, num)<<endl;
	
	return 0;
}