CC := g++ -std=c++11
CCFLAGS := -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
SRC_PATH :=

a.out: Defines.o enums.o
	$(CC) Defines.o $(SRC_PATH)rsdl.cpp enums.o $(CCFLAGS) 
Defines.o: $(SRC_PATH)Defines.cpp
	$(CC) -c $(SRC_PATH)Defines.cpp

enums.o: enums.cpp rsdl.hpp StarWars.hpp
	$(CC) -c $(SRC_PATH)enums.cpp -o enums.o


# Enemies.o: $(SRC_PATH)Enemies.cpp StarWras.hpp
# 	$(CC) -c $(SRC_PATH)Enemies.cpp -o Enemies.o
GameController.o: $(SRC_PATH)GameController.cpp
	$(CC)  -c $(SRC_PATH)GameController.cpp -o GameController.o

# Generals.o: $(SRC_PATH)Generals.cpp StarWras.hpp
# 	$(CC) -c $(SRC_PATH)Generals.cpp -o Generals.o

# ThingsThatsNotMub.cpp.o: $(SRC_PATH)ThingsThatsNotMub.cpp StarWras.hpp
# 	$(CC) -c $(SRC_PATH)ThingsThatsNotMub.cpp -o Defines.o

clean:
	rm *.o a.out