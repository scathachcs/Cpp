#include<iostream>
#include<string>
#include<fstream>
#include "Editor.h"
using namespace std;

int main() {
	string filename;
	while (1) {
		cout << "请输入文件名：";
		cin >> filename;
		Editor test1(filename);
		test1.Run();
	}
	return 0;

}