Task 2.A
compile:
	gcc task2a.c -o task2a -o task2a
	or
	gcc task2b.c -pthread -o task2a


Task 2.B
compile:
	gcc -DPTHREAD_SYNC task2b.c -pthread -o task2b
