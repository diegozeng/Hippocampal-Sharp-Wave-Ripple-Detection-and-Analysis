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
		/*printf("Please type the normalized band-width (0 to 1) of the filter\n");
		res1 = scanf("%f",&b);
		getchar();
		while(!res1)
			{
				printf("Input error\n");
				printf("Please type the normalized band-width (0 to 1) of the filter\n");
				res1 = scanf("%f",&b);
				getchar();
			}*/
		//printf("%f",b);
		//c = PI*(1.0 - b) / 2;
		//d = PI-c;
		//printf("%f\n",c);
		//printf("%f\n",d);
		N = 4 / BW - 1;
		N = ceil(N);
		i = N;
		i = i + 1;	
		printf("The window length should be %d\n",i);
		W = (int*)malloc(sizeof(int)*i);
		memset(W, 0, sizeof(int)*i);
		X = (float*)malloc(sizeof(float)*i);
		memset(X, 0, sizeof(float)*i);
		/////////////////////////////////////// build rectangular window coefficient
		printf("The window coefficient is\n");
		for (j = 0;j < i;j++)
              {
				//W[j]=W[j]+1;
				//printf("%d",k);
				X[j] = X[j]+j;
				//printf("\n");
				if (fabs(X[j]-N/2.0) < EPS)
					X[j] = 2*(fc2-fc1);
				else
					X[j] = sin(PI*2*fc2*(X[j]-N/2.0))/(PI*(X[j]-N/2.0))-sin(PI*2*fc1*(X[j]-N/2.0))/(PI*(X[j]-N/2.0));
				//X[j]= X[j]*pow(2,32);
				//W[j]= (int)(X[j]+0.5);
				//printf("%d",W[j]); 
				//printf("\n");
				printf("%f",X[j]);
				printf("\n");
              }
		///////////////////////////////////////
		printf("The length is %d\n",i);
		printf("again?(Type 0 to exit)");
		scanf("%d",&a);
		getchar();
	};    
	fclose(fp);
	return 0;
}
