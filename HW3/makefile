CC=gcc
CFLAGS=-g -Wall -std=c99
CCLINK=$(CC)
OBJS=file0.o file1.o file2.o file3.o file4.o main.o
EXEC=prog
RM=prog *.o

#main compile command
$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

#dependencies specifications  
file0.o: file0.c file0.h file4.h
	$(CC) $(CFLAG) -c file0.c

file1.o: file0.h file1.c file1.h file2.h file3.h
	$(CC) $(CFLAG) -c file1.c

file2.o: file0.h file2.c file2.h file4.h
	$(CC) $(CFLAG) -c file2.c

file3.o: file3.c file3.h file4.h
	$(CC) $(CFLAG) -c file3.c

file4.o: file0.h file2.h file4.c file4.h
	$(CC) $(CFLAG) -c file4.c

main.o: main.c file0.h file1.h file2.h file3.h file4.h
	$(CC) $(CFLAG) -c main.c

#removes all .o files and prog file
clean:
	rm -rf $(RM)
