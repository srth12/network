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
/*
while(1){

bzero(buffer,256);
int n=0;
long arg1,arg2;
n = read(newsockfd,buffer,255);
     if (n < 0){ printf("ERROR reading from socket");exit(0);}
if(strlen(buffer) ==0) continue;

if(strncmp(buffer,"eof",3) ==0) break;
    // printf("Here is the:%d: message: %s\n",(int)newsockfd,buffer);
     sscanf(buffer,"%ld%ld",&arg1,&arg2);
     //printf("%ld,%ld",arg1,arg2);
	char buf[255];
     bzero((char *)&buf,sizeof(buf));
     snprintf(buf,sizeof(buf),"%ld\n",arg1+arg2);
   n = write(newsockfd,buf,strlen(buf));
     if (n < 0) error("ERROR writing to socket");

}
*/
while(1){
bzero(buffer,255);printf("sssssssss\n");
fgets(buffer,256,newsockfd);
printf("%s",buffer);
if(n<0){printf("reading client message failed\n");return 0;}
printf("succcccccccccccccc\n");
/*
int uno=get_user_details(buffer);
n=write(user[uno].fd,user[uno].message,50);
if(n<0){printf("writing message to client failed\n");return 0;} */
}
close(newsockfd);
}

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
