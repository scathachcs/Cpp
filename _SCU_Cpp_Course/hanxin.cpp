#include<iostream>

class HanXin {
public:
	void line3(int a) {
		n1 = a;
	};
	void line5(int b) {
		n2 = b;
	};
	void line7(int c) {
		n3 = c;
	};
	void showMany(){
	int j = 0;
	for (int i = 10; i < 100; i++) {
		if (i % 3 == n1 && i % 5 == n2 && i % 7 == n3) {
			j = i;
			break;
		}
	}
	if (j != 0) {
		std::cout << j << std::endl;
	}
	else {
		std::cout << "Impossible" << std::endl;
	}
};
private:
	int n1, n2, n3;
};

int main() {
	int n, n1, n2, n3;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> n1 >> n2 >> n3;
		HanXin hx;  //韩信
		hx.line3(n1);  //3人一排
		hx.line5(n2);   //5人一排
		hx.line7(n3);   //7人一排
		hx.showMany();
	}
	return 0;
}
