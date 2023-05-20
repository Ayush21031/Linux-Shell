#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int a, char**ptr){
	// printf("Entered ls file\n");
	DIR *d;
	struct dirent *file;
	// printf("hello bro..%s",*ptr[0]);

	if(strcmp(ptr[1],"0")==0){ //"0"
		// printf("Entered if 0 condition\n");
		d = opendir(".");
		if(d==NULL){
			printf("Error occured\n");
		}
		else{
			// printf("Entered else condition\n");
			file = readdir(d);
			while(file!=NULL){
				// printf("Entered while loop");
				// printf("%s\n",file->d_name);
				if(file->d_name[0]=='.'){
					file = readdir(d);
					continue;
				}
				else{
					printf("%s\n",file->d_name);
					file = readdir(d);
				}
				// file = readdir(d);
			}
		}

	}
	else if(strcmp(ptr[1],"-a")==0){ //"-a"
		// printf("Entered if -a condition\n");
		d = opendir(".");
		if(d==NULL){
			printf("Error occured\n");
		}
		else{
			// printf("Entered else condition\n");
			file = readdir(d);
			while(file!=NULL){
				// printf("Entered while loop");
				printf("%s\n",file->d_name);
				// if(file->d_name[0]=='.'){
				// 	file = readdir(d);
				// 	continue;
				// }
				// else{
				// 	printf("%s\n",file->d_name);
				// 	file = readdir(d);
				// }
				file = readdir(d);
			}
		}
	}
	else if(strcmp(ptr[1],"-i")==0){
		// printf("Entered if -i condition\n");
		d = opendir(".");
		if(d==NULL){
			printf("Error occured\n");
		}
		else{
			// printf("Entered else condition\n");
			file = readdir(d);
			while(file!=NULL){
				// printf("Entered while loop");
				// printf("%s\n",file->d_name);
				if(file->d_name[0]=='.'){
					file = readdir(d);
					continue;
				}
				else{
					printf("%ld %s\n",file->d_ino,file->d_name);
					file = readdir(d);
				}
				// file = readdir(d);
			}
		}
	}
	return 0;
}