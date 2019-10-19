epoll_test.o: epoll_test.c epoll_test.h
	gcc -c epoll_test.c 

all: epoll_test.o
	gcc epoll_test.o -o epoll_test

clean:
	@if [ -f epoll_test ]; then \
	rm  epoll_test ;\
	fi 
	@if [ -f epoll_test.o ]; then \
	rm  epoll_test.o ;\
	fi 
