#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>

void* fn(void *newsockfd){
char buffer[255];
while(1){

bzero(buffer,256);
int n=0;
long arg1,arg2;
n = read(newsockfd,buffer,255);
     if (n < 0){ printf("ERROR reading from socket");exit(0);}
if(strlen(buffer) ==0) continue;

if(strcmp(buffer,"eof") ==0) break;
     printf("Here is the:%d: message: %s\n",newsockfd,buffer);
     sscanf(buffer,"%ld%ld",&arg1,&arg2);
     //printf("%ld,%ld",arg1,arg2);
	char buf[255];
     bzero((char *)&buf,sizeof(buf));
     snprintf(buf,sizeof(buf),"%ld\n",arg1+arg2);
   n = write(newsockfd,buf,strlen(buf));
     if (n < 0) error("ERROR writing to socket");

}
close(newsockfd);
}

int main(){

int portno,serfd,clifd;
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

int cli=sizeof(client);
clifd=accept(serfd,(struct sockaddr *) &client,&cli);

if(clifd<0){printf("Errror in accept\n");exit(0);}
pthread_create(&pd[i],NULL,fn,(void*)clifd);
++i;

}
}
