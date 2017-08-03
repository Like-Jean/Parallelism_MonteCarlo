#include "rand_generator.h"
#include "pi.h"
#include <time.h>
#include <iostream>

double squreCirclePie(double r,unsigned long n){
	double x;
	double y;
	double dis;
	clock_t t1;
	clock_t t2;
	unsigned long num=0;
	double powR=pow(r,2.0);
	double seed=time(0);
	t1=clock();
	#pragma omp parallel for reduction(+:num)
	for(int i=0;i<n;i++){
		x=LCGrand()*2*r;
		y=LCGrand()*2*r;
		
		//cout<<x<<' '<<y<<endl;
		dis=pow(r-x,2.0)+pow(r-y,2.0);
		if(dis<=powR) {
			num=num+1;
		}
	}	
	t2=clock();
	cout<<"time:"<<double(t2-t1)/1000<<endl;
	return (double)num/n*4;

}