#include<iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int num[100]={0};
    for(int i = 0;i < n; i++)
        cin>>num[i];
    int pos = 0;  //当前位置
    int lens = 0; //当前位置可走长度
    int lastfar = 0;//上次可走最远距离
    int step = 0; //已走步数
    if(n==1){  //当起始点即为目的地时
        cout<<0;
        return 0;
    }

    while(1){
        step++;
        int curfar = pos + num[pos]; //当前位置可到达最远距离
        if(curfar>=n-1)         //若当前位置可到达最远距离大于终点，则退出循环
            break;
        int nextfar = curfar;   //下一位置可到达最远距离
        for(int i = lastfar+1 ; i <=curfar; i++){
            if(i+num[i]>nextfar){   //若下一位置可到达最远距离能更大，则更新
                nextfar=i+num[i];
                pos = i;
            }
        }
        lastfar = curfar;
    }


    cout<<step;
    return 0;
}