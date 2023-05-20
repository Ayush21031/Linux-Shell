#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <errno.h>
#include <dirent.h>

int main(int a,char** ptr){
	
	if(strcmp(ptr[1],"-E")==0){
	FILE *file;
	file = fopen(ptr[2],"r");
	if(file==NULL){
		printf("File not found");
	}
	else{
	char c = fgetc(file);
	while(c!=EOF){
		if(c=='\n'){
			printf("$\n");
		}
		else{
			printf("%c",c);
		}
		c = fgetc(file);
	}
	fclose(file);	
	}
}
	else if(strcmp(ptr[1],"-T")==0){
		FILE *file;
		file = fopen(ptr[2],"r");
		if(file==NULL){
			printf("File not found");
		}
		else{
			// int count = 1;
			char c = fgetc(file);
			// printf("%d ",count);
			while(c!=EOF){
				if(c=='\t'){
					// printf("\n");
					// count++;
					printf("^I");
				}
				else{
					printf("%c",c);
				}
				c = fgetc(file);
			}
			fclose(file);
		}

	}

	else if(strcmp(ptr[1],"0")==0){
		FILE *file;
		file = fopen(ptr[2],"r");
		if(file==NULL){
			printf("File not found\n");
		}
		else{
			char c = fgetc(file);
			while(c!=EOF){
				printf("%c",c);
				c = fgetc(file);
			}
		}
		fclose(file);
	}
	return 0;
}