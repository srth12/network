#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>

int main(){

int sockfd,portno,n;
portno=atoi("55555");
if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
printf("socket failed\n");}

struct sockaddr_in host;
bzero(&host,sizeof(host));
host.sin_family=AF_INET;
host.sin_port=htons(portno);
inet_pton(AF_INET,"127.0.0.1",&host.sin_addr);// assigning server address;
if(connect(sockfd,(struct sockaddr*)&host,sizeof(host))<0){
printf("connection failed\n");
exit(0);
}

char buf[1024];

int i; 
bzero(&buf,sizeof(&buf));
if((i=read(sockfd,buf,sizeof(buf)))<0){printf("reading uname request failed\n");exit(0);}
printf("%s",buf);
bzero(&buf,sizeof(&buf));
fgets(buf,255,stdin);
printf("%s",buf);
if((n=write(sockfd,buf,sizeof(buf)))<0){
printf("failed write %d\n",n);exit(0);}
bzero(&buf,sizeof(buf));
read(sockfd,buf,100);
printf("output from server: %s\n",buf);
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
}
