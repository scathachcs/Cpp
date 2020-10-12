#include<iostream>
#include<queue>
using namespace std;

struct Point{           //储存每个腐烂的橘子的坐标
    int x;
    int y;
};

int Orange(int map[3][3]){
    queue<Point> q;         //存放刚腐烂的橘子坐标的队列
    struct Point point;
    int minutes = 0;        //过了第几分钟
    int num=0;             //完好的橘子
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            if(map[i][j]==2){   //将第0分钟时腐烂的橘子的坐标放入队列
                point.x=i;
                point.y=j;
                q.push(point);
            }
            if(map[i][j]==1)   //计算完好的橘子
                num++;
        }
    int nextsize=q.size();     //队列里面新增数量
    int cursize=0;              //队列里面已有的腐烂橘子数量，即本轮影响其他橘子腐烂的橘子数量
    while(q.size()!=0 && num!=0){
        cursize = nextsize;
        nextsize = 0;
        while(cursize--){
            point=q.front();     //取出队列中的橘子
            q.pop();
            int i=point.x;
            int j=point.y;
            if(i>0 && map[i-1][j]==1){  //计算上方
                point.x=i-1;
                point.y=j;
                q.push(point);
                map[i-1][j]=2;
                nextsize++;
                num--;
            }    
            if(i<2 && map[i+1][j]==1){  //计算下方
                point.x=i+1;
                point.y=j;
                q.push(point);
                map[i+1][j]=2;
                nextsize++;
                num--;
            }        
            if(j>0 && map[i][j-1]==1){  //计算左方
                point.x=i;
                point.y=j-1;
                q.push(point);
                map[i][j-1]=2;
                nextsize++;
                num--;
            }
            if(j<2 && map[i][j+1]==1){  //计算右方
                point.x=i;
                point.y=j+1;
                q.push(point);
                map[i][j+1]=2;
                nextsize++;
                num--;
            }
        }
        minutes++;
    }
    if(num==0)  //判断是否还有橘子剩余
        return minutes;
    else 
        return -1;
}
int main(){
    int map[3][3];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            cin >> map[i][j];
    cout<<Orange(map);
    return 0;
}