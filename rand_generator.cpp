#include "rand_generator.h"

const double PI= 3.14159265358979323846 ;
unsigned long y=time(0);//seed for LCG generator
/*-------generate uniform distributed rand (0,1)------*/
double LCGrand(){
	unsigned long m=(1<<31)-1;
	unsigned long a=16807;
	unsigned long c=0;
    y=(a*y+c)%m;
    return (double)y/m;
}
/*-------generate standard normal distributed rand------*/
double box_MullerRand(){
	double u1=LCGrand();
	double u2=LCGrand();
	return pow(-2*log(u1),0.5)*cos(2*PI*u2);
}