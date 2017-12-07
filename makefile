all: control.c
	gcc -o control control.c

run: all
	./control -c 4
	./control -v
	./control -c 3
	./control -v
	./control -r
