all:	test.exe redec_test.exe

redec_test.exe:	redec_test.c
	gcc -Wall -o redec_test.exe redec_test.c

test.exe:	test.c
	gcc -Wall -o test.exe test.c test1.c test2.c single_test.c

clean:
	rm test.exe redec_test.exe
