CC=g++
CFLAGS=-c -g  -Wall  -I./include -I../engine/inc -w `pkg-config --cflags OGRE OGRE-Overlay` 
CPP_FILES := $(wildcard ./src/*.cpp)
OBJ_FILES := $(addprefix ./obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LDFLAGS= `pkg-config --libs-only-l OGRE OGRE-Overlay` -lboost_system -lOIS -lGL -lstdc++  

EXECUTABLE=battleship


all: engine $(EXECUTABLE)    
$(EXECUTABLE): ${CPP_FILES} $(OBJ_FILES) 
	$(CC) $(LDFLAGS) $(OBJ_FILES) ./lib/libbship.a -o $@

./obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) ./obj/*.o
engine:
	$(MAKE) -C ../engine
	cp ../engine/libbship.a ../frontEnd/lib

