#include <iostream>
#include <string>

class DotArray {   //点阵对象
	const int maxcol, maxrow;
public:
	DotArray() :maxcol(5), maxrow(7) {
	}
	virtual void showrow(int i) const = 0;
	virtual ~DotArray() {

	}
};

class DA0 : public DotArray {   //0的点阵
private:
	std::string row[7];
public:
	DA0() {
		row[0] = "*****";
		row[1] = "*   *";
		row[2] = "*   *";
		row[3] = "*   *";
		row[4] = "*   *"; 
		row[5] = "*   *"; 
		row[6] = "*****";

	};
	~DA0() {
	};
	virtual void showrow(int i) const {
		std::cout << row[i]<<"  ";
	};
	
};
class DA1 : public DotArray {   //1的点阵
	std::string row[7];
public:
	DA1() {
		row[0] = "    *";
		row[1] = "    *";
		row[2] = "    *";
		row[3] = "    *";
		row[4] = "    *";
		row[5] = "    *";
		row[6] = "    *";
	};
	~DA1() {
	};
	virtual void showrow(int i) const {
		std::cout << row[i] << "  ";
	};
};

class DA2 : public DotArray {   //2的点阵
	std::string row[7];
public:
	DA2() {
		row[0] = "*****";
		row[1] = "    *";
		row[2] = "    *";
		row[3] = "*****";
		row[4] = "*    ";
		row[5] = "*    ";
		row[6] = "*****";
	};
	~DA2() {
	};
	virtual void showrow(int i) const {
		std::cout << row[i] << "  ";
	};
};
class DA3 : public DotArray {   //3的点阵
	std::string row[7];
public:
	DA3(){
		row[0] = "*****";
		row[1] = "    *";
		row[2] = "    *";
		row[3] = "*****";
		row[4] = "    *";
		row[5] = "    *";
		row[6] = "*****";
	};
	~DA3() {
	};
	virtual void showrow(int i) const {
		std::cout << row[i] << "  ";
	};
};
class DA4 : public DotArray {   //4的点阵
	std::string row[7];
public:
	DA4()  {
		row[0] = "*   *";
		row[1] = "*   *";
		row[2] = "*   *";
		row[3] = "*****";
		row[4] = "    *";
		row[5] = "    *";
		row[6] = "    *";
	};
	~DA4() {
	};
	virtual void showrow(int i) const {
		std::cout << row[i] << "  ";
	};
};
class DA5 : public DotArray {   //5的点阵
	std::string row[7];
public:
	DA5(){
		row[0] = "*****";
		row[1] = "*    ";
		row[2] = "*    ";
		row[3] = "*****";
		row[4] = "    *";
		row[5] = "    *";
		row[6] = "*****";
	};
	~DA5() {
	};
	virtual void showrow(int i) const {
		std::cout << row[i] << "  ";
	};
};
class DA6 : public DotArray {   //6的点阵
	std::string row[7];
public:
	DA6() {
		row[0] = "*****";
		row[1] = "*    ";
		row[2] = "*    ";
		row[3] = "*****";
		row[4] = "*   *";
		row[5] = "*   *";
		row[6] = "*****";
	};
	~DA6() {
	};
	virtual void showrow(int i) const {
	std::cout << row[i] << "  ";
	};
};
class DA7 : public DotArray {   //7的点阵
	 std::string row[7];
public:
	DA7()  {
		row[0] = "*****";
		row[1] = "    *";
		row[2] = "    *";
		row[3] = "    *";
		row[4] = "    *";
		row[5] = "    *";
		row[6] = "    *";
	};
	~DA7() {
	};
	virtual void showrow(int i) const {
		std::cout << row[i] << "  ";
	};
};
class DA8 : public DotArray {   //8的点阵
	std::string row[7];
public:
	DA8(){
		row[0] = "*****";
		row[1] = "*   *";
		row[2] = "*   *";
		row[3] = "*****";
		row[4] = "*   *";
		row[5] = "*   *";
		row[6] = "*****";
	};
	~DA8() {
	};
	virtual void showrow(int i) const {
		std::cout << row[i] << "  ";
	};
};
class DA9 : public DotArray {   //9的点阵
	 std::string row[7];
public:
	DA9() {
		row[0] = "*****";
		row[1] = "*   *";
		row[2] = "*   *";
		row[3] = "*****";
		row[4] = "    *";
		row[5] = "    *";
		row[6] = "*****";
	};
	~DA9() {
	};
	virtual void showrow(int i) const {
		std::cout << row[i] << "  ";
	};
};
class DAPrinter {
private:
	const int num;
	int i;
	DotArray* das[4]; //最多4个点阵对象
public:
	DAPrinter(int n) :num(n) {
		i = 0;
	}
	~DAPrinter() {
		for (; i >= 0; i--) {
			delete[] das[i];
		}

	}
	void split() {
		int n = num;
		int x = 0;
		while (1) {
			x = n % 10;
			n = n / 10;
			switch (x) {
			case 0:
				das[i] = new DA0;
				break;
			case 1:
				das[i] = new DA1;
				break;
			case 2:
				das[i] = new DA2; 
				break;
			case 3:
				das[i] = new DA3;
				break;
			case 4:
				das[i] = new DA4;
				break;
			case 5:
				das[i] = new DA5;
				break;
			case 6:
				das[i] = new DA6; 
				break;
			case 7:
				das[i] = new DA7;
				break;
			case 8:
				das[i] = new DA8;
				break;
			case 9:
				das[i] = new DA9;
				break;
			}
			if (n == 0)
				break;
			i++;
		}
	};
	
	void print() {
		std::cout << num << ":" <<std:: endl;
		for (int j = 0; j < 7; j++) {
			for (int k = i; k >=0; k--) {
				das[k]->showrow(j);
			}
			std::cout << std::endl;
		}
	};
	void reset() {
		for (; i >= 0; i--) {
			delete[] das[i];
		}
	};
	
};
int main() {
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int n1;
		std::cin >> n1;
		DAPrinter p(n1);
		p.split();
		p.print();
	}
	return 0;
}