#include<stdio.h>
#include<string.h>
#include<ctype.h>
FILE *plaintext,*ciphertext,*decipheredtext;
int key[3][3]={{17,7,5},{21,8,21},{2,2,19}},inverseKey[3][3];
int plainMatrix[3][3],cipherMatrix[3][3],receivedCipherMatrix[3][3],decipheredMatrix[3][3];
char plainString[20],cipherString[20],receivedCipherString[20],decipheredString[20];

void openAllFiles()
{
	plaintext=fopen("Plaintext.txt","r");
	
	decipheredtext=fopen("Decipheredtext.txt","w");	
}

void makeCipherString()
{
    int i=0,j,k;
        for(j=0;j<3;j++)
        {
            for(k=0;k<3;k++)
            {
                cipherString[i++]=cipherMatrix[j][k]+65;
            }
            printf("\n");
        }
    printf("%s",cipherString);    
}
void encrypt()
{	int sum,i,j,k;	
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {   sum=0;
            for(k=0;k<3;k++)
            {
                sum = sum + plainMatrix[i][k]*key[k][j];    
            }
            cipherMatrix[i][j]=sum%26;
            
        }
    }
    printf("MULTIPLY SUCCESSFUL \n");
    for(j=0;j<3;j++)
        {   
            for(k=0;k<3;k++)
            {
                printf("%d \t",cipherMatrix[j][k]);
            }
            printf("\n");
        }
}

void appendBogusCharacter()
{
    int i,plaintextLength=strlen(plainString);
    printf("length of plaintext is %d \n",plaintextLength);
    if(plaintextLength<=9)
    {
        for(i=plaintextLength-1;i<9;i++)
            plainString[i]='z';
    }
    printf("%s \n",plainString);

}

void makePlainMatrix()
{   int i=0,j,k;
        for(j=0;j<3;j++)
        {
            for(k=0;k<3;k++)
            {
                plainMatrix[j][k]=((plainString[i++]-97)%26);
            }
            printf("\n");
        }
    printf("PLAIN MATRIX BUILD SUCCESSFULL....DISPLAYING MATRIX NOW\n");
    for(j=0;j<3;j++)
        {
            for(k=0;k<3;k++)
            {
                printf("%d \t",plainMatrix[j][k]);
            }
            printf("\n");
        }

}

void doEncrypt()
{
	int j,i=0;
	ciphertext=fopen("Ciphertext.txt","w");
	char readchar;
	while(!feof(plaintext))
	{
		plainString[i++]=fgetc(plaintext);
	}
    appendBogusCharacter();
    makePlainMatrix();
    encrypt();
    makeCipherString();
	fputs(cipherString,ciphertext);
	fclose(ciphertext);	
}
//-------------------------------------------------------------------------------------------------
int multiplicativeInverse(int number)
{
	int i=0;
	for(;i<26;i++)
	 {
	 	if((i*number)%26==1)
	 		return i;
	 }
}

void makeReceivedCipherMatrix()
{   int i,j,k;
    for(j=0;j<3;j++)
    {
        for(k=0;k<3;k++)
        {
            receivedCipherMatrix[j][k]=receivedCipherString[i++]-65;
		}
    }

}

void CalculateInverseKey()
{
	int determinant = key[0][0]*(key[1][1]*key[2][2]-key[2][1]*key[1][2]) - key[0][1]*(key[1][0]*key[2][2]-key[2][0]*key[1][2]) + key[0][2]*(key[1][0]*key[2][1]-key[1][1]*key[2][0]);
	determinant%=26;
	if(determinant<0)
		determinant+=26;
	int MIdeterminant=multiplicativeInverse(determinant);
	inverseKey[0][0]=((key[1][1]*key[2][2] - key[2][1]*key[1][2])*MIdeterminant)%26;
	inverseKey[0][1]=((key[0][2]*key[2][1] - key[0][1]*key[2][2])*MIdeterminant)%26;
	inverseKey[0][2]=((key[0][1]*key[1][2] - key[1][1]*key[0][2])*MIdeterminant)%26;
	inverseKey[1][0]=((key[1][2]*key[2][0] - key[1][0]*key[2][2])*MIdeterminant)%26;
	inverseKey[1][1]=((key[0][0]*key[2][2] - key[2][0]*key[0][2])*MIdeterminant)%26;
	inverseKey[1][2]=((key[0][2]*key[1][0] - key[0][0]*key[1][2])*MIdeterminant)%26;
	inverseKey[2][0]=((key[1][1]*key[2][0] - key[1][0]*key[2][1])*MIdeterminant)%26;
	inverseKey[2][1]=((key[0][1]*key[2][0] - key[0][0]*key[2][1])*MIdeterminant)%26;
	inverseKey[2][2]=((key[0][0]*key[1][1] - key[1][0]*key[0][1])*MIdeterminant)%26;			
	int j,k;
	printf("\n INVERSE KEY MATRIX \n");
	for(j=0;j<3;j++)
    {
        for(k=0;k<3;k++)
        {
        	if(inverseKey[j][k]<0)
        		inverseKey[j][k]+=26;
            printf("%d \t",inverseKey[j][k]);
        }
        printf("\n");
    }
	
}

void multiplyWithCipheredText()
{	int i,j,k,sum;



	for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {   sum=0;
            for(k=0;k<3;k++)
            {
                sum = sum + receivedCipherMatrix[i][k]*inverseKey[k][j];    
            }
            decipheredMatrix[i][j]=sum%26;          
        }
    }
    
     for(j=0;j<3;j++)
        {   
            for(k=0;k<3;k++)
            {	 if(decipheredMatrix[j][k]<0)
            		decipheredMatrix[j][k]+=26;
                 printf("%d \t",decipheredMatrix[j][k]);
            }
        	printf("\n");                
        }
}
void makeDecipheredString()
{
	int i=0,j,k;
        for(j=0;j<3;j++)
        {
            for(k=0;k<3;k++)
            {
                decipheredString[i++]=decipheredMatrix[j][k]+97;
            }
            printf("\n");
        }
    printf("%s",decipheredString);  
}
void decrypt()
{	makeReceivedCipherMatrix();
	CalculateInverseKey();
	multiplyWithCipheredText();
	makeDecipheredString();	
}

void doDecrypt()
{
	int i=0;
	ciphertext=fopen("Ciphertext.txt","r");
	char readchar;
	while(!feof(ciphertext))
	{
		receivedCipherString[i++]=fgetc(ciphertext);
	}
	printf("RECEIVED CIPHER STRING --- %s\n",receivedCipherString);
	decrypt();
	fclose(plaintext);
	fclose(ciphertext);
	fclose(decipheredtext);
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
				 doDecrypt();
				 break;
		default: printf("GOODBYE!");		 		 
	}
}
