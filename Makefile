CC := g++ -std=c++11
CCFLAGS := -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
RUNFLAG := -c -g
SRC_PATH :=

a.out: Defines.o Generals.o ThingsThatsNotMub.o Player.o Enemies.o main.o GameController.o
	$(CC) -g Defines.o Generals.o ThingsThatsNotMub.o Player.o Enemies.o main.o $(SRC_PATH)rsdl.cpp $(CCFLAGS) 

Defines.o: $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Defines.cpp

Player.o: $(SRC_PATH)Player.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Player.cpp

Enemies.o: $(SRC_PATH)Enemies.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Enemies.cpp

Generals.o: $(SRC_PATH)Generals.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Generals.cpp

ThingsThatsNotMub.o: $(SRC_PATH)ThingsThatsNotMub.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)ThingsThatsNotMub.cpp

GameController.o: $(SRC_PATH)GameController.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)GameController.cpp 

main.o: $(SRC_PATH)main.cpp StarWars.hpp $(SRC_PATH)GameController.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)main.cpp 

clean:
	rm *.o a.out
