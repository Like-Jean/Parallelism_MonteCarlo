#include "stock_price.h"
#include "rand_generator.h"

class HisPrice{
public:
	double miu;
	double std;
	double lastPrice;
	HisPrice(){
		getHPrices_noP();
	}
	void getHPrices_noP(){//read and calculate miu at sametime (we can't paralle when using vector.pushback())
		clock_t t1 = clock();
		ifstream fin("table1.csv");
		string line;
		vector<double> daily_return; 
		double returnp;
		double price;
		double sum_miu=0.0;
		double sum_std=0.0;
		/*-----read file------*/
		getline(fin, line);
		double yesterday_p=-1;
		while(getline(fin, line)){
			price=stod(line,NULL);
			if(yesterday_p!=-1){
				returnp=(price-yesterday_p)/yesterday_p;
				daily_return.push_back(returnp); 
				sum_miu+=returnp;
			}
			else{
				lastPrice=price;
			}
			yesterday_p=price;
			//cout<<price<<endl;
			
		}
		int pricesN=daily_return.size();
		/*-----calculate miu----*/
		miu=sum_miu/pricesN;
		/*-----calculate std----*/
		#pragma omp parallel for reduction(+:sum_std)
		for(int i=0;i<pricesN;i++){
			sum_std+=pow(miu-daily_return[i],2.0);
		}
		std=pow(sum_std/pricesN,0.5);
		clock_t t2 = clock();
		cout<<"read file and calculate miu and std time:"<<double(t2-t1)/1000<<endl;
	}
};

double optionPriceSimulator(double miu,double std,double lastPrice){//step is 1 day, T is 1 year(365 days)
	return lastPrice*exp((miu-0.5*pow(std,2.0))+std*box_MullerRand());
}

void optionSimulator(unsigned long time,int T){
	HisPrice hp=HisPrice();
	double optionPrice;
	double sum=0;
	clock_t t1;
	clock_t t2;
	ofstream fout;
	
    fout.open("price_out500000.csv",ios::out/*|ios::app*/);
	t1=clock();
	#pragma omp parallel for reduction(+:sum)
	for(int i=0;i<time;i++){
		int t=1;
		double price=hp.lastPrice;
		while(t<=T){
			price=optionPriceSimulator(hp.miu,hp.std,price);
			t++;
		}
		#pragma omp critical
			{
				fout<<price<<endl;
			}
		sum+=price;
	}
	fout.close();
	t2=clock();
	cout<<"stock price calculating time:"<<(double)(t2-t1)/1000<<endl;
	cout<<"simulated price in 06/01/2017:"<<sum/time<<endl;
}