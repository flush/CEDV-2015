CC=g++
CFLAGS=-c -Wall -I./inc
LDFLAGS=-shared
SOURCES=./src/records.cpp  
OBJECTS=$(SOURCES:.cpp=.o)
LIBNAME=librecords.so
LIBPATH=./lib

all: $(SOURCES) $(LIBNAME)
    
$(LIBNAME): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(LIBPATH)/$@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ./lib/$(LIBNAME) ./src/*.o *.o

