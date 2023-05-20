#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<errno.h>

int main(int a,char **ptr){
    if(strcmp(ptr[2],"-v")==0){
        char* name = ptr[1];
        int result = mkdir(name,0777);
        if(result==0){
            printf("mkdir: created directory :%s\n",name);
        }
        else{
            printf("mkdir: directory not created : file exists\n");
        }        
    }
    else if(strcmp(ptr[2],"-p")==0){
        char s[100];
        char *name = ptr[1];
        char delim[] = "/";
        char * pt = strtok(name,delim);
        // while(pt!=NULL){
        //     int result = chdir(pt);
        //     getcwd(s,100);
        //     if(result!=0){
        //         int rs = mkdir(pt,0777);
        //         printf("%d",rs);
        //             if(rs==0){
        //                 chdir(pt);
        //             }
        //             else{
        //                 printf("unable to create folder");
        //             }
        //         }
        while(pt!=NULL){
            int result = mkdir(pt,0777);
            if(result!=0){
                chdir(pt);
            }
            else if(result==0){
                chdir(pt);
            }
            pt = strtok(NULL,delim);
        }
    }
    else if(strcmp(ptr[2],"0")==0){
        char* name = ptr[1];
        int result = mkdir(name,0777);
        // printf("%d\n",result);
        if(result==0){
            // printf("mkdir: created directory 2 %s\n",name);
        }
        else{
            printf("mkdir: directory not created : file exists\n");
        }    
    }
        }
// }
