#include<math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define PI 3.1415926535 

int main(void)
{  
	int a=1;
	FILE * fp = fopen("data.txt", "w");
	if(fp == NULL)
	{	
		printf("open file wrong!\n");
	}
	while(a)
	{
		int i,j;
		float N,BW;
		float fs;
		float fc1,fc2;
		int *W = 0;
		float *X = 0;
		float *Y = 0;
		float *Z = 0;
		float EPS = 0.00001;
		int res;
	printf("pls input sampling frequency fs:\n");
		scanf("%f",&fs);
		printf("Pls input the main lobe width of the filter\n");
		//scanf("%f",&BW);
		res = scanf("%f",&BW);
		getchar();
		while(!res)
			{
				printf("Input error\n");
				printf("Please type the normalized main lobe (0 to 1) width of the filter\n");
				res = scanf("%f",&BW);
				getchar();
			}
		BW=2*BW/fs;
		printf("pls input fc1:\n");
		scanf("%f",&fc1);
		fc1=fc1/fs;
		printf("pls input fc2:\n");
		scanf("%f",&fc2);
		fc2=fc2/fs;
		N = 8 / BW;
		N = ceil(N);
		i = N;
		i = i + 1;	
		printf("The window length should be %d\n",i);
		W = (int*)malloc(sizeof(int)*i);
		memset(W, 0, sizeof(int)*i);
		X = (float*)malloc(sizeof(float)*i);
		memset(X, 0, sizeof(float)*i);
		Y = (float*)malloc(sizeof(float)*i);
		memset(Y, 0, sizeof(float)*i);
		Z = (float*)malloc(sizeof(float)*i);
		memset(Z, 0, sizeof(float)*i);
		///////////////////////////////////////////
		//printf("The w[n] coefficient is\n");
		/*for (j = 0;j < i;j++)
			{
				Y[j] = Y[j]+j;
				Y[j] = 0.5 - 0.5*cos(2*PI*Y[j]/(N));
				printf("%f",Y[j]);
				printf("\n");
			}*/
		//printf("The h_d[n] coefficient is\n");
		for (j = 0;j < i;j++)
              {
				Y[j] = Y[j]+j;
				Y[j] = 0.5 - 0.5*cos(2*PI*Y[j]/(N));
				X[j] = X[j]+j;
				//printf("\n");
				if (fabs(X[j]-N/2.0) < EPS)
					X[j] = 2*(fc2-fc1);
				else
					X[j] = sin(PI*2*fc2*(X[j]-N/2.0))/(PI*(X[j]-N/2.0))-sin(PI*2*fc1*(X[j]-N/2.0))/(PI*(X[j]-N/2.0));
				Z[j] = X[j]*Y[j];
				Z[j]= Z[j]*pow(2,32);
				W[j]= (int)(Z[j]+0.5);
				printf("%d",W[j]); 
				printf("\n");
				//printf("%f",Z[j]);
				//printf("\n");
		      }
		
		printf("The length is %d\n",i);
		printf("again?(Type 0 to exit)");
		scanf("%d",&a);
		getchar();
	};     
	fclose(fp);
	return 0;
}
