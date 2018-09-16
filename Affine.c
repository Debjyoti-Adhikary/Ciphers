//Affine cipher
#include<stdio.h>
int key1,key2,ikey1,ikey2;
FILE *plaintext,*ciphertext,*decipheredtext;
void openAllFiles()
{
	plaintext=fopen("Plaintext.txt","r");
	
	decipheredtext=fopen("Decipheredtext.txt","w");	
}

char encrypt(char pt)
{	int tres;
	int temp=pt-97;
	if(isalpha(pt))
	{
		tres=((temp*key1+key2)%26)+65;
	}
	char result = tres;
	return(result);
}

char decrypt(char pt)
{   int tempres;
	int temp=pt-65;
	//ikey1=5;
	ikey1=MultiplicativeInverse(key1);
	ikey2=AdditiveInverse(key2);
	//ikey2=24;
	printf("decrytping");
	if(isalpha(pt))
	{
		tempres=((temp+ikey2)*ikey1)%26;
	}
	char result = tempres+97;
	return(result);
}

int MultiplicativeInverse(int number)
{   int i;
	for(i=1;i<26;i++)
	{
		if((i*number)%26==1)
		{
			break;
		}
	}
	return(i);
}

int AdditiveInverse(int number)
{   int i;
	for(i=1;i<26;i++)
	{
		if((i+number)%26==0)
		{
			break;
		}
	}
	return(i);
}

void doEncrypt()
{	ciphertext=fopen("Ciphertext.txt","w");
	char readchar,writechar;
	printf("enter k1:- ");
	scanf("%d",&key1);
	printf("\nenter k2:- ");
	scanf("%d",&key2);
	while(!feof(plaintext))
	{
		readchar=fgetc(plaintext);
		writechar=encrypt(readchar);
		if(isalpha(writechar))
		{
			fputc(writechar,ciphertext);
		}
		
	}
	fclose(ciphertext);	
}

void doDecrypt()
{   ciphertext=fopen("Ciphertext.txt","r");
	char readCypherText,writechar;
	printf("enter k1:- ");
	scanf("%d",&key1);
	printf("\nenter k2:- ");
	scanf("%d",&key2);
	printf("DECRYPTING\n");
	while(!feof(ciphertext))
	{
		readCypherText=fgetc(ciphertext);
		if(isalpha(readCypherText))
		{
			writechar=decrypt(readCypherText);
			if(isalpha(writechar))
			{
				fputc(writechar,decipheredtext);
			}
		}
	}	
}

void closeAllFiles()
{
	fclose(plaintext);
	fclose(ciphertext);
	fclose(decipheredtext);
}

main()
{	int choice;
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
	closeAllFiles();
	getch();
}

