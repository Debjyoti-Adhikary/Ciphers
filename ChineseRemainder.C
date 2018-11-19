//chinese remainder theorem
#include<conio.h>
#include<stdio.h>
int inverse(int number, int base)
{
	int i=1;
	for(i;i<base;i++)
	{
		if(((i*number)%base)==1)
		 return i;
	}
}
main()
{	int k,i,Mprod=1,x,temp=0;
	printf("enter number of equations - \n");
	scanf("%d",&k);
	int a[k],m[k],M[k],MIn[k];
	for(i=0;i<k;i++)
	{
		printf("\n enter a%d -",i+1);
		scanf("%d",&a[i]);
		printf("\n enter M%d -",i+1);
		scanf("%d",&m[i]);
		Mprod=Mprod*m[i];
	}
	for(i=0;i<k;i++)
	{
		M[i]=Mprod/m[i];
		MIn[i]=inverse(M[i]%m[i],m[i]);
		temp+=a[i]*M[i]*MIn[i];
	}
	printf("\nENTERED EQUATIONS ARE AS FOLLOWS -");
	for(i=0;i<k;i++)
	{
		printf("\n x= %d ( mod %d ) | M = %d | Minverse = %d",a[i],m[i],M[i],MIn[i]);
	}
	printf("\n M= %d ",Mprod);
	x=temp%Mprod;
	printf("\n x = %d",x);
}
