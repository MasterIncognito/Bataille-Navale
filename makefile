exe: main.o fnBasic.o fnCore.o
	gcc -o exe main.o fnBasic.o fnCore.o
	
main.o: main.c var.h fnBasic.h fnCore.h
	gcc -c main.c

fnbasic.o: fnBasic.c fnBasic.h var.h
	gcc -c fnBasic.c

fnCore.o: fnCore.c fnCore.h var.h fnBasic.h
	gcc -c fnCore.c
