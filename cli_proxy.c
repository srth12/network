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

int main(int argc,char **argv){
char buf[1024000];

int i; 
int sockfd,portno,n;struct sockaddr_in host;
if(argc==1){printf("Required format is %s <portno of proxy>\n",argv[0]);}
printf("okkkk\n");portno=atoi(argv[1]);
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
	printf("Enter url\n");
	char url[50];
	gets(url);snprintf(buf,sizeof(buf),"%s%s%s","GET ",url," HTTP/1.1");
	i=write(sockfd,buf,sizeof(buf));
	if(i<0){printf("error in writing\n");exit(0);}
	i=read(sockfd,buf,sizeof(buf));
	if(i<0){printf("error in reading,,\n");exit(0);}
			printf("%s",buf);
	
}
	
