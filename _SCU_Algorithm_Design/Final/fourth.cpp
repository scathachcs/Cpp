#include<iostream>
#include<string.h>
using namespace std;
char board[3][4] =
{
  {'A','B','C','E'},
  {'S','F','C','S'},
  {'A','D','E','E'}
};

int used[3][4]= {0};           //存放是否被使用过

int n;

void backtrack(char word[],int t,int row,int col,bool &flag){
    if(t >= n){                     //判断是否搜索完毕
        flag = true;
        return;
    }
        
    if(row > 0 && used[row-1][col] == 0 && board[row-1][col]==word[t]&&!flag){   //向左搜索，若左边无或者被使用过，则剪枝
        used[row-1][col]=1;
        backtrack(word,t+1,row-1,col,flag);
        used[row-1][col]=0;
    }
        
    if(row < 2 && used[row+1][col] == 0 && board[row+1][col]==word[t]&&!flag){   //向右搜索，若右边无或者被使用过，则剪枝
        used[row+1][col]=1;
        backtrack(word,t+1,row+1,col,flag);
        used[row+1][col]=0;
    }
        
    if(col > 0 && used[row][col-1] == 0 && board[row][col-1]==word[t]&&!flag){   //向上搜索，若上边无或者被使用过，则剪枝
        used[row][col-1]=1;
        backtrack(word,t+1,row,col-1,flag);
        used[row][col-1]=0;
    }
        
    if(col < 3 && used[row][col+1] == 0 && board[row][col+1]==word[t]&&!flag){  //向下搜索，若下边无或者被使用过，则剪枝
        used[row][col+1]=1;
        backtrack(word,t+1,row,col+1,flag);
        used[row][col+1]=0;
    }
        
}

int main(){
    char word[100] = {'\0'};
    while(cin>>word){
        bool flag = false;
        n = strlen(word);
        for(int i = 0; i<3;i++)          //寻找第一个匹配字符
            for(int j = 0 ; j<4;j++)
                if(board[i][j]==word[0])
                    backtrack(word,1,i,j,flag);
        if(flag)
        cout<<"true\n";
        else
        cout<<"false\n";
    }
    return 0;
}
