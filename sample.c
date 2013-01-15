#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<stdbool.h>

bool user_check(char uname[5],char passwd[3]){
/*
switch(&uname){
case 'user1': if(passwd=='sar') return true; else false;break;
case 'user2': if(passwd=='sar') return true; else false;break;
default: return false;
}
*/
if(strncmp(uname,"user1",5)==0){if(strncmp(passwd,"sar",3)==0) return true; else printf("%s",passwd);return false; 
}
else if(strncmp(uname,"user2",5)==0){if(strcmp(passwd,"sar")) return true; else return false; }
else return false;
}

int main(){
bool f=user_check("user1","sar");
printf("%d\n",f);

}
