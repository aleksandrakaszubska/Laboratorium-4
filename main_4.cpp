#define _CRT_SECURE_NO_WARNINGS 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "rk4.h"


double euler(double t0, double yp, double h, double(*fun)(double, double));
double rk4(double t0, double yp, double h, double (*fun)(double, double));
double fun(double t, double y);
double analityczna(double t, double y);

double lambda;					
double t0;						
double yp;						

void main()
{

	double tk=6.;				
	yp=3.;							// wartosc poczatkowa zmiennej zaleznej
	t0=2.;							// wartosc poczatkowa zmiennej niezaleznej
	lambda=4.;
	double h=0.1;					//krok ca³kowania
	int N;							//liczba krokow
	double blad_euler, blad_rk4;		//	blad metody Eulera oraz RK4

	double t0_n1=t0;				//zmienne pomocniczne
	double yp_n1=yp;
	double t0_n2=t0;
	double yp_n2=yp;


/*
	zad3

	printf("metoda Eulera\n");
	for(int i=0; i<((tk-t0)/h); i++)
	{

		t0_n1+=h;
		yp_n1=euler(t0_n1, yp_n1,h,fun);
		blad_euler=fabs(yp_n1-analityczna(t0_n1, yp_n1))/fabs(analityczna(t0_n1,yp_n1));
		printf("t = %lf\t", t0_n1);
		printf("y = %lf\t",yp_n1);
		printf("blad=%lf\n",blad_euler);
	
	}

	printf("\n\n");
	printf("metoda Rungego-Kutty 4-ego rzedu\n");

	for(int i=0; i<((tk-t0)/h); i++)
	{

		t0_n2+=h;
		yp_n2=rk4(t0_n2, yp_n2,h,fun);
		blad_rk4=fabs(yp_n2-analityczna(t0_n2, yp_n2))/fabs(analityczna(t0_n2,yp_n2));
		printf("t = %lf\t", t0_n2);
		printf("y = %lf\t",yp_n2);
		printf("blad=%lf\n",blad_rk4);
	}
*/
	
	
	FILE*f;										//zapisanie do pliku
	f=fopen("plik.txt", "w");

	if(f == NULL)
	{
		printf("Blad otwarcia pliku\n");
		exit(-1); 
	}



	for(int i=0; i<7; i++)
	{
		N=pow(2.,i);
		h=(tk-t0)/N;					//dlugosc kroku
		t0_n1=t0;
		yp_n1=yp;
		t0_n2=t0;
	    yp_n2=yp;
		
		
			for(int j=1; j<=N; j++)
			{
				t0_n1+=h;
				yp_n1=euler(t0_n1, yp_n1,h,fun);
			}
			
			blad_euler=fabs(yp_n1-analityczna(t0_n1, yp_n1))/fabs(analityczna(t0_n1,yp_n1));

			for(int k=1; k<=N; k++)
			{
				t0_n2+=h;
				yp_n2=rk4(t0_n2, yp_n2,h,fun);
			}

			blad_rk4=fabs(yp_n2-analityczna(t0_n2, yp_n2))/fabs(analityczna(t0_n2, yp_n2));
			

			printf("ilosc krokow %d\t\t",N);
			printf("dlugosc kroku: %10.3lf\t\t",h);
			printf("blad Eulera : %lf\t\t",blad_euler);
			printf("blad RK4 : %lf\n",blad_rk4);
		
			fprintf(f,"ilosc krokow %d\t\t",N);
			fprintf(f,"dlugosc kroku: %10.3lf\t\t",h);
			fprintf(f,"blad Eulera : %lf\t\t",blad_euler);
			fprintf(f,"blad RK4 : %lf\n",blad_rk4);
		



				
	}



fclose(f);

}
 
double euler(double t0, double yp, double h, double(*fun)(double, double))
{
	return (yp+h*fun(t0, yp));
}

double fun(double t, double y)
{
	return (lambda*y);
}

double analityczna(double t, double y)
{
	return (yp * exp(lambda * (t-t0)));
}
