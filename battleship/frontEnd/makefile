CC=g++
CFLAGS=-c -Wall  -I./include  -w `pkg-config --cflags OGRE OGRE-Overlay` 
CPP_FILES := $(wildcard ./src/*.cpp)
OBJ_FILES := $(addprefix ./obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LDFLAGS=`pkg-config --libs-only-l OGRE OGRE-Overlay` -lboost_system -lOIS -lGL -lstdc++

EXECUTABLE=battleship

$(info VAR is $(CPP_FILES))
$(info VAR is $(OBJ_FILES))

all: $(CPP_FILES) $(EXECUTABLE)    
$(EXECUTABLE): $(OBJ_FILES) 
	$(CC) $(LDFLAGS) $(OBJ_FILES) -o $@

./obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) ./obj/*.o

