#include<stdio.h>
#include<string.h>
FILE *plaintext,*ciphertext,*decipheredtext;
char key[5][5]={'L','G','B','D','A','Q','M','H','E','C','U','R','N','I','F','X','V','S','O','K','Z','Y','W','T','F'};
char plainString[20],cipherString[20],receivedCipherString[20],decipheredString[20];

void openAllFiles()
{
	plaintext=fopen("Plaintext.txt","r");
	
	decipheredtext=fopen("Decipheredtext.txt","w");	
}

void encrypt()
{	int i,j,k,frow,fcol,srow,scol;
	printf("encrypting now");
	for(k=0;k<5;k++)
			{		int x = k+1;
					plainString[k]=toupper(plainString[k]);
					for(i=0;i<5;i++)
					{
						for(j=0;j<5;j++)
						{	
							if(key[i][j]==plainString[x])
							{	printf("second if %c--%c \n",key[i][j],plainString[k]);
								srow=i;
								scol=j;
							}
							//printf("%c",key[i][j]);
							if(key[i][j]==plainString[k])
							{	printf("first if %c--%c\n",key[i][j],plainString[k]);
								frow=i;
								fcol=j;
							}	
						}
					}
					printf("\n %d ------ %d ------ %d ------ %d\n",frow,fcol,srow,scol);
					if(frow==srow)
					{
						cipherString[k]=key[frow][(fcol+1)%5];
						cipherString[k+1]=key[frow][(scol+1)%5];
					}	
					else if(fcol==scol)
					{
						cipherString[k]=key[(frow+1)%5][fcol];
						cipherString[k+1]=key[(srow+1)%5][scol];
					}
			}
		puts(cipherString);				
}

void doEncrypt()
{
	int i=0;
	ciphertext=fopen("Ciphertext.txt","w");
	char readchar;
	while(!feof(plaintext))
	{
		plainString[i++]=fgetc(plaintext);
	}
	encrypt();
	fputs(cipherString,ciphertext);
	fclose(ciphertext);	
}

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
				// doDecrypt();
				 break;
		default: printf("GOODBYE!");		 		 
	}
//	closeAllFiles();
	getch();
}
