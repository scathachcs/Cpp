#include<iostream>
using namespace std;

double Power(double base, int exponent){
    if(exponent == 0)
        return 1;

    return base*Power(base,exponent-1);
}

int main(){
    int exponent;
    double base;
    while(cin >> base){
        cin >> exponent;
        printf("%.5f\n",Power(base,exponent));
        
    }
    return 0;
}

