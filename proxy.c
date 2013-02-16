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
#include<netdb.h>

int con(int portno){
	int serfd;
struct sockaddr_in seraddr,client;


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

int cli=sizeof(client);
int clifd;
clifd=accept(serfd,(struct sockaddr *) &client,&cli);
if(clifd<=0){printf("Errror in accept\n");exit(0);}	
	return clifd;


}

int con_server(char domain[50],char uri[50],int portno){
/*
char buf[255];

int i; 
int sockfd,n;struct sockaddr_in host;


if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
printf("socket failed\n");}


bzero(&host,sizeof(host));
host.sin_family=AF_INET;
host.sin_port=htons(portno);
inet_pton(AF_INET,"74.125.135.102",&host.sin_addr);// assigning server address;

if(connect(sockfd,(struct sockaddr*)&host,sizeof(host))<0){
printf("connection failed\n");
exit(0);
}
*/

char buf[1024];

int i; 
int sockfd,n;struct sockaddr_in host;


struct addrinfo hints, *servinfo, *p;
int rv;
memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC; // use AF_INET6 to force IPv6
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags=AI_CANONNAME;
if ((rv = getaddrinfo(domain,"80", &hints, &servinfo)) != 0) {
fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
exit(1);
}
// loop through all the results and connect to the first we can
for(p = servinfo; p != NULL; p = p->ai_next) {
if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
perror("socket");
continue;
}
if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
close(sockfd);
perror("connect");
continue;
}


break; // if we get here, we must have connected successfully
}
if (p == NULL) {
// looped off the end of the list with no connection
fprintf(stderr, "failed to connect\n");
exit(2);
}
freeaddrinfo(servinfo);


printf("connecting to server successfull,%d\n",sockfd);
return sockfd;
}

int main(int argc,char **argv){
	if(argc!=2){printf("Input format expected is %s <port>",argv[0]);exit(0);}
	int portno=atoi(argv[1]);char *fff;
	int clifd=con(portno);
	printf("clifd is :%d\n",clifd);
		int i;char buf[1024];
		i=read(clifd,buf,sizeof(buf));	
		if(i<0){printf("Error in reading 1st req");exit(0);}
		char *pch;char domain[50],uri[50];int port;
		pch=strtok(buf," ");
	if(strcasecmp(pch,"get")==0){
		pch=strtok(NULL,"/");printf("domain:%s\n",pch);
		strcpy(domain,pch);// domain=pch;
		pch=strtok(NULL,":");printf("uri:%s\n",pch);
		strcpy(uri,pch);// uri=pch;
		pch=strtok(NULL,"\n");int size;
		if(pch==NULL){port=80;size=0;}
		else{
		port=atoi(pch);size=(int)strlen(pch);}
		printf("port:%d\n",port);
		printf("parsed items are:%s,%s,%d,%d\n",domain,uri,port,size);
	
	//connecting to server...
	int fd=con_server(domain,uri,port);	
	//printf("Server result is: \n%d",fd);
	
	fff="GET /index.html HTTP/1.0 \n From: google.com \n\n";

	i=write(fd,fff,strlen(fff));
	if(i<0){printf("writing to server failed\n");exit(0);}
	printf("written to server\n");
	i=read(fd,buf,sizeof(buf));
	if(i<0){printf("reading from server failed\n");exit(0);}
	printf("Server result is: \n%s",buf);
	i=write(clifd,buf,strlen(buf));
	if(i<0){printf("writing to client failed\n");exit(0);}
	}
	else{printf("Error in the format\n");i=write(clifd,"Error in the format\n",strlen("Error in the format\n"));
	if(i<0){printf("writing to client failed\n");exit(0);}}
}
