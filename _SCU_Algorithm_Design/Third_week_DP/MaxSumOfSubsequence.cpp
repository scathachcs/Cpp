#include<iostream>
using namespace std;

int MaxSumOfSubsequence(int* a, int end) {
	int b = 0;
	int max = -10086;
	for (int i = 0; i < end; i++) {
		if (b > 0)
			b += a[i];
		else
			b = a[i];
		if (b > max)
			max = b;
	}
	return max;
}

int main() {
	int num = 1;
	int a[200000];
	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> a[i];
	}
	cout << MaxSumOfSubsequence(a, num) << endl;
}