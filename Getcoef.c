///////////////////////////////////////
//Function:Getcoef.c                 //
//Input: normalized main lobe        //
//       normalized desired bandwith //
//output: The coeffienct of h[n]     //
//applying retangular window         //
///////////////////////////////////////
#include<math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define PI 3.1415926535 

int main(void)
{  
	int a=1;
	while(a)
	{
		int i,j;
		float N,BW;
		float b;
		float c,d;
		float *X = 0;
		float EPS = 0.00001;
		int res,res1;
    
		printf("Please type the normalized main lobe (0 to 1) width of the filter\n");
		res = scanf("%f",&BW);
		getchar();
		while(!res)
			{
				printf("Input error\n");
				printf("Please type the normalized main lobe (0 to 1) width of the filter\n");
				res = scanf("%f",&BW);
				getchar();
			}
      
		printf("Please type the normalized band-width (0 to 1) of the filter\n");
		res1 = scanf("%f",&b);
		getchar();
		while(!res1)
			{
				printf("Input error\n");
				printf("Please type the normalized band-width (0 to 1) of the filter\n");
				res1 = scanf("%f",&b);
				getchar();
			}
      
		c=PI*(1.0-b)/2;
		d=PI-c;
		//printf("%f\n",c);
		//printf("%f\n",d);
		N=4/BW-1;
		N=ceil(N);
		i=N;
		i=i+1;	
		printf("The window length should be %d\n",i);
		X = (float*)malloc(sizeof(float)*i);
		memset(X, 0, sizeof(float)*i);
		///////////////////////////////////////  build rectangular window coefficient
		printf("The window coefficient is\n");
		for (j = 0;j < i;j++)
       {
		    X[j]=X[j]+j;
				if (fabs(X[j]-N/2.0) < EPS)
				  	X[j]=(d-c)/PI;
				else
				printf("%f",X[j]);
				printf("\n");
       }
                //////////////////////////////////////
		printf("again?(Type 0 to exit)");
		scanf("%d",&a);
		getchar();
	};                            
	return 0;
}
