#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>

void* reader(void* qw){int sockfd=(int) qw;
int n;char buf[1024];printf("(%d)",sockfd);
while(1){
	bzero(&buf,sizeof(buf));
//printf("enter message to send\n");
fgets(buf,1024,stdin);if(strlen(buf)==0) continue;
if((n=write(sockfd,buf,sizeof(buf)))<0){
printf("failed write teh message %d\n",n);exit(0);}
bzero(&buf,sizeof(buf));
}}

void* writer(void* sockfd){
char buf[1024];
bzero(&buf,sizeof(&buf));
int n,i;//printf(":%d:\n",sockfd);
while(1){
bzero(&buf,sizeof(&buf));
if((i=read(sockfd,buf,sizeof(buf)))<0){printf("reading message failed\n");exit(0);}
printf("%s\n",buf);bzero(&buf,sizeof(&buf));
}

}


int main(){
char buf[1024],lol[1024],buffer[1024];

int i; 
int sockfd,portno,n;struct sockaddr_in host;
l:
portno=atoi("55555");
if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
printf("socket failed\n");}


bzero(&host,sizeof(host));
host.sin_family=AF_INET;
host.sin_port=htons(portno);
inet_pton(AF_INET,"127.0.0.1",&host.sin_addr);// assigning server address;

if(connect(sockfd,(struct sockaddr*)&host,sizeof(host))<0){
printf("connection failed\n");
exit(0);
}
//signup
//bzero(&buf,sizeof(&buf));
if((i=read(sockfd,buf,1024))<0){printf("reading signup mode failed\n");exit(0);}
printf("%s",buf);
//bzero(&buf,sizeof(&buf));
read(stdin,buf,strlen(buf));// getting signup mode from terminal
printf("%s\n",buf);
if((n=write(sockfd,buf,sizeof(buf)))<0){
printf("failed write in signup %d\n",n);exit(0);}
printf("Wrote signup to server\n");

//signup ends


//bzero(&buf,sizeof(&buf));
if((i=read(sockfd,lol,sizeof(lol)))<0){printf("reading uname request failed\n");exit(0);}
printf("%s,./.,aaa",buf);bzero(&buf,sizeof(&buf));//printf("hh%s\n",buf);
fgets(buffer,1024,stdin);// getting username and password from terminal

if((n=write(sockfd,buffer,sizeof(buf)))<0){
printf("failed write.. %d\n",n);exit(0);}
//bzero(&buf,sizeof(buf));
read(sockfd,buf,1024);
printf("output from server: %s\n",buf);if(strncmp(buf,"Invalid username and password",29)==0){goto l;}
/*
while(1){
bzero(&buf,sizeof(buf));
printf("enter message to send\n");
fgets(buf,255,stdin);
if((n=write(sockfd,buf,sizeof(buf)))<0){
printf("failed write teh message %d\n",n);exit(0);}
bzero(&buf,sizeof(&buf));
//while(1){
if((i=read(sockfd,buf,sizeof(buf)))<0){printf("reading message failed\n");exit(0);}
printf("%s\n",buf);
//}
}
*/
pthread_t t1,t2;printf("id=%d\n",sockfd);
pthread_create(&t1,NULL,reader, (void*)sockfd);
pthread_create(&t2,NULL,writer, (void*)sockfd);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
}
