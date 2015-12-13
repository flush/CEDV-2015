CC=g++
CFLAGS=-c -Wall -I../inc
LDFLAGS=
SOURCES=  ./main.cpp 
LIB=records
LIBDIR=../lib
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=records

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -L$(LIBDIR) -l$(LIB) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) ../src/*.o *.o

