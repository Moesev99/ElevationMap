#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	char *name;
	int loc[2];
	double height;
	double slope;
} Hill;


Hill setHill(char name[20], int xloc, int yloc, double height, double slope)
{
	Hill  hill;
	hill.name = name;
	hill.loc[0] = xloc;
	hill.loc[1] = yloc;
	hill.height = height;
	hill.slope = slope;

	return hill;

}


int main(int argc, char const *argv[])
{
	Hill hills[5];
	int rows = 15, cols=19;
	char names[5][20] = {"Ada's Apex", "Turing's Top", "Babbage's Bluff", "Hopper's Hill", "Kathrine's Cliff"};
	int xlocs[5] = {12,4,6,14,1};
	int ylocs[5] = {9,3,13,2,9};
	double heights[5] = {20,20,15,15,10};
	double slopes[5] = {.25,.33,.33,.5,.5};

	double elevation[rows][cols];

	int i,j,k,temp;
	for (i=0;i<5;i++)
	{
		hills[i] = setHill(names[i], xlocs[i], ylocs[i], heights[i], slopes[i]);
	}
 arg
	for (i = 0; i < rows; ++i)
	{
		
		for (j = 0; j < cols; ++j)
		{
			elevation[i][j]=0;
			if (!(i==0 || j==0 || i == (rows-1) || j == (cols-1)))
			{
				for (k=0;k<5;k++)
				{
					elevation[i][j] += heights[k] * exp( -pow(slopes[k], 2) * ( pow((j-xlocs[k]),2) + pow((i-ylocs[k]),2)));
				}
			}
		}
		
	}

	for (i = 0; i < rows; ++i)
	{
		temp = i;
		i = rows-1-i;
		for (j = 0; j < cols; ++j)
		{
			printf("%4.1f ", elevation[i][j]);
		}
		printf("\n");
		i=temp;
	}

	printf("\n");

	int xpos, ypos;

	printf("Enter your x location (1-17): ");
	scanf("%d", &xpos);
	printf("Enter your y location (1-13): ");
	scanf("%d", &ypos);

	double elev =  elevation[ypos][xpos];
	double diffW = elevation[ypos][xpos-1] - elev;
	double diffE = elevation[ypos][xpos+1] - elev;
	double diffN = elevation[ypos+1][xpos] - elev;
	double diffS = elevation[ypos-1][xpos] - elev;
    
	//printf("diffW=%f\n", diffW);
	// printf("diffE=%f\n", diffE);
	// printf("diffN=%f\n", diffN);
	// printf("diffS=%f\n", diffS);
	printf("The elevation for the point (%d,%d) is %4.4f\n", xpos, ypos, elev);
	
	int flag=0;
	
	for (k=0;k<5;k++)
	{	
		if (xpos == xlocs[k] && ypos == ylocs[k])
		{
			printf("You are at the peak of %s\n", names[k]);
			flag = 1;
			break;
		}
	}
	if (flag==0)
	{
		printf("You are not at the peak of a hill.\n");
	}

	double minDiff = 99999999, ans;
	char *direction;
	if (abs(diffN)<=minDiff)
	{
		direction = "North";
		minDiff = abs(diffN);
		ans = diffN;
	}	
	if (abs(diffE)<=minDiff)
	{
		direction = "East";
		minDiff = abs(diffE);
		ans = diffE;
	}	
	if (abs(diffS)<=minDiff)
	{
		direction = "South";
		minDiff = abs(diffS);
		ans = diffS;
	}	
	if (abs(diffW)<=minDiff)
	{
		direction = "West";
		minDiff = abs(diffW);
		ans = diffW;
	}	

	printf("Walk %s for a moderate hike. The elevation change is %4.4f\n", direction, ans);
	return 0;
}