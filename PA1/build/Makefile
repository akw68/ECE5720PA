CC  = gcc
CCFLAGS = -Wall 
LDFLAGS = -lpthread -lrt

N = 25000
P = 2

bksb: ../src/bksb.c 
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS)
	# ./$@ $(N)

pbksb: ../src/pbksb.c 
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS)
	# ./$@ $(N) $(P)

test: clean bksb pbksb
	./bksb $(N)
	./pbksb $(N) $(P)

clean:
	rm -rf *.o bksb pbksb *.out ref.h