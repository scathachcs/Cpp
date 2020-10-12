#include<iostream>
using namespace std;

int main(){
    int item[100][100]={0}; //每个物品的价值
    int value[100][100]={0}; //子问题最优解
    int m;
    int n;
    cin >> n; //输入行数
    cin >> m; //输入列数
    for(int i=0;i<n;i++) //输入单个物品价值
        for(int j=0;j<m;j++)
            cin>>item[i][j];
    value[n-1][m-1]=item[n-1][m-1];
    for(int i=n-2;i>=0;i--)           
        value[i][m-1]=item[i][m-1]+value[i+1][m-1];
    for(int j=m-2;j>=0;j--)
        value[n-1][j]=item[n-1][j]+value[n-1][j+1];
    for(int i=n-2;i>=0;i--)
        for(int j=m-2;j>=0;j--)
            value[i][j]=(value[i+1][j]>value[i][j+1]?value[i+1][j]:value[i][j+1])+item[i][j];
    cout<<value[0][0];
}