#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <errno.h>
#include <dirent.h>
#include<pthread.h>

void *date_fun(void *argument)
{
    system(argument);
    return NULL;
}

void pwd(char *ptr){
    if((ptr==NULL) || (strcmp(ptr,"-L")==0)){
        char dir[256];
        getcwd(dir,256);
        printf("%s\n",dir);
    }
    else if(strcmp(ptr,"-P")==0){
        char dir[256];
        getcwd(dir,256);
        printf("%s\n",dir); 
    }
    else{
        // printf("Invalid Tags\n");
        char dir[256];
        getcwd(dir,256);
        printf("%s\n",dir);
    }
}

void echo(char *ptr,char delim[],int m){
    if(m==0){
        if(strcmp(ptr,"-n")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                return;
            }
            else{
                while(ptr!=NULL){
                    printf("%s ",ptr);
                    ptr = strtok(NULL,delim);
                }
            }
        }
        else if(strcmp(ptr,"-e")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("\n");
                return;
            }
            else{
                while(ptr!=NULL){
                    int len = strlen(ptr);
                    int i=0;
                    // char *c = ptr;
                    while(i<len){
                        if(ptr[i]!='\\'){
                            printf("%c",ptr[i]);
                        }
                        i++;
                    }
                    printf(" ");
                    ptr = strtok(NULL,delim);
                }
            }
            printf("\n");
        }
    }
    else{
        while(ptr!=NULL){
            printf("%s ",ptr);
            ptr = strtok(NULL,delim);
        }
        printf("\n");
    }

}

void cd(char *ptr,char delim[]){
    if(ptr!=NULL){
           int output = chdir(ptr);
            char s[256];
            if(output==0){
                // getcwd(s,256);
                // printf("Directory changed successfully to-->>%s\n",s);
            }
            else{
                getcwd(s,256);
                printf("failed to change directory %s\n",s);
            }

        }
    
    else if(ptr==NULL){
        int output = chdir("/");
        output = chdir("home/ayush");
        if(output!=0){
            printf("Failed to change directory\n");
        }
    }
}

void mkdir(char *ptr,char delim[],char s[],int m,int h){
    int f;
    char path[256];
    strcpy(path,s);
    strcat(path,"/_make_dir");
    int flag=0;
    if(h==0){
        char *f = "a";
        int k;
        if(strcmp(ptr,"-v")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("Invalid command\n");
                flag = 1;
            }
            else{
                f = "-v";
            }
        }
        else if(strcmp(ptr,"-p")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("Invalid command\n");
                flag = 1;
            }
            else{
                f = "-p";
            }
        }
        else if(m==1){
            f = "0";
        }
        if(flag==0){
            while(ptr!=NULL){
                pid_t pid = fork();
                if(pid<0){
                    printf("Unable to create child\n");
                }
                else if(pid==0){
                    execl(path,"buffer",ptr,f,NULL);
                }
                else{
                    waitpid(pid,&k,0);
                }
                ptr = strtok(NULL,delim);
            }
        }
    }
    else if(h==1){
        char* f = "a";
        if(strcmp(ptr,"-v")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("Invalid command\n");
                flag = 1;
            }
            else{
                f = "-v";
            }
        }
        else if(strcmp(ptr,"-p")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("Invalid command\n");
                flag = 1;
            }
            else{
                f = "-p";
            }
        }
        else if(m==1){
            f = "0";
        }
        if(flag==0){
            while(ptr!=NULL){
                char *s = (char*)malloc(sizeof(char)*100);
                strcpy(s,path);
                strcat(s," ");
                strcat(s,ptr);
                strcat(s," ");
                strcat(s,f);
                pthread_t thread;
                pthread_create(&thread,NULL,date_fun,s);
                pthread_join(thread,NULL);
                ptr = strtok(NULL,delim);

            }
        }
    }
}


void ls(char* ptr,char delim[],char s[],int h){
    char path[256];
    strcpy(path,s);
    strcat(path,"/_ls");
    int k;
    if(h==0){
        char *f = "a";
        if(ptr==NULL){
            f = "0";
        }
        else if(strcmp(ptr,"-a")==0){
            f = "-a";
        }
        else if(strcmp(ptr,"-i")==0){
            f = "-i";
        }
        pid_t pid = fork();
        if(pid<0){
            printf("Unable to create child\n");
        }
        else if(pid==0){
            execl(path,"buffer",f,NULL);
        }
        else{
            waitpid(pid,&k,0);
        }
    }
    else if(h==1){
        char *f = "a";
        if(ptr==NULL){
            f = "0";
        }
        else if(strcmp(ptr,"-a")==0){
            f = "-a";
        }
        else if(strcmp(ptr,"-i")==0){
            f = "-i";
        }
        strcat(path," ");
        strcat(path,f);
        pthread_t thread;
        pthread_create(&thread,NULL,date_fun,path);
        pthread_join(thread,NULL);

    }
}


