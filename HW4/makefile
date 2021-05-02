CC=gcc
CFLAGS=-g -Wall -std=c99
CCLINK=$(CC)
OBJS=grades.o
EXEC=libgrades.so
RM=libgrades.so *.o

#main compile command
$(EXEC): $(OBJS)
	$(CCLINK) -shared $(OBJS) -o $(EXEC) -llinked-list -L.

#dependencies specifications  
grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAG) -c -fpic grades.c


#removes all .o files and prog file
clean:
	rm -rf $(RM)
