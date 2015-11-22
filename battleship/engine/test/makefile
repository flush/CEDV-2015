CC=g++
CFLAGS=-c -Wall -I../inc
LDFLAGS=
SOURCES=../src/ship.cpp ../src/fleet.cpp ../src/common.cpp ./main.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=battleship

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) ../src/*.o *.o

