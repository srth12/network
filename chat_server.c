#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<stdbool.h>
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

if(strncmp(uname,"user-2:",7)==0){if(strncmp(passwd,"sar",3)==0) { return true;} else return false; }
else if(strncmp(uname,"user-1:",7)==0){if(strncmp(passwd,"sar",3)==0){ return true;} else{ printf("iiiii,%s\n\n",passwd);return false;} }
else if(strncmp(uname,"user-3:",7)==0){if(strncmp(passwd,"sar",3)==0) return true; else return false; }
else return false;
}


void* fn(void *newsockfd){
char buffer[255];int n;
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

snprintf(temp,sizeof(temp),"From user-%d\n",my_no[(int)newsockfd]);
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
//printf("*%d*,%s\n",u,buffer);
//if(n<0){printf("reading client message failed\n");return 0;}
//printf("succcccccccccccccc\n");

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
	int p=get_user_no(uname,clifd);printf("p=%d\n",p);
snprintf(uname,sizeof(uname),"user-%d\n",p);
strcat(logged_in_usrlist,uname);
my_no[clifd]=p;// adding current users id to global var

strcpy(ttt,"successfully logged in :\n Logged in users :");
strcat(ttt,logged_in_usrlist);
if((i=write(clifd,ttt,100))<0){printf("error writing file");exit(0);}
//logged_in_usrlist[no_of_users]=&uname;
//for( q=0;q<=no_of_users;q++){printf("Logged in usrs:%s;",&logged_in_usrlist[q]);}

//printf("my_no=%s\n",logged_in_usrlist);
//if((i=write(clifd,logged_in_usrlist,100)<0)){printf("rclient list disp failded");return 0;}
//write(clifd,logged_in_usrlist,sizeof(logged_in_usrlist));
pthread_create(&pd[i],NULL,fn,(void*)clifd);
++i;++no_of_users;


}
else{if((i=write(clifd,"Invalid username and password",30))<0){printf("erroring uname and pawd failed");exit(0);} close(clifd);}

}
}
