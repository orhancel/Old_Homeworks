#include <stdio.h>

#include <math.h>
#include <cmath>   
#include <iostream>
using namespace std;

#define _USE_MATH_DEFINES






double Bisection(double a,double b,int &iter,double epsilon,double p,int criterion){/////////////ENTER FUNCTIN HERE////////ENTER FUNCTIN HERE////////ENTER FUNCTIN HERE////////

	double mid=0;
	mid=(a+b)/2;////ORTALAMA DEGER

	double f=0;

	double x=mid;

	f=2*x+3*cos(x)-exp(x);//////////////ENTER FUNCTIN HERE////////ENTER FUNCTIN HERE////////ENTER FUNCTIN HERE////////ENTER FUNCTIN HERE////////ENTER FUNCTIN HERE////////ENTER FUNCTIN HERE////



	iter+=1;
	printf("iterasyon=%d  ABSOLUTE_ERROR=%lf  RELATIVE_ERROR=%lf  ROOT=%lf ppp=%lf \n",iter,abs(mid-p),  abs(mid-p)/abs(mid)  ,mid,p);
	if(mid<=0.00000000001){
		printf("\nP equals 0\n");
		exit(1);
	}
	if(iter>=100){
		printf("\n100 iterasyon\n");
		return 0;
	}

	switch (criterion){
		case 1:	
				if(abs(f)<epsilon ){/////////////////Distance to root///DISTANCE TO ROOT////////
					
					return mid;

				}
				else
				{


					if(f>0){
						b=mid;
						
						return Bisection(a,b,iter,epsilon,p,criterion);
					}
					else{
						
						a=mid;
						return Bisection(a,b,iter,epsilon,p,criterion);
					}
				}
				break;


		case 2:///////////////////ABSOLUTE ERROR////ABSOLUTE ERROR////ABSOLUTE ERROR////ABSOLUTE ERROR////ABSOLUTE ERROR///
				if(iter==1)
				{
					p=mid;
					if(f>0){
						b=mid;
						
						return Bisection(a,b,iter,epsilon,p,criterion);
					}
					else{
						
						a=mid;
						return Bisection(a,b,iter,epsilon,p,criterion);
					}

				}
				else
				{
					if(abs(mid-p)<epsilon)
						return mid;
					else{
						if(f>0){
							p=mid;
							b=mid;
							
							return Bisection(a,b,iter,epsilon,p,criterion);
						}
						else{
							p=mid;
							a=mid;
							return Bisection(a,b,iter,epsilon,p,criterion);
						}

					}
				}
				break;


		case 3:////RELATIVE ERROR//////RELATIVE ERROR//////RELATIVE ERROR//////RELATIVE ERROR//////RELATIVE ERROR////
				if(iter==1)
				{
					p=mid;
					if(f>0){
						b=mid;
						
						return Bisection(a,b,iter,epsilon,p,criterion);
					}
					else{
						
						a=mid;
						return Bisection(a,b,iter,epsilon,p,criterion);
					}

				}
				else
				{
					if(abs(mid-p)/abs(mid)<epsilon)
						return mid;
					else{
						if(f>0){
							p=mid;
							b=mid;
							
							return Bisection(a,b,iter,epsilon,p,criterion);
						}
						else{
							p=mid;
							a=mid;
							return Bisection(a,b,iter,epsilon,p,criterion);
						}

					}
				}
				break;
	

	

	
	}

	



}




int main (int argc, char** argv) {
	double a;
	double b;
	double epsilon;
	double p=0.1;
	int iter=0;
	int criter=0;
	string criterion;


	a=atof(argv[1]);
	
	b=atof(argv[2]);
	
	criterion=argv[3];


	epsilon=atof(argv[4]);
	
	
	if(criterion=="DISTANCE_TO_ROOT"){
	
		criter=1;
	}
	else if(criterion=="ABSOLUTE_ERROR"){
		
		criter=2;
	}
	else if(criterion=="RELATIVE_ERROR"){
		
		criter=3;
	}
	a=Bisection(a,b,iter,epsilon,p,criter);


}


