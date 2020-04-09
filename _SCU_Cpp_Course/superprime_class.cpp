#include<iostream>


class prime {
public:
	int judgep(int a);
};

class superprime {
public:
	superprime();
	int judgesp(int i);
	int show();
private:
	int num, max, sum;
};

int main()
{
	superprime superprimex;
	for (int i = 100; i < 1000; i++) {
		superprimex.judgesp(i);
	}
	superprimex.show();
	return 0;
}

int prime::judgep(int a) {
	int i, flag = 1;
	for (i = 2; i < a; i++) {
		if (a % i == 0) {
			flag = 0;
			break;
		}
	}
	if (a < 2)
		flag = 0;
	return flag;
};
int superprime::judgesp(int i) {
	int a, b, c;
	prime primex;
	a = i / 100;
	b = (i - a * 100) / 10;
	c = i % 10;
	if (primex.judgep(a + b + c) == 1 && primex.judgep(a * a + b * b + c * c) == 1 && primex.judgep(a * b * c) == 1) {
		num++;
		sum += i;
		max = i;
	};
	return 0;
}

int superprime::show() {
	std::cout<<max<<" "<<num<<" "<<sum<<std::endl;
	return 0;
}

superprime::superprime() {
	sum = 0, max = 0, num = 0;
}
