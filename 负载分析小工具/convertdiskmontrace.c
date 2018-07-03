#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	char line[200];
	FILE *fp1,*fp2;
	int devno,bcount,newflag,max=0,itemcount=0;
	char ch,flag[10],source[20],dest[20];
	unsigned long long blkno;
	float startTime;
	long int sum=0;

	printf("Please input the name of source file: ");
	scanf("%s",source);
	if((fp1=fopen(source,"r"))==NULL)
    {
        fprintf(stderr, "Couldn't open the source file!\n");
		exit(1);
    }

	printf("Please input the name of destination file: ");
	scanf("%s",dest);
	if((fp2=fopen(dest,"w"))==NULL)
    {
        fprintf(stderr,"Could not open destination file for write!\n");
        exit(1);
    }

	while((ch=fgetc(fp1))!=EOF)
	{
		fseek(fp1,-1,1L);
		if(fgets(line,200,fp1)==NULL)
		{
			return (0);
		}
		if(sscanf(line, "%*d %f %*f %d %s %llu %d\n", &startTime,&devno,&flag,&blkno,&bcount)==0)
		{
			fprintf(stderr, "Wrong number of arguments for I/O trace event type\n");
			fprintf(stderr, "line: %s", line);
			break;
		}
		if((((blkno + bcount -1) / 4 - (blkno)/4 + 1) * 4+((blkno)/4)*4)<2090000)
		{
			itemcount++;
			if(strcmp(flag,"Read")==0)
				newflag=1;
			else if(strcmp(flag,"Write")==0)
				newflag=0;
			else
				printf("Unkown type of operation!\n");
			fprintf(fp2,"%f %d %llu %d %d\n", startTime*1000.0, 0, blkno, bcount, newflag);
			sum=sum+bcount;
			if(max<=bcount)
			{
				max=bcount;
			}
		}
	}
	printf("The average request size is %f\n",sum*1.0/itemcount);
	printf("The max request size is %d\n",max);
	printf("The total number of the items are: %d\n",itemcount);
	if(fclose(fp1)!=0)
		printf("Error in closing source file!\n");
	if(fclose(fp2)!=0)
		printf("Error in closing destination file!\n");
	return 0;
}
