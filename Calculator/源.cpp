#include<iostream>
#include"calculator.h"

using namespace std;

int main() {
	while (1) {
		cout << "��������ʽ����1+2+3="<<endl;
		calculator x;
		cout <<"�����"<< x.run()<<endl<<"����Ҫ�˳���Y/N:";
		char y;
		cin >> y;
		while(!(y == 'Y' || y == 'y' || y == 'n' || y == 'N')) {
			cout << "������Ч�����������룺";
			cin >> y;
		}
		if (y == 'Y' || y == 'y') {
			break;
		}
	}
	return 0;
}