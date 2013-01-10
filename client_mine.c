#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

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

//updating

char buf[1024];
bzero(&buf,sizeof(buf));
fgets(buf,255,stdin);

if((n=write(sockfd,buf,sizeof(buf)))<0){
printf("failed write %d\n",n);exit(0);}
bzero((char*)&buf,sizeof(buf));

read(sockfd,buf,sizeof(buf));
printf("output from server: %s\n",buf);
}
