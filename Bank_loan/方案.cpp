#include<iostream>
#include<cmath>

int main(){
	std::cout<<"�����������"<<std::endl;
	int loans=0;
	std::cin>>loans;
	std::cout<<"������������"<<std::endl;
	int years=0;
	std::cin>>years;
	std::cout<<"������������"<<std::endl;
	double interest=0;
	std::cin>>interest;
	double A; 
	double x=loans,y=loans;
	x=pow(interest+1,years)*x;
	x/=(years*12);//xΪÿ�����޹��� 
	y/=(years*12);//yΪÿ�����޹��� 
	double estimator_loans=0;
	while(1){
		double z=0;
		z=(x+y)/2;//���ַ������ֵ 
		for(int i=1;i<=years*12;i++){
			estimator_loans+=z/pow((1+interest/12),i);
		}
		if(estimator_loans>loans){
			x=z;//�������ȹ���ֵ���ڴ����ȣ���z����A�Ĺ���ֵ 
		}
		else{
			y=z;//�������ȹ���ֵС�ڴ����ȣ���zС��A�Ĺ���ֵ
		}
		estimator_loans=0; 
		if((x-y)<=0.00001){//�������㹻Сʱ����A�Ĺ���ֵ��ֽӽ�A 
		A=x;
		estimator_loans=0;
		break;
		} 
	
	}
	std::cout<<"ÿ��Ӧ����"<<A<<std::endl;
	double monthly=interest/12;//������ʵ������ 
	double yearly=pow(1+monthly,12)-1;//������ʵ������ 
	double daily=pow(yearly+1,1.0/365)-1;//������ʵ������ 
	double biweekly=pow(1+daily,14)-1;//������ʵ˫������ 
	std::cout<<"˫�����ʣ�"<<biweekly<<std::endl; 
	int i;
	for(i=1;;i++){//����ڶ���˫�ܣ��ۼƻ������ 
		    double day;
			day=x/pow((1+biweekly),i);
			estimator_loans+=day/2.0;
			if(estimator_loans>loans){
				break;
			}
			
		}
	std::cout<<"�ķ�˫������"<<i<<std::endl;
	return 0;
} 
