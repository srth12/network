#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<stdbool.h>

struct thread{
char uname[7];int fd,u_no;
char * message;
}user[9];

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
printf("!!!!!!!!!!,%s\n",details);
char * pch;int u;
strtok(details,"-:");
pch=strtok(NULL,"-:");
sscanf(pch,"%d",&u);
pch=strtok(NULL,"-:");
user[u].message=pch;
return u;
}

int no_of_users=0;
bool user_check(char uname[5],char passwd[3]){

if(strncmp(uname,"user-1:",5)==0){if(strcmp(passwd,"sar")==0) return true; else return false; }
else if(strncmp(uname,"user-2:",5)==0){if(strcmp(passwd,"sar")) return true; else return false; }
else return false;
}


void* fn(void *newsockfd){
char buffer[255];int n;

while(1){

memset(buffer,0,255);//printf("sssssssss\n");
n=read(newsockfd,buffer,256);
if(n< 0) {printf("Error in reading\n");}
if(strlen(buffer)<=4){continue;}
int uno;
//uno=get_user_details(buffer);
//get_user_details defined here itself due to error
char * pch;int u;n=strlen(buffer);
pch=strtok(buffer,"-:");

pch=strtok(NULL,"-:");
sscanf(pch,"%d",&u);
pch=strtok(NULL,"-:");
user[u].message=pch;
printf("%d,%s,%d,okk\n",user[u].fd,user[u].message,n);
n=write(user[u].fd,user[u].message,strlen(user[u].message));
if(n<0 ) {printf("writing message to client failed\n");return 0;}
//ends here
printf("*%d*,%s\n",u,buffer);
//if(n<0){printf("reading client message failed\n");return 0;}
//printf("succcccccccccccccc\n");

}
printf("server closed for client%d\n",newsockfd);

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
int i=0;pthread_t pd[12];
while(1){
int i;
int cli=sizeof(client);
int clifd;
clifd=accept(serfd,(struct sockaddr *) &client,&cli);
printf(":j:%d:j:\n",clifd);
char uname[50],passwd[50];char str[255];
if(clifd<0){printf("Errror in accept\n");exit(0);}
if((i=write(clifd,"Enter username and password\n",30))<0){printf("requesting uname and pawd failed");return 0;}

if((i=read(clifd,str,50))<0){printf("reading uname and pawd failed");return 0;}
sscanf(str,"%s%s",&uname,&passwd);
printf("user name and paswd rec is:%s,%s\n",uname,passwd);
if(user_check(uname,passwd)){
if((i=write(clifd,"successfully logged in",22))<0){printf("error writing file");exit(0);}
get_user_no(uname,clifd);
pthread_create(&pd[i],NULL,fn,(void*)clifd);
++i;++no_of_users;


}
else{if((i=write(clifd,"Invalid username and password",30))<0){printf("erroring uname and pawd failed");exit(0);}}

}
}
