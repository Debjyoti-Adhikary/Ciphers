#include<stdio.h>
#include<string.h>

FILE *plaintext,*ciphertext,*decipheredtext;
char plainString[20],cipherString[20],receivedCipherString[20],decipheredString[20];
char keyString[20];
void openAllFiles()
{
	plaintext=fopen("Plaintext.txt","r");
	
	decipheredtext=fopen("Decipheredtext.txt","w");	
}

char addChar(char ch,char key)
{	char result;
    int k=key-65;
	int temp=(((ch-97)+k)%26)+65;
	result=temp;
	return result;
}

void encrypt()
{	int i,j=0;
	int keyLength = strlen(keyString);
	printf("PLAINTEXT IS - %s \n",plainString);
	for(i=0;i<strlen(plainString)-1;i++)
	{	
  			cipherString[i]=addChar(plainString[i],keyString[j%keyLength]);
  			j++;
	}
	printf("CIPHERTEXT IS - %s \n",cipherString);
}

void doEncrypt()
{   int i=0;
	ciphertext=fopen("Ciphertext.txt","w");
	printf("enter key:- ");
	scanf("%s",&keyString);
	while(!feof(plaintext))
	{
		plainString[i++]=fgetc(plaintext);
	}
	encrypt();
	fputs(cipherString,ciphertext);
	fclose(ciphertext);	
}

//---------------------------------------------------------------------------------------------

int inverse(int key)
{   int i=0;
	for(i=0;i<26;i++)
	{
		if((i+key)%26==0)
		 return i;
	}
}

char subChar(char ch,char key)
{
	char result;
	int j = key-65;
	int k = inverse(j);
	int temp=(((ch-65)+k)%26)+97;
	result=temp;
	return result;
}

void decrypt()
{
	int i,j=0;
	int keyLength=strlen(keyString);
	printf("RECEIVED CIPHERTEXT IS - %s \n",receivedCipherString);
	for(i=0;i<strlen(receivedCipherString)-1;i++)
	{	
		decipheredString[i] = subChar(receivedCipherString[i],keyString[j%keyLength]);
		j++;	
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
	scanf("%s",&keyString);
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
