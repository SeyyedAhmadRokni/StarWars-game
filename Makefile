CC := g++ -std=c++11
CCFLAGS := -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
RUNFLAG := -c -g
SRC_PATH := src/


starwars.out: BasicStructures.o GameEquipments.o Player.o Enemies.o main.o Game.o EnemyManager.o OtherGameManagers.o PlayerManager.o

	$(CC) -g $(SRC_PATH)rsdl.cpp BasicStructures.o GameEquipments.o Player.o Enemies.o EnemyManager.o OtherGameManagers.o PlayerManager.o Game.o main.o -o starwars.out $(CCFLAGS) 

Player.o: $(SRC_PATH)Player.cpp $(SRC_PATH)Player.hpp $(SRC_PATH)Defines.hpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Player.cpp

Enemies.o: $(SRC_PATH)Enemies.cpp $(SRC_PATH)Enemies.hpp $(SRC_PATH)Defines.hpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Enemies.cpp

BasicStructures.o: $(SRC_PATH)BasicStructures.cpp $(SRC_PATH)BasicStructures.hpp $(SRC_PATH)Defines.hpp
	$(CC) $(RUNFLAG) $(SRC_PATH)BasicStructures.cpp

GameEquipments.o: $(SRC_PATH)GameEquipments.cpp $(SRC_PATH)Arrow.hpp $(SRC_PATH)Items.hpp  $(SRC_PATH)Defines.hpp
	$(CC) $(RUNFLAG) $(SRC_PATH)GameEquipments.cpp

Game.o: $(SRC_PATH)Game.cpp $(SRC_PATH)StarWars.hpp $(SRC_PATH)Defines.hpp
	$(CC) $(RUNFLAG) $(SRC_PATH)Game.cpp 

EnemyManager.o: $(SRC_PATH)EnemyManager.cpp $(SRC_PATH)Managers.hpp $(SRC_PATH)Defines.hpp
	$(CC) $(RUNFLAG) $(SRC_PATH)EnemyManager.cpp

OtherGameManagers.o: $(SRC_PATH)OtherGameManagers.cpp $(SRC_PATH)Managers.hpp $(SRC_PATH)Defines.hpp
	$(CC) $(RUNFLAG) $(SRC_PATH)OtherGameManagers.cpp

PlayerManager.o: $(SRC_PATH)PlayerManager.cpp $(SRC_PATH)Managers.hpp $(SRC_PATH)Defines.hpp
	$(CC) $(RUNFLAG) $(SRC_PATH)PlayerManager.cpp

main.o: $(SRC_PATH)main.cpp $(SRC_PATH)StarWars.hpp $(SRC_PATH)Game.cpp
	$(CC) $(RUNFLAG) $(SRC_PATH)main.cpp 

clean:
	rm *.o starwars.out
