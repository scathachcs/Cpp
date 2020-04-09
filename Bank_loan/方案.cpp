#include<iostream>
#include<cmath>

int main(){
	std::cout<<"请输入贷款额度"<<std::endl;
	int loans=0;
	std::cin>>loans;
	std::cout<<"请输入总年限"<<std::endl;
	int years=0;
	std::cin>>years;
	std::cout<<"请输入年利率"<<std::endl;
	double interest=0;
	std::cin>>interest;
	double A; 
	double x=loans,y=loans;
	x=pow(interest+1,years)*x;
	x/=(years*12);//x为每月上限估计 
	y/=(years*12);//y为每月下限估计 
	double estimator_loans=0;
	while(1){
		double z=0;
		z=(x+y)/2;//二分法求估计值 
		for(int i=1;i<=years*12;i++){
			estimator_loans+=z/pow((1+interest/12),i);
		}
		if(estimator_loans>loans){
			x=z;//若贷款额度估计值大于贷款额度，则z大于A的估计值 
		}
		else{
			y=z;//若贷款额度估计值小于贷款额度，则z小于A的估计值
		}
		estimator_loans=0; 
		if((x-y)<=0.00001){//当精度足够小时，即A的估计值充分接近A 
		A=x;
		estimator_loans=0;
		break;
		} 
	
	}
	std::cout<<"每月应还："<<A<<std::endl;
	double monthly=interest/12;//计算真实月利率 
	double yearly=pow(1+monthly,12)-1;//计算真实年利率 
	double daily=pow(yearly+1,1.0/365)-1;//计算真实日利率 
	double biweekly=pow(1+daily,14)-1;//计算真实双周利率 
	std::cout<<"双周利率："<<biweekly<<std::endl; 
	int i;
	for(i=1;;i++){//计算第多少双周，累计还款完成 
		    double day;
			day=x/pow((1+biweekly),i);
			estimator_loans+=day/2.0;
			if(estimator_loans>loans){
				break;
			}
			
		}
	std::cout<<"耗费双周数："<<i<<std::endl;
	return 0;
} 
