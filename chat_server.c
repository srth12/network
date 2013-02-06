#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

char logged_in_usrlist[100];char ttt[100];
struct thread{
char uname[7];int fd,u_no;
char * message;
}user[9];
int my_no[100];
int get_user_no(char * uname,int clifd){
// getting details of the user
char * pch;int u;
char ls[5];
strcpy(ls,uname);
strtok(uname,"-:");
pch=strtok(NULL,"-:");
sscanf(pch,"%d",&u);
pch=strtok(NULL,"-:");
user[u].u_no=u;user[u].fd=clifd;
printf("-::%d::-\n",u);
//updated till here
return u;

}

//stores the message and return the user no to send the message
int get_user_details(char * details){
//printf("!!!!!!!!!!,%s\n",details);
char * pch;int u;
strtok(details,"-:");
pch=strtok(NULL,"-:");
sscanf(pch,"%d",&u);
pch=strtok(NULL,"-:");
user[u].message=pch;
return u;
}

int no_of_users=0;
bool user_check(char uname[7],char passwd[3]){
/*
if(strncmp(uname,"user-2:",7)==0){if(strncmp(passwd,"sar",3)==0) { return true;} else return false; }
else if(strncmp(uname,"user-1:",7)==0){if(strncmp(passwd,"sar",3)==0){ return true;} else{ return false;} }
else if(strncmp(uname,"user-3:",7)==0){if(strncmp(passwd,"sar",3)==0) return true; else return false; }
else return false;
*/
FILE *fp;
fp=fopen("users.txt","r");
if(fp==NULL){printf("File open failed\n");exit(0);}
char i[50],j[50],line[50];

while(fgets(line,50,fp) !=NULL){
//printf("[:%s:]\n",line);
sscanf(line,"%s%s",i,j);
if(strncmp(uname,i,7)==0){if(strncmp(passwd,j,3)==0) { return true;}  }

}
return false;
}


bool signup(char uname[50],char passwd[55]){
	
	char i[50],j[50],line[50];FILE *fp;
	fp=fopen("users.txt","w");
	putc('c',fp);
	
		
}

/*
bool signup(char uname[50],char passwd[3],char str[255]){
	
	char i[50],j[50],line[50];
	FILE *fp;
		fp=fopen("users.txt","w+");
		 int kk=fputs("hhhhh\n",fp);
		 printf("(%d)\n",kk);
		if(fp==NULL){printf("File open failed\n");return false;}
	while(fgets(line,50,fp) !=NULL){
	printf("[:%s:]\n",line);
	sscanf(line,"%s%s",i,j);
	if(strncmp(uname,i,7)==0){return false;  }
		}
		//fclose(fp);
		//fseek(fp,0,SEEK_SET);
		
		
		//fw=fopen("users.txt","a");
		//if(fw==NULL){printf("File open failed\n");return false;}
		//snprintf(line,strlen(line),"%s%s",uname,passwd);
		//fseek(fp,0,SEEK_END);
		
		printf("[string going to write to file issss:%s:]\n",uname);
		//if(putc('a',fp)>0){ 
		
		if(fputs(uname,fp)<0){printf("Error in writing to file\n");return false;
		//if(fprintf(fp,"%s",uname)==EOF){printf("Error in writing to file\n");return false;
		}
		else{ return true; fputs(uname,fp);
		
		fclose(fp);}
		
		 fputs(uname,fp);
		
		fclose(fp);
		
}

*/

