CC=g++
CFLAGS=-c -Wall -I./inc
LDFLAGS=
EXECUTABLE=libbship.a
CPP_FILES := $(wildcard ./src/*.cpp)
OBJ_FILES := $(addprefix ./obj/,$(notdir $(CPP_FILES:.cpp=.o)))



all: ${OBJ_FILES} $(EXECUTABLE)    

$(EXECUTABLE): $(OBJ_FILES)
	ar rcs ${EXECUTABLE} $(OBJ_FILES) 


./obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) ./obj/*.o *.o *.a

