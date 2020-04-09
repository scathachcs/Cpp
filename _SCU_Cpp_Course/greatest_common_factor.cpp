#include<iostream>

class Number {
public:
	Number(int n1){
	n = n1;
}
	int maxDivisor(Number n2) {
	int a=n, b=n2.n, c=0;
	while(a != b) {
		if (a < b){
			c = a;
			a = b;
			b = c;
		}
			c = b;
			b = a - b;
			a = c;
	}
	c = a;
	return c;
}
	void show(){
	std::cout << n << std::endl;
}
	private:
	int n;
};

int main() {
	int n, n1, n2;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> n1 >> n2;
		Number no1(n1), no2(n2);
		Number no3 =no1.maxDivisor(no2);  //最大公约数
		no3.show();
	}
	return 0;
}

