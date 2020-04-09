#include<iostream>

using namespace std;

void show(int* b) {
	for (int i = 1; i <= b[0]; i++) {
		cout << b[i];
	}
	cout << endl;
}


void arrange(int* a,int* b,int front) {
	if (front > b[0]) {
		show(b);
	}

	for (int i = 1; i <= a[0]; i++) {
		if (a[i] == 1) {
			continue;
		}
		b[front] = i;
		a[i] = 1 ;
		arrange(a,b,front+1);
		a[i] = 0 ;
		b[front] = 0;
	}
}

int main() {
	
	int a[10] = { 0 };
	int b[10] = { 0 };
	cin >> a[0];
	b[0] = a[0];
	arrange(a,b,1);
	return 0;
}