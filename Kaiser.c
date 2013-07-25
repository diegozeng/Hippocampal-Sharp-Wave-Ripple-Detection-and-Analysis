#include<math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define PI 3.1415926535 

static float bessel0(float x)
{
  int i;
	float d,y,d2,sum;
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

int main(void)
{
	int a = 1;
	while(a)
	{
	int j;
	float EPS = 0.00001;
	float *beta = 0;
	float *beta1 = 0;
	float *win = 0;
	float *X = 0;
	float *Y = 0;
	int *W = 0;
	float *Z = 0;
	float be,fs1,fp1,fp2,fs2,delta,alfa,N,M,fs;
	//int res2;
	printf("pls input first sidelobe attenuation:\n");
	scanf("%f",&alfa);
	printf("pls input sampling frequency fs:\n");
	scanf("%f",&fs);
	printf("pls input fs1:\n");
	scanf("%f",&fs1);
	fs1=fs1/fs;
	printf("pls input fp1:\n");
	scanf("%f",&fp1);
	fp1=fp1/fs;
	printf("pls input fp2:\n");
	scanf("%f",&fp2);
	fp2=fp2/fs;
	printf("pls input fs2:\n");
	scanf("%f",&fs2);
	fs2=fs2/fs;
	
	if ((fp1 - fs1) > (fs2 - fp2))
		delta = fs2- fp2;
	else 
		delta = fp1-fs1;
	M = (alfa-7.95)/(14.36*delta)+1;
	N = ceil(M); 
	printf("\n");
	printf("Output parameters:\n");
	printf("The filter's order is:\n");
	printf("%f\n",N-1);
	printf("The window length is:\n");
	printf("%f\n",N);
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
	beta = (float*)malloc(sizeof(float)*N);
		memset(beta, 0, sizeof(float)*N);
	beta1 = (float*)malloc(sizeof(float)*N);
		memset(beta1, 0, sizeof(float)*N);
	win = (float*)malloc(sizeof(float)*N);
		memset(win, 0, sizeof(float)*N);
	W = (int*)malloc(sizeof(int)*N);
		memset(W, 0, sizeof(int)*N);
    X = (float*)malloc(sizeof(float)*N);
		memset(X, 0, sizeof(float)*N);
    Y = (float*)malloc(sizeof(float)*N);
		memset(Y, 0, sizeof(float)*N);
	Z = (float*)malloc(sizeof(float)*N);
		memset(Z, 0, sizeof(float)*N);
	printf("The impulse response h[n] are:\n");
	for(j = 0; j <N; j++)
		{
			X[j]=X[j]+j;
			//printf("%d\n",X[j]);
			beta[j]=beta[j]+be;
			//printf("%f\n",beta[j]);
			beta1[j]=beta[j]*sqrt(1.0-((2.0*X[j])/(N-1.0)-1.0)*((2.0*X[j])/(N-1.0)-1.0));
			//printf("%f\n",beta1[j]);
			beta1[j] = bessel0(beta1[j]);
			//printf("%f\n",beta1[j]);
			beta[j] = bessel0(beta[j]);
			//printf("%f\n",beta[j]);
			win[j]=beta1[j]/beta[j];
			//printf("%f\n",win[j]);
				//printf("\n");
			Y[j]=Y[j]+j;
				if (fabs(Y[j]-(N-1.0)/2.0) < EPS)
					Y[j] = fs2+fp2-fs1-fp1;
				else
					Y[j] = sin((PI*fs2 + PI*fp2)*(Y[j]-(N-1.0)/2.0))/(PI*(Y[j]-(N-1.0)/2.0))-sin((PI*fs1 + PI*fp1)*(Y[j]-(N-1.0)/2.0))/(PI*(Y[j]-(N-1.0)/2.0));
				//printf("%f\n",Y[j]);
				Z[j] = Y[j]*win[j];
				printf("%f\n",Z[j]);
		}
		printf("\n");
		printf("again?(Type 0 to exit)");
		scanf("%d",&a);
		getchar();
	}
	return 0;
}

