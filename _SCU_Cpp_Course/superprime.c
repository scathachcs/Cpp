#include<stdio.h> 

int judge (int a);

int main ()
{
	int num,sum=0,max,i,a,b,c;
	for(i=101;i<1000;i++){
		if(judge(i)==1){
			a=i/100;
			b=(i-a*100)/10;
			c=i%10;
			if(judge(a+b+c)==1&&judge(a*a+b*b+c*c)==1&&judge(a*b*c)==1){
				num++;
				sum+=i;
				max=i;
			}
		}
	}
	printf("%d %d %d\n",num,sum,max);
	
	return 0;
}

int judge (int a)
{
	int i,flag=1;
	for(i=2;i<a;i++){
		if(a%i==0){
			flag=0;
			break;
		}
	}
	if(a<3)
	flag=0;
	return flag;
}
