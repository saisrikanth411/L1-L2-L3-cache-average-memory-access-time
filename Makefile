CC = gcc
CFLAGS = -Wall 

all: random randomread mountain linearread

random: random.c  clock.c 
	$(CC) $(CFLAGS) -o random random.c  clock.c 

randomread: randomread.c  clock.c 
	$(CC) $(CFLAGS) -o randomread randomread.c  clock.c 

mountain: mountain.c fcyc2.c clock.c 
	$(CC) $(CFLAGS) -o mountain mountain.c fcyc2.c clock.c

linearread: linearread.c fcyc2.c clock.c 
	$(CC) $(CFLAGS) -o linearread linearread.c fcyc2.c clock.c 


clean:
	rm -f random *.o *~
	rm -f randomread *.o *~
	rm -f linearread *.o *~
	rm -f mountain *.o *~
