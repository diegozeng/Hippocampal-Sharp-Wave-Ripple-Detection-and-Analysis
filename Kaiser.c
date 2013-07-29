#include<math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define PI 3.1415926535 

static double bessel0(double x)
{
	int i;
	double d,y,d2,sum;
	y=x/2.0;
	d=1.0;
	sum=1.0;
	for(i=1;i<=25;i++)
		{
			d=d*y/i;
			d2=d*d;
			sum=sum+d2;
			if(d2<sum*(1.0e-8))
				break;
		}
	return(sum);
}

int main(int *W)
//int KAIS(int *W)
{
	
	int a = 1;
	FILE * fp = fopen("data.txt", "w");
	if(fp == NULL)
	{	
		printf("open file wrong!\n");
	}
	while(a)
	{
	int j;
	double EPS = 0.00001;
	double *beta = 0;
	double *beta1 = 0;
	double *win = 0;
	double *X = 0;
	double *Y = 0;
//	int *W = 0;
	double *Z = 0;
	double be,fs1,fp1,fp2,fs2,delta,alfa,N,M,fs;
	//int res2;
	printf("pls input first sidelobe attenuation:\n");
	scanf("%lf",&alfa);
	printf("pls input sampling frequency fs:\n");
	scanf("%lf",&fs);
	printf("pls input fs1:\n");
	scanf("%lf",&fs1);
	fs1=fs1/fs;
	printf("pls input fp1:\n");
	scanf("%lf",&fp1);
	fp1=fp1/fs;
	printf("pls input fp2:\n");
	scanf("%lf",&fp2);
	fp2=fp2/fs;
	printf("pls input fs2:\n");
	scanf("%lf",&fs2);
	fs2=fs2/fs;
	
	if ((fp1 - fs1) > (fs2 - fp2))
		delta = fs2- fp2;
	else 
		delta = fp1-fs1;
	M = (alfa-7.95)/(14.36*delta)+1;
	N = ceil(M);
	fprintf(fp, "%lf,", N);
	printf("\n");
	printf("Output parameters:\n");
	printf("The filter's order is:\n");
	printf("%lf\n",N-1);
	printf("The window length is:\n");
	printf("%lf\n",N);
	if (alfa>=50.0)
		be = 0.1102*(alfa-8.7);
	if (21.0<alfa<50.0)
	    be = 0.5842*pow(alfa-21.0,0.4)+0.07886*(alfa-21);
	else 
		be = 0;
	//printf("Please type the normalized band-width (0 to 1) of the filter\n");
	//res2 = scanf("%f",&b);
	//getchar();
	//	while(!res2)
	//		{
	//			printf("Input error\n");
	//			printf("Please type the normalized band-width (0 to 1) of the filter\n");
	//			res2 = scanf("%f",&b);
	//			getchar();
	//		}
		//printf("%f",b);
	//	c = PI*(1.0 - b) / 2;
	//	d = PI-c;
	beta = (double*)malloc(sizeof(double)*N);
		memset(beta, 0, sizeof(double)*N);
	beta1 = (double*)malloc(sizeof(double)*N);
		memset(beta1, 0, sizeof(double)*N);
	win = (double*)malloc(sizeof(double)*N);
		memset(win, 0, sizeof(double)*N);
	W = (int*)malloc(sizeof(int)*N);
		memset(W, 0, sizeof(int)*N);
    X = (double*)malloc(sizeof(double)*N);
		memset(X, 0, sizeof(double)*N);
    Y = (double*)malloc(sizeof(double)*N);
		memset(Y, 0, sizeof(double)*N);
	Z = (double*)malloc(sizeof(double)*N);
		memset(Z, 0, sizeof(double)*N);
	printf("The impulse response h[n] are:\n");
	for(j = 0; j <N; j++)
		{
			X[j]=X[j]+j;
			//printf("%d\n",X[j]);
			beta[j]=beta[j]+be;
			//printf("%lf\n",beta[j]);
			beta1[j]=beta[j]*sqrt(1.0-((2.0*X[j])/(N-1.0)-1.0)*((2.0*X[j])/(N-1.0)-1.0));
			//printf("%lf\n",beta1[j]);
			beta1[j] = bessel0(beta1[j]);
			//printf("%lf\n",beta1[j]);
			beta[j] = bessel0(beta[j]);
			//printf("%lf\n",beta[j]);
			win[j]=beta1[j]/beta[j];
			//printf("%lf\n",win[j]);
				//printf("\n");
			Y[j]=Y[j]+j;
				if (fabs(Y[j]-(N-1.0)/2.0) < EPS)
					Y[j] = fs2+fp2-fs1-fp1;
				else
					Y[j] = sin((PI*fs2 + PI*fp2)*(Y[j]-(N-1.0)/2.0))/(PI*(Y[j]-(N-1.0)/2.0))-sin((PI*fs1 + PI*fp1)*(Y[j]-(N-1.0)/2.0))/(PI*(Y[j]-(N-1.0)/2.0));
				//printf("%lf\n",Y[j]);
				Z[j] = Y[j]*win[j];
				//printf("%.15lf\n",Z[j]);
				//fprintf(fp, "%.15lf,",Z[j]);
				Z[j]= Z[j]*pow(2.0,32);
				W[j]= (int)(Z[j]+0.5);
				printf("%d\n",W[j]);
				fprintf(fp, "%d,",W[j]);
		}
		printf("\n");
		printf("again?(Type 0 to exit)");
		scanf("%d",&a);
		getchar();
	}
	fclose(fp);
	return 0;
}

