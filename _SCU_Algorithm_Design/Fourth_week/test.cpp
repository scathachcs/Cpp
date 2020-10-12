#include<iostream>
using namespace std;

void Merge(int p[101][2],int q[100][2],int& countP,int countQ){
    int temp[101][2];
    int num=0;
    int i=1,j=0;
    temp[0][0]=p[0][0];
    temp[0][1]=p[0][1];
    for(;i!=countP&&j!=countQ;){
          if(p[i][0]<=q[j][0]){
              if(p[i][1]>temp[num][1]){
                num++;
                temp[num][0]=p[i][0];
                temp[num][1]=p[i][1];
                i++;
              }
              else{
                  i++;
              }
          }
          else{
              if(q[j][0]==temp[num][0]){
                  temp[num][1]=temp[num][1]>q[j][1]?temp[num][1]:q[j][1];
                  j++;
              }
              else if(q[j][1]>temp[num][1]){
                  num++;
                  temp[num][0]=q[j][0];
                  temp[num][1]=q[j][1];
                  j++;
              }
              else{
                  j++;
              }
          } 
    }
    for(;i!=countP;){
        if(p[i][1]>temp[num][1]){
                  num++;
                  temp[num][0]=p[i][0];
                  temp[num][1]=p[i][1];
                  i++;
        }
    }
    for(;j!=countQ;){
        if(q[j][0]==temp[num][0]){
            temp[num][1]=temp[num][1]>q[j][1]?temp[num][1]:q[j][1];
            j++;
        }
        else if(q[j][1]>temp[num][1]){
                  num++;
                  temp[num][0]=q[j][0];
                  temp[num][1]=q[j][1];
                  j++;
              }
    }
    countP = num+1;
    for(int i=0;i<countP;i++){
        p[i][0]=temp[i][0];
        p[i][1]=temp[i][1];
    }
}

int DP(int *magic,int* summon,int* cnt,int N,int V){
    int p[101][2]={{0,0}};//0为跳跃点x坐标，1为跳跃点y坐标
    int q[100][2]={{0,0}};
    int count=1;
    N=N-1;
    int i=cnt[N];
    int j=0;
    while(N>=0){
        i--;
        for(j=0;j<count;j++){
            if(p[j][0]+summon[N]>V){
                break;
            }
            q[j][0]=p[j][0]+summon[N];
            q[j][1]=p[j][1]+magic[N];
        }
        Merge(p,q,count,j);
        if(i==0){
            N--;
            if(N>=0)
            i=cnt[N];
        }
    }
    return p[count-1][1];
}

int main (){
    int T;
    int K[10];    
    cin>>T;
    for(int t=0;t<T;t++){
        int N;
        cin>>N;
        int V;
        cin>>V;
        int magic[10];
        int summon[10];
        int cnt[10];
        for(int i=0;i<N;i++){
            cin>>magic[i];
        }
        for(int i=0;i<N;i++){
            cin>>summon[i];
        }
        for(int i=0;i<N;i++){
            cin>>cnt[i];
        }
        K[t]=DP(magic,summon,cnt,N,V);
    }
    for(int t=0;t<T;t++){
        cout<<K[t]<<endl;
    }
}
