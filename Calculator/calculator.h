#pragma once
#include<iostream>
#include<stack>
#include<string>
using namespace std;

class calculator {
private:
	char ch;
	char prech;
	double num;
	stack<double> opnd;
	stack<char> optr;
	string result;
public:
	calculator() {

	}
	~calculator() {

	}
	

	string run() {
		optr.push('=');
		prech = '=';
		cin >> ch;
		do {
			if (!isop(ch)) {
				cin.putback(ch);
				cin >> num;
				opnd.push(num);
				prech = '0';
				cin >> ch;
			}
			else {
				if ((prech == '=' || prech == '(') && (ch == '+' || ch == '-')) {
					opnd.push(0);
				}
				double x;
				double y;
				char z;
				switch (Precede(optr.top(), ch)) {
				case'<':
					optr.push(ch);
					prech = ch;
					cin >> ch;
					break;
				case'=':
					optr.pop();
					if(ch!='='||!optr.empty())
					cin >> ch;					
					break;
				case'>':
					x = opnd.top();
					opnd.pop();
					y = opnd.top();
					opnd.pop();
					z = optr.top();
					optr.pop();
					num = Operator(x,y,z );
					opnd.push(num);
					break;
				case'e':
					return "error";
				}
			}
		} while (!optr.empty());
		num = opnd.top();
		result=to_string(num);
		return result;
	}

	bool isop(char ch) {
		switch (ch) {
		case'+':
		case'-':
		case'*':
		case'/':
		case'=':
		case'(':
		case')':
			return true;
		default:
			return false;
		}
	}
	char Precede(char x, char y) {
		switch (x) {

		case '+':
		case '-':
			switch (y) {
			case'*':
			case'/':
			case'(':
				return '<';
			default:
				return '>';
			}

		case '*':
		case '/':
			switch (y) {
			case'(':
				return '<';
			default:
				return '>';
			}

		case '(':
			switch (y) {
			case')':
				return '=';
			case'=':
				return 'e';
			default:
				return '<';
			}

		case ')':
			switch (y) {
			case'(':
				return 'e';
			default:
				return '>';
			}

		case '=':
			switch (y) {
			case')':
				return 'e';
			case'=':
				return '=';
			default:
				return '<';
			}
		}
	}
	double Operator(double x, double y, char z) {
		switch (z) {
		case'+':
			return x + y;
		case'-':
			return y - x;
		case'*':
			return x * y;
		case'/':
			return y / x;
		}
		return 0;
	}
 };