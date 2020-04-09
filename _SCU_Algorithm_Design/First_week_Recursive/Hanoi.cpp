#include<iostream>
#include<math.h>

using namespace std;

int static x = 0;

void Hanoi(int n, int num, char src, char dest, char z) {
	if (n == 1) {
		x++;
		cout << "step " << x << ": " << num << " From " << src << " To " << dest << endl;
	}
	if (n > 1) {
		Hanoi(n - 1, num - 1, src, z, dest);
		Hanoi(1, num, src, dest, z);
		Hanoi(n - 1, num - 1, z, dest, src);
	}

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
	int a[100] = { 0 };
	input(a);
	for (int i = 0; a[i] != 0; i++) {
		x = 0;
		cout << pow(2, a[i]) - 1 << endl;
		Hanoi(a[i], a[i], 'A', 'C', 'B');
	}

}