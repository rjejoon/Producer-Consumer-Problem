CFLAGS = -Wall -std=c99 -O
CXXFLAGS = -Wall -std=c++17 -O
DBGCFLAGS = -Wall -std=c99 -g
DBGCXXFLAGS = -Wall -std=c++17 -g

# Project files
OBJS = prodcon.o tands.o
DBGOBJS = debug_prodcon.o debug_tands.o
EXE = prodcon


# release
executable: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXE)

prodcon.o: prodcon.cpp prodcon.h tands.o
	$(CXX) $(CXXFLAGS) -c prodcon.cpp tands.o -o prodcon.o

tands.o: tands.c
	$(CC) $(CFLAGS) -c tands.c -o tands.o


# debug 
debug: $(DBGOBJS)
	$(CXX) $(DBGCXXFLAGS) $(DBGOBJS) -o $(EXE)

debug_prodcon.o: prodcon.cpp prodcon.h debug_tands.o
	$(CXX) $(DBGCXXFLAGS) -c prodcon.cpp debug_tands.o -o debug_prodcon.o

debug_tands.o: tands.c
	$(CC) $(DBGCFLAGS) -c tands.c -o debug_tands.o


compress:
	zip assign2.zip prodcon.cpp prodcon.h tands.c Makefile

clean:
	rm -f *.o
	rm -f $(EXE)
