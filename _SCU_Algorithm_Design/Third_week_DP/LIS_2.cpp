#include<iostream>
using namespace std;


int main()
{
	int* a = new int[100001];
	int* b = new int[100001];
	a[0] = 0;
	b[0] = 0;
	int num;
	cin >> num;
	for (int i = 1; i <= num; i++) {
		cin >> a[i];
		b[i] = 0x7fffffff;
	}
		
	b[1] = a[1];
	int len = 1;
	for (int i = 2; i <= num; i++)
	{
		
		if (a[i] > b[len]) {
			len++;
			b[len] = a[i];
		}
		else 
		{
			int l = 1;
			int r = len;
			int mid;
			while (l < r) {
				mid = (l + r) / 2;
				if (a[mid] < a[i])
					l = mid + 1;
				else
					r = mid - 1;
			}
			b[l] = a[i];
		}
	}
	cout<<len<<endl;
	delete[] a;
	delete[] b;
	return 0;
}