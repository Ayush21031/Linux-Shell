all: A B C D E F
A:shell.c
	gcc shell.c -o shell.o
B:ls.c
	gcc ls.c -o _ls
C:cat.c
	gcc cat.c -o _cat
D:rm.c
	gcc rm.c -o _rm
E:date.c
	gcc date.c -o _date
F:make_dir.c
	gcc make_dir.c -o _make_dir
clean:
	rm *.o