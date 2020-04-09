#include<iostream>
#include"calculator.h"

using namespace std;

int main() {
	while (1) {
		cout << "请输入表达式：如1+2+3="<<endl;
		calculator x;
		cout <<"结果："<< x.run()<<endl<<"请问要退出吗Y/N:";
		char y;
		cin >> y;
		while(!(y == 'Y' || y == 'y' || y == 'n' || y == 'N')) {
			cout << "输入无效，请重新输入：";
			cin >> y;
		}
		if (y == 'Y' || y == 'y') {
			break;
		}
	}
	return 0;
}