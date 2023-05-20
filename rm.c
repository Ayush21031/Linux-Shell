#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<dirent.h>


int main(int a,char** ptr){
	// printf("ptr in file %s\n",ptr[2]);
	if(strcmp(ptr[1],"-v")==0){
		DIR* p = opendir(ptr[2]);
		if(p!=NULL){
			printf("cannot remove '%s' is a directory:\n",ptr[2]);
		}
		else{
			int result = remove(ptr[2]);
			if(result==0){
				printf("removed '%s' \n",ptr[2]);
			}
			else{
				printf("rm: cannot remove %s : No such file in directory\n",ptr[2]);
			}
		}
	}
	else if(strcmp(ptr[1],"-i")==0){
		char choice;
		DIR* p = opendir(ptr[2]);
		if(p!=NULL){
			printf("Cannot remove %s is a directory\n",ptr[2]);
		}
		else{
			printf("Are you sure you want to delete %s(y/n)",ptr[2]);
			scanf("%c",&choice);
			if(choice=='y' || choice=='Y'){
				int k = remove(ptr[2]);
				if(k!=0){
					printf("cannot remove %s : No such file or directory exists\n",ptr[2]);
				}

			}
		}
	}
	else if(strcmp(ptr[1],"-d")==0){
		DIR* p = opendir(ptr[2]);
		if(p!=NULL){
			int result = remove(ptr[2]);
			if(result==0){
				printf("Directory %s removed successfully\n",ptr[2]);
			}
			else{
				printf("rm: cannot remove %s : No such file or directory exits\n",ptr[2]);
			}
		}
		else{
			printf("%s is not a directory\n",ptr[2]);
		}
	}
	else if(strcmp(ptr[1],"0")==0){
		DIR* p = opendir(ptr[2]);
		if(p!=NULL){
			printf("cannot remove %s is a directory\n",ptr[2]);
		}
		else{
			int g = remove(ptr[2]);
			// printf("%d\n",g);
			if(g!=0){
				printf("cannot remove %s : No such file or directory\n",ptr[2]);
			}
		}
	}
	return 0;
}
