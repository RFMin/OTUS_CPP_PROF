CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c11
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
    CHECK=-lcheck -L.
	#LEAK=leaks -atExit -- ./a.out
else
    CHECK=-lcheck -lm -lsubunit -lrt -lpthread -L. #-L/usr/lib -L/usr/local/lib 
	#LEAK=valgrind -q --track-origins=yes ./a.out
endif

all: ip_filter

rebuild: clean all

#test: clean s21_string.o s21_sscanf_tests.o s21_sprintf_tests.o s21_string_tests.o s21_string_test_new.o
#	$(CC) $(CFLAGS) main.c s21_string.o s21_sscanf_tests.o s21_sprintf_tests.o s21_string_tests.o s21_string_test_new.o $(CHECK)
#	./a.out 

clean:
	rm -rf *.g* *.out *.o *.a

ip_filter: ip_filter.o
	$(CC) $(CFLAGS) ip_filter.o -o ip_filter

ip-filter.o:
	$(CC) $(CFLAGS) -c ip_srt_c.cpp

valgrind: rebuild
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./ip_filter
	cat RESULT_VALGRIND.txt