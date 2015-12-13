CC=g++
CFLAGS=-c  -Wall  -I./include -I../engine/inc -w `pkg-config --cflags OGRE OGRE-Overlay` 
CPP_FILES := $(wildcard ./src/*.cpp)
OBJ_FILES := $(addprefix ./obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LDFLAGS=-L ./lib `pkg-config --libs-only-l OGRE OGRE-Overlay` -lboost_system -lOIS -lGL -lstdc++ -lbship2 

EXECUTABLE=battleship


all: engine $(EXECUTABLE)    
$(EXECUTABLE): ${CPP_FILES} $(OBJ_FILES) 
	$(CC) $(LDFLAGS) $(OBJ_FILES) -o $@

./obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) ./obj/*.o
engine:
	$(MAKE) -C ../engine
	cp ../engine/libbship.a ../frontEnd/lib

