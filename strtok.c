#include<stdio.h>
#include<string.h>
int main(){
printf("Enter string\n");
char str[222];
scanf("%s",str);
printf("Entered sting:%s\n",str);
char * pch;
pch = strtok (str," ,.-");
  
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
 
 printf ("%s\n",pch);
 
 char a[44]="hello ";
 strcat(a,"world\n");
 printf("%s",a);
}
