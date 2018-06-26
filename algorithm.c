#include "stdio.h"
main()
{
	char num,num1,i,buff[25],j,x,count=0,count1=0;
	unsigned long temp,temp1,temp2;
	printf("please input num43605!\n");
	scanf("%d",&temp);
	printf("%d\n",temp);
	for(i=0;i<25;i++)
	{
		temp1 = temp >> i;
		temp2 = temp1 & 0x01;//´òÓ¡×îµÍÎ»
		buff[i] = (char)temp2;
		printf("buff[%02d]=%d\n",i,temp2);
	}
	printf("please input out=?\n");
	scanf("%d",&num);
	for(i=24;i>=0;i--)
	{
		if(buff[i] == 1)
		{
			count++;
			buff[i] = 0;
		}
		if(count == num)
		{
			j = i;
			for(i=0;i<j;i++)
				printf("buff[%d]=%d\n",i,buff[i]);
			printf("over!\r\n");
			goto test;
		}
	}
test:
	printf("please input out=?\n");
	scanf("%d",&num1);
	for(i=j;i>=0;i--)
	{
		if(buff[i] == 1)
		{
			count1++;
			buff[i] = 0;
		}
		if(count1 == num1)
		{
			x = i;
			for(i=0;i<x;i++)
				printf("buff[%d]=%d\n",i,buff[i]);
			printf("over!\r\n");
			return;
		}
	}
}
