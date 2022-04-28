CC := g++ -std=c++11
CCFLAGS := -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
RUNFLAG := -c -g
SRC_PATH :=

a.out: Defines.o BasicStructures.o GameEquipments.o Player.o Enemies.o main.o Game.o EnemyManager.o OtherGameManagers.o PlayerManager.o

	$(CC) -g $(SRC_PATH)rsdl.cpp Defines.o BasicStructures.o GameEquipments.o Player.o Enemies.o EnemyManager.o OtherGameManagers.o PlayerManager.o Game.o main.o $(CCFLAGS) 


Defines.o: $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Defines.cpp

Player.o: $(SRC_PATH)Player.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Player.cpp

Enemies.o: $(SRC_PATH)Enemies.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Enemies.cpp

BasicStructures.o: $(SRC_PATH)BasicStructures.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)BasicStructures.cpp

GameEquipments.o: $(SRC_PATH)GameEquipments.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)GameEquipments.cpp

Game.o: $(SRC_PATH)Game.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Game.cpp 

EnemyManager.o: $(SRC_PATH)EnemyManager.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)EnemyManager.cpp

OtherGameManagers.o: $(SRC_PATH)OtherGameManagers.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)OtherGameManagers.cpp

PlayerManager.o: $(SRC_PATH)PlayerManager.cpp StarWars.hpp $(SRC_PATH)Defines.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)PlayerManager.cpp

main.o: $(SRC_PATH)main.cpp StarWars.hpp $(SRC_PATH)Game.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)main.cpp 

clean:
	rm *.o a.out
