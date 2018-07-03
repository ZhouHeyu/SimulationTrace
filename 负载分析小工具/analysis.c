#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	char line[200];
	FILE *fp1;
	int devno,blkno,bcount;
	int flags;
	char ch,source[20];
	double time;
	int itemcount=0,readitemcount=0,temp=99999999;
	long int sum=0;
	int max=0,min=9999;

	printf("Please input the name of source file: ");
	scanf("%s",source);

	if((fp1=fopen(source,"r"))==NULL)
    {
        fprintf(stderr, "Couldn't open the source file!\n");
        exit(2);
    }

	while((ch=fgetc(fp1))!=EOF)
	{
		fseek(fp1,-1,1L);

		if(fgets(line,200,fp1)==NULL)
		{
			return (0);
		}

		if (sscanf(line, "%lf %d %d %d %d\n", &time, &devno, &blkno, &bcount, &flags) == 0)
                   {
                   fprintf(stderr, "Wrong number of arguments for I/O trace event type\n");
			fprintf(stderr, "line: %s", line);
			break;
                      }
			
		else
	             {
                   itemcount++;  }

		if(flags==1)
			readitemcount++;

		sum=sum+bcount;

		if(max<=bcount)
		{
			max=bcount;
		}

		if(min>=bcount)
		{
			min=bcount;
		}

		if((min==0)&&(temp >= itemcount))
		{
			printf("The bcount of line %d is 0\n",itemcount);
			temp = itemcount;
		}
		#ifdef DEBUG
			if(itemcount > 328960)
			{
				printf("max is %d, min is %d, sum is %d, bcount is %d\n",max,min,sum,bcount);
			}
		#endif
	}
	printf("The average request size is %f\n",sum*1.0/itemcount);
	printf("The max request size is %d\n",max);
	printf("The min request size is %d\n",min);
	printf("The total number of read requests are: %d\n",readitemcount);
	printf("The total number of requests are: %d\n",itemcount);
	if(fclose(fp1)!=0)
		printf("Error in closing source file!\n");
	return 0;
}
