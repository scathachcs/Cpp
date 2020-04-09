#include<iostream>

using namespace std;

double SumOfList(double* a, int* b) {
	double sum = 0;
	for (int i = 1; i <= a[0]; i++) {
		if (b[i] != 0)
			sum += a[i];
	}
	return sum;
}


bool SumOfPart(double* a, int* b, int front, double target) {
	if (front > a[0])
		return target == SumOfList(a, b);
	for (int i = front; i <= a[0]; i++) {
		b[i] = 1;
		if (SumOfPart(a, b, i + 1, target))
			return true;
		b[i] = 0;
		if (i = a[0]) {
			if (SumOfPart(a, b, i + 1, target))
				return true;
		}
		
	}
	return false;
}


int main() {
	double a[21] = { 0 };
	int b[21] = { 0 };
	cin >> a[0];
	double target;
	cin >> target;
	for (int i = 1; i <= a[0]; i++) {
		cin >> a[i];
	}
	
	if (SumOfPart(a, b, 1, target))
		cout << "YE5"<<endl;
	else
		cout << "N0"<<endl; 
	return 0;
}

