CC      = gcc
CFLAGS = -Wall -pedantic -Wextra
OBJECTS = prodcom.o reader.o munch1.o munch2.o writer.o queue.o stats.o

prodcom: $(OBJECTS)
	$(CC) $(CFLAGS) -o prodcom $(OBJECTS) -pthread

prodcom.o: prodcom.c reader.h munch1.h munch2.h writer.h queue.h
	$(CC) $(CFLAGS) -c prodcom.c

reader.o: reader.c reader.h queue.h
	$(CC) $(CFLAGS) -c reader.c

munch1.o: munch1.c munch1.h queue.h
	$(CC) $(CFLAGS) -c munch1.c

munch2.o: munch2.c munch2.h queue.h
	$(CC) $(CFLAGS) -c munch2.c

writer.o: writer.c writer.h queue.h
	$(CC) $(CFLAGS) -c writer.c

queue.o: queue.c queue.h stats.h
	$(CC) $(CFLAGS) -c queue.c
	
stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f $(OBJECTS) prodcom
