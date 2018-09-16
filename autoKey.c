#include<stdio.h>
#include<string.h>
FILE *plaintext,*ciphertext,*decipheredtext;
char plainString[20],cipherString[20],receivedCipherString[20],decipheredString[20];
int key;
void openAllFiles()
{
	plaintext=fopen("Plaintext.txt","r");	
	decipheredtext=fopen("Decipheredtext.txt","w");	
}

char addChar(char ch,int k)
{	char result;
	int temp=(((ch-97)+k)%26)+65;
	result=temp;
	return result;
}

void encrypt()
{	int i;
	printf("PLAINTEXT IS - %s \n",plainString);
	cipherString[0]=addChar(plainString[0],key);
	for(i=1;i<strlen(plainString)-1;i++)
	{	int temp=plainString[i-1]-97;
	    cipherString[i]=addChar(plainString[i],temp);
	}
	printf("CIPHERTEXT IS - %s \n",cipherString);
}

void doEncrypt()
{   int i=0;
	ciphertext=fopen("Ciphertext.txt","w");
	char readchar;
	printf("enter key:- ");
	scanf("%d",&key);
	while(!feof(plaintext))
	{
		plainString[i++]=fgetc(plaintext);
	}
	encrypt();
	fputs(cipherString,ciphertext);
	fclose(ciphertext);	
}

//---------------------------------------------------------------------------------------------
char subChar(char ch,int k)
{
	char result;
	int temp=(((ch-65)+k)%26)+97;
	result=temp;
	return result;
}

int inverse(int x)
{	int i;
	for(i=0;i<26;i++)
	{
		if((i+x)%26==0)
		{
			return i;
		}
	}
}

void decrypt()
{
	int i;
	printf("RECEIVED CIPHERTEXT IS - %s \n",receivedCipherString);
	decipheredString[0]=subChar(receivedCipherString[0],inverse(key));
	for(i=1;i<strlen(receivedCipherString)-1;i++)
	{	
		int temp=decipheredString[i-1]-97;
	    decipheredString[i]=subChar(receivedCipherString[i],inverse(temp));
	}
	printf("DECIPHERED TEXT IS - %s \n",decipheredString);
	fputs(decipheredString,decipheredtext);
}

void doDecrypt()
{
	int i=0;
	ciphertext=fopen("Ciphertext.txt","r");
	char readchar;
	printf("enter key:- ");
	scanf("%d",&key);
	while(!feof(ciphertext))
	{
		receivedCipherString[i++]=fgetc(ciphertext);
	}
	decrypt();
	fclose(plaintext);
	fclose(ciphertext);
	fclose(decipheredtext);
}
//---------------------------------------------------------------------------------------------
int main()
{
	int choice;
	openAllFiles();
	printf("ENTER 1. TO ENCRYPT\n, 2 TO DECRYPT\n, 3 TO EXIT\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1 : printf("ENTERING ENCRYPTION MODE\n");
				 doEncrypt();
				 break;
		case 2 : printf("ENTERING DECRYPTION MODE\n");
				 doDecrypt();
				 break;
		default: printf("GOODBYE!");		 		 
	}
//	closeAllFiles();
	getch();
}
