#include<stdio.h>
#include<string.h>
#include<time.h>
int main(int a,char** ptr){
	time_t t1;
	time(&t1);
	char s[50];
	if(strcmp(ptr[1],"0")==0){
		strftime(s, 50, "%A %e %B %G %r %Z ", localtime(&t1));
		printf("%s\n", s);
	}
	else if(strcmp(ptr[1],"-u")==0){
		strftime(s, 50, "%A %e %B %G %r UTC ", gmtime(&t1));
		printf("%s\n", s);
	}
	else if(strcmp(ptr[1],"-R")==0){
		strftime(s, 50, "%a, %e %b %G %r %z ", localtime(&t1));
		printf("%s\n", s);
	}
	return 0;
}
