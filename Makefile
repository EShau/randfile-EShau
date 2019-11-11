ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: dr_main.o
	$(CC) -o test_dev_random dr_main.o

dr_main.o: dr_main.c
	$(CC) -c dr_main.c

run:
	./test_dev_random

memcheck:
	valgrind --leak-check=yes ./test_dev_random

clean:
	rm *.o
	rm *~