void cat(char* ptr,char delim[],char s[],int m,int h){
    char path[256];
    strcpy(path,s);
    strcat(path,"/_cat");
    int k;
    int flag = 0;
    if(h==0){
        char* f = "a";
        if(strcmp(ptr,"-E")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                flag =1;
                printf("Invalid command\n");
            }
            else{
                f = "-E";
            }
        }
        else if(strcmp(ptr,"-T")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                flag =1;
                printf("Invalid command\n");
            }
            else{
                f = "-T";
            }
        }
        else if(m==1){
            f = "0";
        }
        if(flag==0){
            while(ptr!=NULL){
                pid_t pid = fork();
                if(pid<0){
                    printf("Unable to create child\n");
                }
                else if(pid==0){
                    // ptr = strtok(NULL,delim);
                    execl(path,"buffer",f,ptr,NULL);
                }
                else{
                    waitpid(pid,&k,0);
                }
                ptr = strtok(NULL,delim);
            }
        }
    }
    else if(h==1){
        char *f = "a";
        if(strcmp(ptr,"-E")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("Invalid command\n");
                flag =1;
            }
            else{
                f = "-E";
            }
        }
        else if(strcmp(ptr,"-T")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("Invalid command\n");
                flag =1;
            }
            else{
                f = "-T";
            }
        }
        else if(m==1){
            f = "0";
        }
        if(flag==0){
            while(ptr!=NULL){
                char *s = (char*)malloc(sizeof(char)*100);
                strcpy(s,path);
                strcat(s," ");
                strcat(s,f);
                strcat(s," ");
                strcat(s,ptr);
                pthread_t thread;
                pthread_create(&thread,NULL,date_fun,s);
                pthread_join(thread,NULL);
                ptr = strtok(NULL,delim);
            }
        }
    }

}

void rm(char* ptr,char delim[],char s[],int m,int h){
    char path[256];
    strcpy(path,s);
    strcat(path,"/_rm");
    int k;
    int flag = 0;
    if(h==0){
        char *f = "a";
        if(strcmp(ptr,"-v")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("Invalid command\n");
                flag = 1;
            }
            else{
                f = "-v";
            }
        }
        else if(strcmp(ptr,"-i")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                flag =1;
                printf("Invalid command\n");
            }
            else{
                f = "-i";
            }
        }
        else if(strcmp(ptr,"-d")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                flag =1;
                printf("Invalid command\n");
            }
            else{
                f = "-d";
            }
        }
        else if(m==1){
            f = "0";
        }

        if(flag==0){
            while(ptr!=NULL){
                pid_t pid = fork();
                if(pid<0){
                    printf("Unable to create child\n");
                }
                else if(pid==0){
                    execl(path,"buffer",f,ptr,NULL);
                }
                else{
                    waitpid(pid,&k,0);
                }
                ptr = strtok(NULL,delim);
            }
        }
    }
    else if(h==1){
        // printf("Inside h==1\n");
        char* k = "a";
        if(strcmp(ptr,"-v")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                flag =1;
                printf("Invalid command\n");
            }
            else{
                k = "-v";
            }
        }
        else if(strcmp(ptr,"-i")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                flag = 1;
                printf("Invalid command\n");
            }
            else{
                k = "-i";
            }
        }
        else if(strcmp(ptr,"-d")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                flag =1;
                printf("Invalid command\n");
            }
            else{
                k = "-d";
            }
        }
        else if(m==1){
            k = "0";
        }
        if(flag==0){
            while(ptr!=NULL){
                char *s = (char*)malloc(sizeof(char)*100);
                strcpy(s,path);
                strcat(s," ");
                strcat(s,k);
                strcat(s," ");
                strcat(s,ptr);
                pthread_t thread;
                pthread_create(&thread,NULL,date_fun,s);
                pthread_join(thread,NULL);
                ptr = strtok(NULL,delim);
            }
        }
    }
}


void date(char* ptr,char delim[],char s[],int h){
    char path[256];
    strcpy(path,s);
    strcat(path,"/_date");
    int k;
    int flag = 0;
    // printf("%d\n",h);
    if(h==0){
        char *f = "a";
        if(ptr==NULL){
            f = "0";
        }
        else if(strcmp(ptr,"-u")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                f = "-u";
            }
            else{
                printf("Invalid syntax\n");
                flag = 1;
            }

        }
        else if(strcmp(ptr,"-R")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                f = "-R";
            }
            else{
                flag = 1;
                printf("Invalid syntax\n");
            }
        }
        if(flag==0){
            pid_t pid = fork();
            if(pid<0){
                printf("Unable to create child\n");
            }
            else if(pid==0){
                execl(path,"buffer",f,ptr,NULL);
            }
            else{
                waitpid(pid,&k,0);
            }
        }
    }

    else if(h==1){
        char *f = "a";
        if(ptr==NULL){
            f = "0";
        }
        else if(strcmp(ptr,"-u")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                f = "-u";
            }
            else{
                printf("Invalid syntax\n");
                flag = 1;
            }
        }
        else if(strcmp(ptr,"-R")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                f = "-R";
            }
            else{
                printf("Invalid syntax\n");
                flag = 1;
            }
        }
        // printf("here %s\n",f);
        if(flag==0){
            strcat(path," ");
            strcat(path,f);
            strcat(path," ");
            pthread_t thread;
            pthread_create(&thread,NULL,date_fun,path);
            pthread_join(thread,NULL);
        }
    }
}