void* fn(void *qw){
char buffer[255];int n;int newsockfd=(int)qw;  
//printf("%d\n",(int*)newsockfd);
while(1){

memset(buffer,0,255);//
n=read(newsockfd,buffer,256);
if(n< 0) {printf("Error in reading\n");break;}
if(strlen(buffer)<=4){continue;}
int uno;//printf("hihi-%s\n",buffer);
//uno=get_user_details(buffer);
//get_user_details defined here itself due to error
char * pch;int u;n=strlen(buffer);
pch=strtok(buffer,"-:");

pch=strtok(NULL,"-:");
sscanf(pch,"%d",&u);
pch=strtok(NULL,"-:");
//adding from usr to message
char temp[100];
int y=3;printf("(%d)",newsockfd);
snprintf(temp,sizeof(temp),"From user-%d\n",my_no[newsockfd]);
//strcat(temp,my_no[*(int*)newsockfd]);
strcat(temp,pch);
//snprintf(temp,sizeof(temp),"%s%s","From user-",my_no[*(int*)newsockfd]);
printf("[%s]\n",temp);
user[u].message=temp;

//
//user[u].message=pch;
//printf("%d,%s,%d,okk\n",user[u].fd,user[u].message,n);
n=write(user[u].fd,user[u].message,strlen(user[u].message));
if(n<0 ) {printf("writing message to client failed\n");return 0;}
memset(buffer,0,255);
//ends here


}
printf("server closed for client%d\n",(int)newsockfd);

close(newsockfd);
}

//main program
int main(){
printf("hello2\n");
int portno,serfd;
struct sockaddr_in seraddr,client;
portno=atoi("55555");

if((serfd=socket(AF_INET,SOCK_STREAM,0))<0){
printf("socket failed\n");
return 0;
}

bzero((char *) &seraddr, sizeof(seraddr));
seraddr.sin_addr.s_addr = INADDR_ANY;// assigning server address;
seraddr.sin_family = AF_INET;
seraddr.sin_port = htons(portno);
if(bind(serfd,(struct sockaddr *) &seraddr,sizeof(seraddr))<0){
printf("binding failed\n");
return 0;}

int n=listen(serfd,2);
if(n<0){printf("error in listen\n");}
int i=0;pthread_t pd[12];int q;
u:
while(1){
int i;
int cli=sizeof(client);
int clifd;
clifd=accept(serfd,(struct sockaddr *) &client,&cli);
if(clifd<=0){printf("Errror in accept\n");exit(0);}
//printf(":j:%d:j:\n",clifd);
char uname[50],passwd[50];char str[255],mode_str[255];
//signup


if((i=write(clifd,"1. for signup, 2. for login..\n",255))<0){printf("requesting user mode failded");return 0;}printf("mo0000\n");
if((i=read(clifd,mode_str,sizeof(mode_str)))<=0){printf("reading user mode failded\n");return 0;}
int mode=atoi(mode_str);
printf("mode:%d\n",mode);

if((i=read(clifd,str,sizeof(str)))<=0){printf("reading uname and pawd failed");return 0;}
printf("u and p is:%s,%d\n",str,strlen(str));
sscanf(str,"%s%s",uname,passwd);

switch(mode){
case 1: 
if(signup(uname,passwd)){printf("successfully signed up\n");
int p=get_user_no(uname,clifd);printf("p=%d\n",p);
snprintf(uname,sizeof(uname),"user-%d\n",p);
strcat(logged_in_usrlist,uname);
my_no[clifd]=p;// adding current users id to global var

strcpy(ttt,"successfully Signed up :\n Logged in users :\n");
strcat(ttt,logged_in_usrlist);
if((i=write(clifd,ttt,100))<0){printf("error writing file");exit(0);}

pthread_create(&pd[i],NULL,fn,(void*)clifd);
++i;++no_of_users;
goto u;
}
else{printf("failed to signup\n");goto u;}
default:break;
}

//signup ends here


if(user_check(uname,passwd)){
	int p=get_user_no(uname,clifd);printf("p=%d\n",p);
snprintf(uname,sizeof(uname),"user-%d\n",p);
strcat(logged_in_usrlist,uname);
my_no[clifd]=p;// adding current users id to global var

strcpy(ttt,"successfully logged in :\n Logged in users :\n");
strcat(ttt,logged_in_usrlist);
if((i=write(clifd,ttt,100))<0){printf("error writing file");exit(0);}


pthread_create(&pd[i],NULL,fn,(void*)clifd);
++i;++no_of_users;


}
else{if((i=write(clifd,"Invalid username and password",30))<0){printf("erroring uname and pawd failed");exit(0);} close(clifd);}

}
}
