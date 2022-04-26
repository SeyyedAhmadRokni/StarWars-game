CC := g++ -std=c++11
CCFLAGS := -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
SRC_PATH :=

a.out: Defines.o Generals.o ThingsThatsNotMub.o Player.o Enemies.o
	$(CC) Defines.o Generals.o ThingsThatsNotMub.o Player.o Enemies.o $(SRC_PATH)rsdl.cpp $(CCFLAGS) 

Defines.o: $(SRC_PATH)Defines.cpp
	$(CC) -c $(SRC_PATH)Defines.cpp

Player.o: $(SRC_PATH)Player.cpp StarWars.hpp
	$(CC) -c $(SRC_PATH)Player.cpp

Enemies.o: $(SRC_PATH)Enemies.cpp StarWars.hpp
	$(CC) -c $(SRC_PATH)Enemies.cpp

Generals.o: $(SRC_PATH)Generals.cpp StarWars.hpp
	$(CC) -c $(SRC_PATH)Generals.cpp

ThingsThatsNotMub.cpp.o: $(SRC_PATH)ThingsThatsNotMub.cpp StarWras.hpp
	$(CC) -c $(SRC_PATH)ThingsThatsNotMub.cpp

clean:
	rm *.o a.out