int main()
{
    int flag = 1;
    char curr_dir[1000];
    char copy_dir[1000];
    getcwd(curr_dir,1000);
    strcpy(copy_dir,curr_dir);    
    while(flag==1){
        getcwd(curr_dir,1000);
        printf("%s $$ ",curr_dir);
        int h = 0;
        char str[256];
        fgets(str,256,stdin);
        char delim[] = " ";
	    char deli[] = "\n";
	    char *point = strtok(str,deli);
        char *t = strtok(str,"&");
        // printf("check 1 t %s\n",t);
        char *str2 = (char*)malloc(sizeof(char)*256);
        strcpy(str2,t);
        // printf("check 2 str2 %s\n",str2);
        t = strtok(NULL,"&");
        // printf("check 3 t after & split %s\n",t);
        if(t!=NULL && strcmp(t,"t")==0){
            h = 1;
        }
        // printf("check 4 h value %d\n",h);
        char *ptr = strtok(str2, delim);
        int m=0;
        if(strcmp(ptr,"cd")==0){
            ptr= strtok(NULL,delim);
            cd(ptr,delim);
        }
        else if(strcmp(ptr,"pwd")==0){
            ptr = strtok(NULL,delim);
            // if(ptr==NULL || strcmp(ptr,"-L")==0 || strcmp(ptr,"-P")==0){
            //     pwd(ptr);
            // }
            // else{
            //     printf("Invalid Tag\n");
            // }
            pwd(ptr);
                    
        }
        else if(strcmp(ptr,"echo")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("\n");
            }
            else if(strcmp(ptr,"-n")==0 || strcmp(ptr,"-e")==0){
                m = 0;
                echo(ptr,delim,m);
            }
            else if(ptr!=NULL){
                m = 1;
                echo(ptr,delim,m);
            }
        }
        
        else if(strcmp(ptr,"exit")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                flag = 0;
            }
            else{
                printf("Invalid tags\n");
            }
        }

        else if(strcmp(ptr,"mkdir")==0){
            ptr = strtok(NULL,delim);
            // printf("%s",ptr);
            if(ptr==NULL){
                printf("Invalid command\n");
            }
            else if((ptr[0]=='-') && ((ptr[1]=='v')||(ptr[1]=='p'))){
                int m = 0;
                mkdir(ptr,delim,copy_dir,m,h);
            }
            else if(ptr[0]=='-'){
                printf("Invalid tag\n");
            }
            // else if(ptr==NULL){
            //     printf("Invalid command\n");
            // }
            else{
                m=1;
                mkdir(ptr,delim,copy_dir,m,h);
            }
        }

        else if(strcmp(ptr,"ls")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL || strcmp(ptr,"-a")==0 || strcmp(ptr,"-i")==0){
                ls(ptr,delim,copy_dir,h);
            }
            else{
                printf("Invalid tag\n");
            }
            
        }

        else if(strcmp(ptr,"cat")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL){
                printf("Invalid command\n");
            }
            else if(ptr[0]=='-' && (ptr[1]=='T' || ptr[1]=='E')){
                m=0;
                cat(ptr,delim,copy_dir,m,h);
            }
            else if(ptr[0]=='-'){
                printf("Invalid tag\n");
            }
            else{
                m=1;
                cat(ptr,delim,copy_dir,m,h);
            }
        }

        else if(strcmp(ptr,"rm")==0){
            ptr = strtok(NULL,delim);
            // printf("%s",ptr);
            if(ptr==NULL){
                printf("Invalid command\n");
            }
            else if(strcmp(ptr,"-v")==0 || strcmp(ptr,"-d")==0 || strcmp(ptr,"-i")==0){
                m = 0;
                rm(ptr,delim,copy_dir,m,h);
            }
            else if(ptr[0]=='-'){
                printf("Invalid tag\n");
            }
            else{
                m = 1;
                rm(ptr,delim,copy_dir,m,h);
            }
        }

        else if(strcmp(ptr,"date")==0){
            ptr = strtok(NULL,delim);
            if(ptr==NULL || strcmp(ptr,"-u")==0 || strcmp(ptr,"-R")==0){
                date(ptr,delim,copy_dir,h);
            }
            else if(ptr[0]=='-'){
                printf("Invalid tag\n");
            }
            else{
                printf("Invalid date or unable to set date\n");
            }
        }
        else{
            printf("Invalid command\n");
        }
    }    
	return 0;
}
