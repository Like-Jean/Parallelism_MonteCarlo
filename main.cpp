#include "pi.h"
#include "rand_generator.h"
#include "stock_price.h"

void main()
{
	cout<<"thread num:"<<omp_get_num_procs()<<endl;
	int n=10000000;
	cout<<"generate "<<n<<" times"<<endl;
	/*-------calculate pie----------*/
	cout<<squreCirclePie(10,n);
	/*-------simulate option price--*/
	
	//optionSimulator(n,253);
}

