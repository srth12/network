#include<stdio.h>



int main(){
	FILE *fp;char buf[55];
	fp=fopen("users.txt","r");if(fp==NULL){printf("File open failed\n");return 0;}
	while(fgets(buf,sizeof(buf),fp)!=NULL)
	printf("%s",buf);
	fclose(fp);
	FILE *pd;
	char l[55]="user-5: sar";
	
	pd=fopen("users.txt","a");
	fputs(l,pd);
	//fputs("user-2: sar",pd);
	


}
